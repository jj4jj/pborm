PROJECT='pborm'
VERSION='0.0.1'
DEBUG = 1    #0/1
DEFS = []
VERBOSE = 'on'    #on/off
EXTRA_C_FLAGS = ''
EXTRA_CXX_FLAGS = '-std=c++11'
EXTRA_LD_FLAGS = '-ldl -lm -lrt -pthread'
LIBS = [
         {
            'name':'pborm_api',
            'subdir':'api',
            'includes':['/usr/local/include','..'],
            'linkpaths':[],
            'src_dirs': ['orm/proto'],
            'genobj': {
                'out':'${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc',
                'dep':'${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.proto',
                'cmd':'cd ${CMAKE_CURRENT_SOURCE_DIR}/../orm && make'
            }
        },
]
EXES = [
        {
            'name':'pborm',
            'subdir':'orm',
            'includes':['/usr/local/include','..','../pbdcex/include','../pbdcex/include'],
            'linkpaths':['../dcpots/lib','../pbdcex/lib'],
            'src_dirs': ['orm/proto'],
            'extra_srcs': [''],
            'linklibs' : [
                'dcbase',
                'dcnode',
                'dcutil-mysql',
                'pbdcex',
                'libprotobuf.a',
                'mysqlclient',
            ],
            'genobj': {
                'out':'${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.pb.cc',
                'dep':'${CMAKE_CURRENT_SOURCE_DIR}/../orm/proto/pborm.proto',
                'cmd':'cd ${CMAKE_CURRENT_SOURCE_DIR}/../orm && make'
            }

        },
        {
            'name':'testapi',
            'subdir':'testapi',
            'includes':['/usr/local/include','..'],
            'linkpaths':['../dcpots/lib'],
            'src_dirs': ['orm/proto'],
            'extra_srcs': [''],
            'linklibs' : [
                'dcbase',
                'dcnode',
                'pborm_api',
                'dcutil-mysql',
                'libprotobuf.a',
                'mysqlclient',
            ]
        }
]
