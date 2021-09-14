FROM ubuntu:21.04

ENV DEBIAN_FRONTEND=noninteractive
SHELL ["/bin/bash", "-c"]


RUN apt-get -qq update -y && \
    apt-get -qq upgrade -y && \
    apt-get -qq install -y apt-utils wget git g++-10 libstdc++-10-dev

RUN apt-get -y install \
    g++ \
    cmake \
    libboost-all-dev \
    libevent-dev \
    libdouble-conversion-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libiberty-dev \
    liblz4-dev \
    liblzma-dev \
    libsnappy-dev \
    make \
    zlib1g-dev \
    binutils-dev \
    libjemalloc-dev \
    libssl-dev \
    pkg-config \
    libunwind-dev

RUN apt-get -y install \
    libunwind8-dev \
    libelf-dev \
    libdwarf-dev

ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8

RUN cd /tmp && git clone https://github.com/fmtlib/fmt.git && cd fmt && mkdir _build && cd _build && cmake .. && make -j4 && make install

RUN mkdir -p /tmp/folly && cd /tmp/folly && wget https://github.com/facebook/folly/releases/download/v2021.09.13.00/folly-v2021.09.13.00.tar.gz && tar -zxvf folly-v2021.09.13.00.tar.gz && mkdir _build && cd _build && cmake .. && make -j15 && make install

RUN apt-get -y install libgtest-dev

WORKDIR /
