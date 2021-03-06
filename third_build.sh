#!/bin/bash

set -e -x

cd kcws
tar -xvf models.tar.gz
cd ..

cd third_party/

cd glog/glog-0.3.4
./configure --prefix $(pwd)
make clean;make install
mv include ../
mv lib ../
cd ..
cd lib 
rm -rf *.so*
cd ../../

cd gflags/gflags-2.0
./configure --prefix $(pwd)
make clean;make install
mv include ../
mv lib ../
cd ..
cd lib 
rm -rf *.so*
cd ../../

