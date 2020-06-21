# mmo-proxy-server

Branch|Status
---|---
master|[![Build Status](https://travis-ci.org/MMOPrototyp/mmo-proxy-server.svg?branch=master)](https://travis-ci.org/MMOPrototyp/mmo-proxy-server)
develop|[![Build Status](https://travis-ci.org/MMOPrototyp/mmo-proxy-server.svg?branch=develop)](https://travis-ci.org/MMOPrototyp/mmo-proxy-server)

A proxy server for the MMO prototyp, written in C++

## Build

https://docs.conan.io/en/latest/getting_started.html

```bash
sudo chmod 755 build.sh
./build.sh
```

To install dependencies:
```shell script
sudo apt-get install \
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
```

## Install Redis Client Library

https://github.com/cpp-redis/cpp_redis/wiki/Mac-&-Linux-Install

https://github.com/maurodelazeri/conan-cpp_redis

```
conan create .
```

## Create conan cmake files

```shell script
cd build
conan install .. --profile=cygwin
```

## Redis Client

Path: `3rdparty/redis-cpp`

## Git Submodules

https://git-scm.com/book/en/v2/Git-Tools-Submodules

## Conan

```shell script
conan remote add conan-radalytica https://api.bintray.com/conan/rd/conan-radalytica
```

## Links

  - https://github.com/nothings/single_file_libs

## Special thanks

Special thanks to @Nostritius for his great help with cmake and his great patience. Thank you very much!