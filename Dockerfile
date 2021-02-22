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

# Installing Boost C++ Library
RUN cd /tmp && wget http://downloads.sourceforge.net/project/boost/boost/1.75.0/boost_1_75_0.tar.gz \
  && tar xfz boost_1_75_0.tar.gz \
  && rm boost_1_75_0.tar.gz \
  && cd boost_1_75_0 \
  && ./bootstrap.sh --prefix=/usr/local --with-libraries=serialization,json \
  && ./b2 install \
  && cd /tmp \
  && rm -rf boost_1_75_0

# Installing Google Protobuf Library
RUN apt-get install -y autoconf automake libtool curl make g++ unzip
RUN cd && git clone https://github.com/protocolbuffers/protobuf.git \
    && cd protobuf \
    && git submodule update --init --recursive \
    && ./autogen.sh \
    && ./configure \
    && make \
    && make check \
    && make install \
    && ldconfig

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