#!/bin/bash
if [[ ! -d 3rd/hpbex ]];then
    cd 3rd && git clone  https://github.com/jj4jj/hpbex.git
fi
if [[ ! -d 3rd/dcpots ]];then
    cd 3rd && git clone https://github.com/jj4jj/dcpots.git
fi

cd 3rd/dcpots/tools/cmaketools/ && python generate.py ../../../../cmake_conf && cd -
mkdir -p build
cd build && cmake ../ && cd -
cd build && make && cd -


