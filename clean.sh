#!/bin/bash

set -e -x

rm -rf seg_backend_api
rm -rf tensorflow_test

rm -rf kcws/models

cd third_party/

cd glog
rm -rf include lib
cd glog-0.3.4
make clean;
cd ..
cd ..

cd gflags
rm -rf include lib
cd gflags-2.0
make clean;
cd ..
cd ..

