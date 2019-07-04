#!/bin/bash

set -e -x

g++ -std=c++11 -o seg_backend_api \
                ./src/kcws/seg_backend_api.cc \
                ./src/kcws/pos_tagger.cc \
                ./src/kcws/sentence_breaker.cc \
                ./src/kcws/tf_seg_model.cc \
                ./src/kcws/viterbi_decode.cc \
                ./src/utils/basic_vocab.cc \
                ./src/utils/jsonxx.cc \
                ./src/utils/py_word2vec_vob.cc \
                ./src/utils/word2vec_vob.cc \
                ./src/tfmodel/tfmodel.cc \
                -g -Wall -D_DEBUG -Wshadow -Wno-sign-compare -w -Xlinker -export-dynamic \
                -I../tensorflow/ \
                -I./include/ \
                -I./include/kcws/ \
                -I./include/utils/ \
                -I./include/tfmodel/ \
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

