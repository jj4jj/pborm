#include "base/logger.h"
#include "dcnode/dcnode.h"
#include "utility/util_mysql_pool.h"
#include "utility/util_proto.h"
#include "base/cmdline_opt.h"
#include "base/msg_buffer.hpp"
#include "proto/pborm_conf.hpb.h"
#include "mysql_gen.h"
#include "pborm_msg.h"


#define MAJOR_VERSION   0
#define MINOR_VERSION   1
#define PATCH_VERSION   1

using namespace dcsutil;
using namespace pborm;
using namespace google::protobuf;
using namespace std;

static struct {
    dcnode_t            * dc;
    mysqlclient_pool_t  * mysql;
    MySQLMsgCvt         * converter;
    msg_buffer_t          msgbuff;
} g_ctx;

static int 
response_error_msg(dcnode_t *dc, int ret, const mysqlclient_pool_t::command_t & cmd){
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
    }
    return dcnode_send(g_ctx.dc, cmd.src.c_str(), g_ctx.msgbuff.buffer, g_ctx.msgbuff.valid_size);
}


static void
orm_msg_fetch_result(void *ud, const mysqlclient_pool_t::result_t & result,
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
    if (result.status){
        rsp->set_err_no(result.err_no);
        rsp->set_err_msg(result.error);
    }
    else {
        rsp->set_count(result.affects);
        if (cmd.need_result){
            OrmMsgRspSelect * select = rsp->mutable_select();
            select->set_total(result.fetched_results.size());
            auto msg_desc = g_ctx.converter->GetProtoMeta().GetMsgDesc(cmd.full_msg_type_name.c_str());
            if (!msg_desc){
                rsp->set_err_no(-1);
                rsp->set_err_msg("not found the msg desc !");
            }
            MySQLRow sqlrow;
            mysqlclient_t::table_row_t tbrow;
            sqlrow.table_name = msg_desc->name().c_str();
            for (size_t i = 0; i < result.fetched_results.size(); ++i){
                g_ctx.msgbuff.valid_size = g_ctx.msgbuff.max_size;
                auto & row = result.fetched_results[i];
                result.alloc_mysql_row_converted(tbrow, i);

                sqlrow.fields_name = tbrow.fields_name;
                sqlrow.num_fields = tbrow.fields_count;
                sqlrow.row_data = tbrow.row_data;
                sqlrow.row_lengths = tbrow.row_length;
                ret = g_ctx.converter->GetMsgBufferFromSQLRow(g_ctx.msgbuff.buffer,
                    &g_ctx.msgbuff.valid_size, sqlrow, cmd.flatmode);
                result.free_mysql_row(tbrow);
                if (ret){
                    GLOG_ERR("convert get msg :%s error !", cmd.full_msg_type_name.c_str());
                    rsp->set_err_no(-1);
                    rsp->set_err_msg("get msg buffer from sql row error !");
                    break;
                }
                select->add_msgs(g_ctx.msgbuff.buffer, g_ctx.msgbuff.valid_size);
            }
        }
    }
    if (!msg.Pack(g_ctx.msgbuff)){
        GLOG_ERR("msg pack error ! msg:%s", cmd.full_msg_type_name.c_str());
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
    Message * newmsg = nullptr;
    int ret = -1;
    mysqlclient_pool_t::command_t   cmd;
    cmd.cbdata.copy(orm_msg.cb().data().data(), orm_msg.cb().data().length());
    cmd.opaque = orm_msg.op();
    cmd.full_msg_type_name = orm_msg.msg_full_type_name();
    cmd.src = src;
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
            GLOG_ERR("check msg:%s valid error :%s", orm_msg.msg_full_type_name().c_str());
            ret = -3;
            break;
        }
        MySQLMsgMeta msgen(g_ctx.converter);
        if (msgen.AttachMsg(newmsg)){
            GLOG_ERR("attach msg:%s valid error :%s", orm_msg.msg_full_type_name().c_str());
            ret = -4;
            break;
        }
        ///////////////////////////////////////////////////////////////////////
        bool flatmode = false;
        switch (orm_msg.op()){
        case ORM_INSERT:
            ret = msgen.Insert(cmd.sql);
            break;
        case ORM_DELETE:
            ret = msgen.Delete(cmd.sql, nullptr, flatmode);
            break;
        case ORM_SELECT:
            msgen.Select(cmd.sql, nullptr, nullptr, flatmode);
            break;
        case ORM_UPDATE:
            msgen.Update(cmd.sql, flatmode);
            break;
        case ORM_COUNT:
            //msgen.Count(cmd.sql)
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
        return response_error_msg(g_ctx.dc, ret, cmd);
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
    if (argc < 2){
        cmdline.pusage();
        return -1;
    }
    if (cmdline.hasopt("g")){
        const pborm::Config &  conf = pborm::Config::default_instance();
        dcsutil::protobuf_saveto_xml(conf, "pborm.default.xml");
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
    int ret = protobuf_readfrom_xml(xmlconfig, confile, error);
    if (ret){
        cerr << "read config file error !" << endl;
        return -2;
    }
    cout << "config file " << endl;
    cout << xmlconfig.ShortDebugString() << endl;
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
    
    //->dcnode
    //->mysql
    mysqlclient_pool_t  mcp;
    mysqlclient_pool_t::mysqlconnx_config_t  mconf;
    mconf.uname = config.db.uname.data;
    mconf.passwd = config.db.passwd.data;    
    if (mcp.init(mconf)){
        GLOG_ERR("mysql client create error !");
        return -1;
    }

    MySQLMsgCvt	msc(config.meta_path.data, (st_mysql*)mcp.mysqlhandle());
    ret = msc.InitMeta();
    if (ret){
        cerr << "init schama error ! ret:" << ret << endl;
        return -11;
    }
    g_ctx.converter = &msc;

    dcnode_config_t dconf;
    dconf.addr = dcnode_addr_t(config.listen.data);
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
    }
    return 0;
}







