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
            'includes':['/usr/local/include','3rd/dcpots'],
            'linkpaths':[],
            'src_dirs': ['orm/proto'],
        },
]
EXES = [
        {
            'name':'pborm',
            'subdir':'orm',
            'includes':['/usr/local/include','3rd/dcpots','3rd/hpbex'],
            'linkpaths':['3rd/dcpots/lib'],
            'src_dirs': ['orm/proto'],
            'extra_srcs': ['3rd/hpbex/ext_meta.cpp','3rd/hpbex/mysql_gen.cpp','3rd/hpbex/extensions_option.cpp'],
            'linklibs' : [
                'dcnode',
                'dcutil',
                'libprotobuf.a',
                'mysqlclient',
            ]
        },
        {
            'name':'testapi',
            'subdir':'testapi',
            'includes':['/usr/local/include','3rd/dcpots'],
            'linkpaths':['3rd/dcpots/lib'],
            'src_dirs': [],
            'linklibs' : [
                'pborm_api',
                'dcnode',
                'libprotobuf.a',
            ]
        }
]
