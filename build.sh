#!/bin/bash

# see also: https://stackoverflow.com/questions/1125968/how-do-i-force-git-pull-to-overwrite-local-files

# see also: https://unix.stackexchange.com/questions/510744/conan-command-not-found

git submodule init && git submodule update

cd 3rdparty/cpp_redis
git submodule init && git submodule update
cmake .
cd ../../

cd 3rdparty/config4cpp
git submodule init && git submodule update
make CDBG=-w
cd ../../

cd 3rdparty/evpp
git submodule init && git submodule update
git submodule update --init --recursive

echo "Compile and run unit tests"
mkdir -p build && cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make -j
$ make test

cd ../../

mkdir build
cd build
conan install ..

cd ../

make RedisCPP

cmake .
make

chmod -R 777 bin

# copy executable to other directory, || true for travis ci build (where these directories does not exists)
cd ../
mkdir config || true
mkdir bin || true
mkdir bin/config || true
cp -R config/* bin/config || true
cp -R mmo-proxy-server/bin/* bin || true