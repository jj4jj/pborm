#include "dcpots/base/logger.h"
#include "dcpots/dcnode/dcnode.h"
#include "dcpots/utility/mysql/dcmysqlc_pool.h"
#include "dcpots/utility/drs/dcproto.h"
#include "dcpots/base/cmdline_opt.h"
#include "dcpots/base/msg_buffer.hpp"
#include "pbdcex/generater/mysql_gen.h"
#include "proto/pborm.pb.h"
#include "proto/pborm_conf.cex.hpp"
#include "pborm_msg.h"


#define MAJOR_VERSION   0
#define MINOR_VERSION   1
#define PATCH_VERSION   1

using namespace dcs;
using namespace pborm;
using namespace google::protobuf;
using namespace std;


#define MAX_MSG_BUFF_SIZE   (1024*1024*2)
static struct {
    dcnode_t            * dc;
    mysqlclient_pool_t  * mysql;
    MySQLMsgCvt         * converter;
    msg_buffer_t          msgbuff;
} g_ctx;


static int 
response_error_msg(int ret, const mysqlclient_pool_t::command_t & cmd){
    pborm_msg_t ormmsg;
    ormmsg.set_op((OrmMsgOP)cmd.opaque);
    if (cmd.cbdata.valid_size > 0){
        ormmsg.mutable_cb()->set_data(cmd.cbdata.buffer, cmd.cbdata.valid_size);
    }
    ormmsg.set_msg_full_type_name(cmd.full_msg_type_name);
    auto rsp = ormmsg.mutable_rsp();
    rsp->set_err_no(ret);
    rsp->set_err_msg("general error !");
    if (!ormmsg.Pack(g_ctx.msgbuff)){
        GLOG_ERR("msg pack error ! msg:%s", cmd.full_msg_type_name.c_str());
		return -1;
    }
    return dcnode_send(g_ctx.dc, cmd.src.c_str(), g_ctx.msgbuff.buffer, g_ctx.msgbuff.valid_size);
}

static inline void
_convert_orm_count_result(OrmMsgRsp * rsp,const mysqlclient_pool_t::result_t & result){
	if (!result.fetched_results.empty() && result.fetched_results[0][0].first == "COUNT(*)"){
		rsp->set_count(strtol(result.fetched_results[0][0].second.buffer, NULL, 10));
	}
	else {
		GLOG_ERR("select count(*) error result ! results.size(:%zu) field:%s",
			result.fetched_results.size(),	
			result.fetched_results[0][0].first.c_str());
		rsp->set_err_no(-1);
		rsp->set_err_msg("select count error result converting!");
	}
}

static inline void
_convert_orm_select_result(OrmMsgRsp * rsp,
	const mysqlclient_pool_t::result_t & result,const mysqlclient_pool_t::command_t & cmd){
	rsp->set_count(result.fetched_results.size());
	OrmMsgRspSelect * select = rsp->mutable_select();
	select->mutable_head()->set_offset(cmd.offset);
	select->mutable_head()->set_limit(cmd.limit);
	MySQLRow sqlrow;
	mysqlclient_t::table_row_t tbrow;
	for (size_t i = 0; i < result.fetched_results.size(); ++i){
		result.alloc_mysql_row_converted(tbrow, i);
		sqlrow.fields_name = tbrow.fields_name;
		sqlrow.num_fields = tbrow.fields_count;
		sqlrow.row_data = tbrow.row_data;
		sqlrow.row_lengths = tbrow.row_length;

		g_ctx.msgbuff.valid_size = g_ctx.msgbuff.max_size;
		int ret = g_ctx.converter->GetMsgBufferFromSQLRow(
			cmd.full_msg_type_name.c_str(),
			g_ctx.msgbuff.buffer,
			&g_ctx.msgbuff.valid_size, sqlrow, cmd.flatmode);
		result.free_mysql_row(tbrow);
		if (ret){
			GLOG_ERR("convert get msg :%s error !", cmd.full_msg_type_name.c_str());
			rsp->set_err_no(-110);
			rsp->set_err_msg("get msg buffer from sql row error !");
			return;
		}
		select->add_msgs(g_ctx.msgbuff.buffer, g_ctx.msgbuff.valid_size);
	}
}

static void
orm_msg_fetch_result(void *, const mysqlclient_pool_t::result_t & result,
                    const mysqlclient_pool_t::command_t & cmd){
    pborm_msg_t msg;
    msg.set_op((OrmMsgOP)cmd.opaque);
    if (cmd.cbdata.valid_size > 0){
        msg.mutable_cb()->set_data(cmd.cbdata.buffer, cmd.cbdata.valid_size);
    }
    msg.set_msg_full_type_name(cmd.full_msg_type_name);
    auto rsp = msg.mutable_rsp();
    int ret = 0;
	rsp->set_err_no(ret);
	auto msg_desc = g_ctx.converter->GetProtoMeta().GetMsgDesc(cmd.full_msg_type_name.c_str());
	if (!msg_desc){ //error msg
		rsp->set_err_no(-1);
		rsp->set_err_msg("not found the msg desc in meta !");
	}	
    else if (result.status){
        rsp->set_err_no(result.err_no);
        rsp->set_err_msg(result.error);
		GLOG_ERR("result stats :%d error:%d error msg:%s", result.status,
			result.err_no, result.error.c_str());
    }
    else {
        rsp->set_count(result.affects);
        if (cmd.opaque == ORM_SELECT){
			_convert_orm_select_result(rsp, result, cmd);
        }
		else if (cmd.opaque == ORM_COUNT){
			_convert_orm_count_result(rsp, result);
		}
    }
    GLOG_TRA("send msg result to api client:%s", msg.Debug());
    if (!msg.Pack(g_ctx.msgbuff)){
        GLOG_ERR("msg pack error ! type:%s msg:%s buffer size:%d",
            cmd.full_msg_type_name.c_str(), msg.Debug(), g_ctx.msgbuff.max_size);
        return;
    }
    ret = dcnode_send(g_ctx.dc, cmd.src.c_str(), g_ctx.msgbuff.buffer, g_ctx.msgbuff.valid_size);
    if (ret){
        GLOG_ERR("dcnode send msg error : %d !", ret);
    }
}

static int 
orm_msg_dispatcher(void * ud, const char * src, const msg_buffer_t & msg){
    assert(&g_ctx == ud);
    pborm_msg_t orm_msg;
    if (!orm_msg.Unpack(msg)){
        GLOG_ERR("unpack msg error !");
        return -1;
    }
	GLOG_TRA("recvef from client :%s msg:%s", src, orm_msg.Debug());
    Message * newmsg = nullptr;
    int ret = -1;
    mysqlclient_pool_t::command_t   cmd;
    cmd.cbdata.copy(orm_msg.cb().data().data(), orm_msg.cb().data().length());
    cmd.opaque = orm_msg.op();
    cmd.full_msg_type_name = orm_msg.msg_full_type_name();
    cmd.src = src;
	cmd.need_result = false;
    ////////////////////////////////////////////////////////////////////////////
    do {
        newmsg = g_ctx.converter->GetProtoMeta().NewDynMessage(orm_msg.msg_full_type_name().c_str(),
            orm_msg.req().msg_data().data(), orm_msg.req().msg_data().length());
        if (!newmsg){
            GLOG_ERR("can't find the msg :%s", orm_msg.msg_full_type_name().c_str());
            ret = -2;
            break;
        }
        if (g_ctx.converter->CheckMsgValid(newmsg->GetDescriptor())){
            GLOG_ERR("check msg:%s valid error !", orm_msg.msg_full_type_name().c_str());
            ret = -3;
            break;
        }
        MySQLMsgMeta msgen(g_ctx.converter);
        if (msgen.AttachMsg(newmsg)){
            GLOG_ERR("attach msg:%s valid error !", orm_msg.msg_full_type_name().c_str());
            ret = -4;
            break;
        }
        ///////////////////////////////////////////////////////////////////////
        bool flatmode = false;
        switch (orm_msg.op()){
        case ORM_COMMAND:
			ret = 0;
            break;
        case ORM_INSERT:
            ret = msgen.Insert(cmd.sql);
            break;
        case ORM_DELETE:
            ret = msgen.Delete(cmd.sql, nullptr, flatmode);
            break;
        case ORM_SELECT:
			do {
				cmd.need_result = true;
				std::vector<string>		fieldsv;
				strsplit(orm_msg.req().select().fields(), ",", fieldsv);
				cmd.offset = orm_msg.req().select().head().offset();
				cmd.limit = orm_msg.req().select().head().limit();
				ret = msgen.Select(cmd.sql, &fieldsv,
					orm_msg.req().select().where().c_str(),
					cmd.offset, cmd.limit,
					orm_msg.req().select().orderby().c_str(),
					orm_msg.req().select().order(),
					flatmode);
			} while (false);
            break;
        case ORM_UPDATE:
            ret = msgen.Update(cmd.sql, flatmode);
            break;
        case ORM_COUNT:
			cmd.need_result = true;
			ret = msgen.Count(cmd.sql, orm_msg.req().select().where().c_str());
            break;
        }
        if (ret){
            GLOG_ERR("generate sql error !");
            return -5;
        }
        ret = g_ctx.mysql->execute(cmd, orm_msg_fetch_result, 0);
        if (ret){
            GLOG_ERR("excute command error:%d !", ret);
            ret = -6;
        }
    } while (false);
    if (newmsg){
        g_ctx.converter->GetProtoMeta().FreeDynMessage(newmsg);
    }
    if (ret){
        return response_error_msg(ret, cmd);
    }
    return 0;
}

int 
main(int argc, char ** argv){   
    cmdline_opt_t   cmdline(argc, argv);
    cmdline.parse("config:r::config file:pborm.xml;"
        "version:n:v:show the version;"
        "genconf:n:g:generate a config file;");
    if (cmdline.hasopt("version")){
        cout << MAJOR_VERSION << "." << MINOR_VERSION << "." << PATCH_VERSION << endl;
        return 0;
    }
    if (cmdline.hasopt("g")){
        const pborm::Config &  def_conf = pborm::Config::default_instance();
        pborm::Config conf = def_conf;
        conf.add_meta_files("db.proto");
        conf.add_meta_files("comm.proto");
        const char * default_config_file = "pborm.default.xml";
        dcs::protobuf_msg_to_xml_file(conf, default_config_file);
        cout << "generate default config file :" << default_config_file << endl;
        return 0;
    }
    const char * confile = cmdline.getoptstr("config");
    if (access(confile, R_OK)){
        cerr << "config file :" << confile << " not exists !" << endl;
        return -1;
    }
    //read config
    pborm::Config xmlconfig;
    string error;
    int ret = protobuf_msg_from_xml_file(xmlconfig, confile, error);
    if (ret){
        cerr << "read config file error !" << endl;
        return -2;
    }
    cout << "config file as follow:" << endl;
    cout << xmlconfig.DebugString() << endl;
    pborm::Config_ST    config;
    config.convfrom(xmlconfig);
    /////////////////////////////////////////////////////////////////////////////
    if (lockpidfile(config.process.pidfile.data) != getpid()){
        GLOG_ERR("lock pid file error !");
        return -10;
    }
    logger_config_t logconf;
    logconf.dir = config.log.path.data;
    logconf.pattern = config.log.file_pattern.data;
    //logconf.lv = config.log.level;
    logconf.max_roll = config.log.max_roll;
    logconf.max_file_size = config.log.max_file_size;
    logconf.max_msg_size = config.log.max_line_size;

    global_logger_init(logconf);
    protobuf_logger_init();

    if (config.process.daemon){
        daemonlize();
    }
    
    g_ctx.msgbuff.create(MAX_MSG_BUFF_SIZE);

    //->dcnode
    //->mysql
    mysqlclient_pool_t  mcp;
    mysqlclient_pool_t::mysqlconnx_config_t  mconf;
    mconf.uname = config.db.uname.data;
    mconf.passwd = config.db.passwd.data;    
    mconf.ip = config.db.ip.data;
    mconf.port = config.db.port;
	mconf.dbname = config.db.dbname.data;
    if (mcp.init(mconf, config.thread_num)){
        return -1;
    }
    mysqlclient_t main_client;
    ret = main_client.init(mconf);
    if (ret){
        GLOG_ERR("mysql client init error :%d error info:%s", ret, main_client.err_msg());
        return  -2;
    }

    const char * otherfiles[16];
    int notherfiles = 0;
    for (notherfiles = 0; notherfiles < config.meta_files.count; ++notherfiles){
        otherfiles[notherfiles] = config.meta_files.list[notherfiles].data;
    }

    const char * paths[] = { config.meta_path.data };
    //main file
    MySQLMsgCvt	msc(config.meta_files.list[0].data, main_client.mysql_handle());
    ret = msc.InitMeta(1, (const char **)paths, notherfiles - 1, (const char **)(otherfiles + 1));
    if (ret){
        cerr << "init schama error ! ret:" << ret << endl;
        return -11;
    }
    g_ctx.converter = &msc;

    dcnode_config_t dconf;	
	string listenaddr = "pull:";
	listenaddr += config.listen.data;
	dconf.addr = listenaddr;
	dconf.name = "pborm";
	dconf.max_children_heart_beat_expired = 5;
    dcnode_t * dc = dcnode_create(dconf);
    if (!dc){
        GLOG_ERR("dcnode create error !");
        return -2;
    }
    g_ctx.dc = dc;
    g_ctx.mysql = &mcp;
    dcnode_set_dispatcher(dc, orm_msg_dispatcher, &g_ctx);
    while (true){
        dcnode_update(dc, 5000);//5ms
        mcp.poll();
        main_client.ping();
    }
    return 0;
}







