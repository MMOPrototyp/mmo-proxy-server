# mmo-proxy-server
A proxy server for the MMO prototyp, written in C++

## Build

https://docs.conan.io/en/latest/getting_started.html

```bash
sudo chmod 755 build.sh
./build.sh
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

## Special thanks

Special thanks to @Nostritius for his great help with cmake and his great patience. Thank you very much!