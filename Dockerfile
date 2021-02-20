FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y git nano wget

# setting timezone to avoid input lock while building
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# instaliing GCC with CMake and Make
RUN apt-get install -y build-essential cmake make

# Download Boost C++ Library, untar, setup install with bootstrap and only build needed libraries
# and then install
RUN cd /tmp && wget http://downloads.sourceforge.net/project/boost/boost/1.75.0/boost_1_75_0.tar.gz \
  && tar xfz boost_1_75_0.tar.gz \
  && rm boost_1_75_0.tar.gz \
  && cd boost_1_75_0 \
  && ./bootstrap.sh --prefix=/usr/local --with-libraries=serialization,json \
  && ./b2 install \
  && cd /tmp \
  && rm -rf boost_1_75_0

WORKDIR /usr/src/app

# a folder for developing via adding volumes of host project folder to dev/
RUN mkdir dev

RUN git clone https://github.com/jellythefish/cpp_serialization_methods \
  && cd cpp_serialization_methods \
  && git checkout develop

# Build and run
RUN cd cpp_serialization_methods \
  && mkdir build \
  && cd build \
  && cmake .. \
  && make
WORKDIR /usr/src/app/cpp_serialization_methods/build
CMD ["./serialization"]