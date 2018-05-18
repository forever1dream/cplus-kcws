#!/bin/bash

set -e -x

g++ -std=c++11 -o seg_backend_api ./tensor_decode/cc/seg_backend_api.cc \
			  ./tensor_decode/cc/pos_tagger.cc ./tensor_decode/cc/sentence_breaker.cc ./tensor_decode/cc/tf_seg_model.cc ./tensor_decode/cc/viterbi_decode.cc \
			  ./utils/basic_vocab.cc ./utils/jsonxx.cc ./utils/py_word2vec_vob.cc ./utils/word2vec_vob.cc \
			  ./tfmodel/tfmodel.cc \
			  -g -Wall -D_DEBUG -Wshadow -Wno-sign-compare -w -Xlinker -export-dynamic \
			  -I../tensorflow/ \
			  -I./kcws/cc/ \
			  -I./utils/ \
			  -I./tfmodel/ \
			  -I./third_party/gflags/include/ \
			  -I./third_party/glog/include/ \
			  -I/home/sunxx/soft/boost/include/ \
			  -I/usr/include/python2.7/ \
			  -I../tensorflow/tensorflow/contrib/makefile/gen/proto \
			  -I../tensorflow/tensorflow/contrib/makefile/downloads/eigen \
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

