#!/bin/bash
if [[ ! -d ../dcpots ]];then
    cd .. && git clone https://github.com/jj4jj/dcpots.git
fi
if [[ ! -d ../pbdcex ]];then
    cd .. && git clone https://github.com/jj4jj/pbdcex.git
fi

python ../dcpots/tools/cmaketools/generate.py cmake_conf && cd -
mkdir -p build
cd build && cmake ../ && cd -
cd build && make && cd -


