#!/bin/bash

set -e -x

rm -rf tensorflow_test

g++ -std=c++11 -o tensorflow_test \
                ./src/test/test_tensorflow.cpp \
                ./src/tfmodel/tfmodel.cc \
                -g -Wall -D_DEBUG -Wshadow -Wno-sign-compare -w -Xlinker -export-dynamic \
                -I../tensorflow/ \
                -I./include/tfmodel/ \
                -I./include/utils/ \
                -I./include/base/ \
                -I./third_party/gflags/include/ \
                -I./third_party/glog/include/ \
                -I/home/sunxx/soft/boost/include/ \
                -I/usr/include/python2.7/ \
                -I../tensorflow/tensorflow/contrib/makefile/gen/proto \
                -I../tensorflow/tensorflow/contrib/makefile/downloads/eigen \
                -I../tensorflow/tensorflow/contrib/makefile/downloads/absl/ \
                -I../tensorflow/tensorflow/contrib/makefile/gen/protobuf/include \
                -I../tensorflow/tensorflow/contrib/makefile/downloads/nsync/public/ \
                -L../tensorflow/bazel-bin/tensorflow -ltensorflow_cc \
                -L../tensorflow/bazel-bin/tensorflow -ltensorflow_framework \
                -L./third_party/gflags/lib -lgflags \
                -L./third_party/gflags/lib -lgflags_nothreads \
                -L./third_party/glog/lib -lglog \
                -L/home/sunxx/soft/boost/lib -lboost_system \
                -L/usr/lib64 -lpython2.7 \
                -lm \
                -ldl \
                -lpthread \

