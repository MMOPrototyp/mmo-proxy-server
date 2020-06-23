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

Windows VCPKG package installation
```shell script
./vcpkg install fmt
./vcpkg install folly
./vcpkg install fizz
./vcpkg install wangle
```

VCPKG (windows only):

  - https://developerpaul123.github.io/c++/cmake/using-vcpkg-on-windows/
  - https://www.jetbrains.com/help/clion/cmake-profile.html
  
Old CMake options:
```shell script
-DCMAKE_TOOLCHAIN_FILE=C:/Users/Justin/.../vcpkg/scripts/buildsystems/vcpkg.cmake
-DCMAKE_GENERATOR_PLATFORM=x64
-VCPKG_TARGET_TRIPLET=x64
-A
x64
```

New CMake Options:
```shell script
-DCMAKE_TOOLCHAIN_FILE=C:/Users/Justin/.../vcpkg/scripts/buildsystems/vcpkg.cmake
```

## Build config4cpp

https://docs.microsoft.com/de-de/dotnet/framework/tools/developer-command-prompt-for-vs

Windows: Open "Developer Command Prompt for VS 2019"
Linux: Open shell

```shell script
cd 3rdparty/config4cpp

# Windows
nmake -f Makeile.win

#Linux
make
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