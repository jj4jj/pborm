#include "base/stdinc.h"
#include "api/pborm_api.h"
#include "base/cmdline_opt.h"
#include "mysql_gen.h"
#include "orm/proto/db.pb.h"
#include "orm/proto/db.hpb.h"
#include "utility/util_proto.h"
#include "base/logger.h"

using namespace test;
using namespace std;



////////////////////////////////for test
#include "utility/util_mysql.h"
using namespace dcsutil;


static void 
receive_result(void *ud, const pborm_result_t & result){
	GLOG_TRA("receive msg ");
}

int main(int argc, char ** argv){

	global_logger_init(logger_config_t());
	protobuf_logger_init();


	cmdline_opt_t	cmdline(argc, argv);
	cmdline.parse("pborm:r::pborm server address:tcp://127.0.0.1:8888;"
					"init:n:i:init the db test env;"
					"user:r:u:mysql user name:gsgame;"
					"passwd:r:p:mysql password:gsgame");

	//msg meta
	DBTest		obj;
	DBTest_ST	sto;
	sto.construct();


	if (cmdline.hasopt("i") || cmdline.hasopt("init")){		
		//mysql handle
		mysqlclient_t	mysql;
		mysqlclient_t::cnnx_conf_t	conf;
		conf.ip = "127.0.0.1";
		conf.uname = cmdline.getoptstr("u");
		conf.passwd = cmdline.getoptstr("p");
		conf.port = 3306;
		conf.dbname = "test";

		if (mysql.init(conf)){
			GLOG_TRA("mysql init error !");
			return -1;
		}
		
		//mysql convert center 
		MySQLMsgCvt	msc("proto/db.proto", (st_mysql*) mysql.mysql_handle());
		const char * v = "./proto";
		int iret = msc.InitMeta(1, &v);
		if (iret){
			cerr << "init schama error ! ret:" << iret << endl;
			return -1;
		}

		MySQLMsgMeta hellogen(&msc);
		///////////////////////////////////////////////////////////////////////
		string sql;
		msc.CreateDB("test", sql);
		mysql.execute(sql);

		msc.CreateTables(obj.GetDescriptor()->name().c_str(), sql);
		mysql.execute(sql);

		cout << "init test db env ok !";
		return 0;
	}

	int ret = pborm_init(cmdline.getoptstr("pborm"));
	if (ret){
		GLOG_ERR("init pborm error!");
		return -1;
	}
	//set call back
	pborm_set_cb(receive_result, 0);

	int test_case = 0;
	while (true){
		pborm_poll(100000);//100ms
		/////////////////////////////////////
		switch (test_case){
		case 0:
			sto.role_id = rand() % 156777;
			sto.seq = 20;
			sto.convto(obj);
			ret = pborm_insert(obj, "hello,world", 11);
			break;
		case 1:
			ret = pborm_delete(obj, "hello,world", 11);
			break;
		case 2:
			sto.seq = 267;
			sto.convto(obj);
			ret = pborm_get(obj, "hello,world", 11);
			break;
		case 3:
			sto.seq = 577;
			sto.convto(obj);
			ret = pborm_update(obj, "hello,world", 11);
			break;
		case 4:
			sto.seq = 55;
			sto.convto(obj);
			ret = pborm_batch_get(obj, "1", 0, 10, 1, "hello,world", 11);
			break;
		}
		if (ret == 0){
			++test_case;
		}
	}
    return 0;
}