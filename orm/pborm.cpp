
#include "3rd/dcpots/base/logger.h"
#include "3rd/hpbex/mysql_gen.h"
#include "dcnode/dcnode.h"
#include "utility/util_mysql_pool.h"
#include "utility/util_proto.h"
#include "base/cmdline_opt.h"
#include "base/msg_buffer.hpp"
#include "proto/pborm_conf.hpb.h"

using namespace std;
#define MAJOR_VERSION   0
#define MINOR_VERSION   1
#define PATCH_VERSION   1

using namespace dcsutil;
int main(int argc, char ** argv){   
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
    pborm::Config config;
    string error;
    int ret = protobuf_readfrom_xml(config, confile, error);
    if (ret){
        cerr << "read config file error !" << endl;
        return -2;
    }
    cout << "config file " << endl;
    cout << config.ShortDebugString() << endl;
    pborm::Config_ST    confst;
    confst.convfrom(config);
    
    //->dcnode
    //->mysql
    mysqlclient_pool_t  mcp;
    mysqlclient_pool_t::mysqlconnx_config_t  mconf;
    mconf.uname = "gsgame";
    mconf.passwd = "gsgame";
    mconf.dbname = "";
    
    if (mcp.init(mconf)){

    }




    return 0;
}







