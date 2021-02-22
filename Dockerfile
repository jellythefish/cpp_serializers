FROM ubuntu:latest

# setting timezone to avoid input lock while building
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /usr/src/app

##############################################################################
# INSTALLING DEPENDENCIES
RUN apt-get update
RUN apt-get install -y git nano wget

# Installing GCC with CMake and Make
RUN apt-get install -y build-essential cmake make

# Installing Google Protobuf Library
RUN apt-get install -y autoconf automake libtool curl unzip
RUN cd /tmp && wget https://github.com/protocolbuffers/protobuf/releases/download/v3.15.1/protobuf-cpp-3.15.1.tar.gz \
    && tar xfz protobuf-cpp-3.15.1.tar.gz \
    && rm protobuf-cpp-3.15.1.tar.gz \
    && cd protobuf-3.15.1 \
    && ./configure \
    && make \
    && make check \
    && make install \
    && ldconfig \
    && cd /tmp \
    && rm -rf protobuf-3.15.1

# Installing Boost C++ Library
RUN apt-get -y install zlib1g zlib1g-dev libbz2-dev liblzma-dev libzstd-dev
RUN cd /tmp && wget http://downloads.sourceforge.net/project/boost/boost/1.75.0/boost_1_75_0.tar.gz \
  && tar xfz boost_1_75_0.tar.gz \
  && rm boost_1_75_0.tar.gz \
  && cd boost_1_75_0 \
  && ./bootstrap.sh --prefix=/usr/local --with-libraries=serialization,json,filesystem,iostreams,system,program_options,regex \
  && ./b2 install \
  && cd /tmp \
  && rm -rf boost_1_75_0

# Installing Apache Avro
# installing python as a needed dependency
RUN cd /tmp && wget https://www.python.org/ftp/python/3.7.8/Python-3.7.8.tar.xz \
    && tar xf Python-3.7.8.tar.xz \
    && rm Python-3.7.8.tar.xz \
    && cd Python-3.7.8 \
    && ./configure \
    && make \
    && make install \
    && cd /tmp \
    && rm -rf Python-3.7.8

RUN apt-get install -y libsnappy-dev pkg-config
RUN cd /tmp && wget https://apache-mirror.rbc.ru/pub/apache/avro/avro-1.10.1/avro-src-1.10.1.tar.gz \
    && tar xfz avro-src-1.10.1.tar.gz \
    && rm avro-src-1.10.1.tar.gz \
    && cd avro-src-1.10.1/lang/c++ \
    && ./build.sh test \
    && ./build.sh install \
    && cd /tmp \
    && rm -rf avro-src-1.10.1

##############################################################################

# A folder for developing and debbuging: for adding volume of sources in host project folder
RUN mkdir dev

# Getting sources of an application
RUN git clone https://github.com/jellythefish/cpp_serialization_methods \
  && cd cpp_serialization_methods \
  && git checkout develop

# Building and running
RUN cd cpp_serialization_methods \
  && mkdir build \
  && cd build \
  && cmake .. \
  && make
WORKDIR /usr/src/app/cpp_serialization_methods/build
CMD ["./serialization"]