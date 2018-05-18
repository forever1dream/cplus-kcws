#!/bin/bash

set -e -x

cd tensor_decode
tar -xvf models.tar.gz
cd ..

cd third_party/

cd glog/glog-0.3.4
./configure --prefix $(pwd)
make clean;make install
mv include ../
mv lib ../
cd ../../

cd gflags/gflags-2.0
./configure --prefix $(pwd)
make clean;make install
mv include ../
mv lib ../
cd ../../

