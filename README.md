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

## Git Submodules

https://git-scm.com/book/en/v2/Git-Tools-Submodules