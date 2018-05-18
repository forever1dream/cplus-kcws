#!/bin/bash

set -e -x

模型训练参考项目：https://github.com/koth/kcws.git

该项目为 上面项目 的另一种编译方式

注意：修改build.sh 脚本中tensorflow 以及 boost的路径为自己的安装路径

first run : third_build.sh

second run : build.sh

third : ./seg_backend_api


项目准备工作:

#1、安装centos7系统之后 安装下面的系统工具
#rm -f /var/run/yum.pid
yum install vim  
yum install gcc-c++
yum install git

#2、安装 tensorflow 需要的依赖
#yum install python-devel
#yum install numpy
#yum install automake
#yum install libtool  
#yum install libsysfs
#yum install zlib-devel
#首先安装epel扩展源：
#yum -y install epel-release
#然后再安装pip
#yum -y install python-pip
#pip install wheel
#pip install --upgrade pip
#pip install wheel

#3、获取 tensorflow
git clone --recursive https://github.com/tensorflow/tensorflow

#4、编译 so 库
#C版本：
#bazel build :libtensorflow.so
#C++版本：
#bazel build :libtensorflow_cc.so
#编译成功后，在bazel-bin/tensorflow/目录下会出现libtensorflow.so/libtensorflow_cc.so文件
#2.其他依赖
#在使用tensorflow c/c++接口时，会有很多头文件依赖、protobuf版本依赖等问题
#（1）tensorflow/contrib/makefile目录下，找到build_all_xxx.sh文件并执行，
#   例如准备在linux上使用，就执行build_all_linux.sh文件，成功后会出现一个gen文件夹
#（2）把tensorflow和bazel-genfiles文件夹下的头文件都抽取出来放在一个文件夹下面，
#   或者通过cmake把这两个路径添加进include_directories中
#（3）tensorflow/contrib/makefile/gen/protobuf/include，也就是（1）中生成的文件夹中的头文件，
#   也需要抽取或者在cmake中包含在include_directories中
bazel build //tensorflow:libtensorflow_cc.so

#5、编译 C++所需的依赖库
cd tensorflow/contrib/makefile
sh build_all_linux.sh

#6、编译 pip_package
bazel build -c opt //tensorflow/tools/pip_package:build_pip_package
bazel build -c opt --copt=-msse4 //tensorflow/tools/pip_package:build_pip_package

#7、生成 python 的 pip安装包
bazel-bin/tensorflow/tools/pip_package/build_pip_package ./tmp/tensorflow_pkg

#8、安装到系统中 .whl 文件的实际名字与你所使用的平台有关
pip install /tmp/tensorflow_pkg/tensorflow-0.5.0-cp27-none-linux_x86_64.whl

#9、C++ 调用模型解码测试
#https://github.com/koth/kcws
#git clone https://github.com/koth/kcws.git 
#python 模型训练 参考 该项目
