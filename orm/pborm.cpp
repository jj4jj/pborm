
#include "3rd/dcpots/base/logger.h"
#include "3rd/hpbex/mysql_gen.h"
#include "3rd/dcpots/base/msg_buffer.hpp"
#include "3rd/dcpots/dcnode/dcnode.h"
#include "3rd/dcpots/utility/util_mysql_pool.h"
#include "proto/pborm_conf.hpb.h"

using namespace std;
#define MAJOR_VERSION   0
#define MINOR_VERSION   1
#define PATCH_VERSION   1

int main(int argc, char ** argv){
    
    cmdline_opt_t   cmdline(argc, argv);
    cmdline.parse("config:r::config file:pborm.conf;version:n:v:show the version");
    if (cmdline.hasopt("version")){
        cout << MAJOR_VERSION << "." << MINOR_VERSION << "." << PATCH_VERSION << endl;
        return 0;
    }
    const char * confile = cmdline.getoptstr("config");
    if (!access(confile, R_OK)){
        cerr << "config file  :" << confile << " not exists !" << endl;
        return -1;
    }
    //->dcnode
    //->mysql
    mysqlclient_pool_t  mcp;
    mysqlclient_pool_t::mysqlconnx_config_t  mconf;

    std::string  ip;
    std::string  uname;
    std::string  passwd;
    std::string  dbname;
    std::string  unisock;
    std::string	 char_set;
    mconf.ip.
    mcp.init()




    return 0;
}







