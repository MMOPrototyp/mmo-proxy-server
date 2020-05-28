#!/bin/bash

# see also: https://stackoverflow.com/questions/1125968/how-do-i-force-git-pull-to-overwrite-local-files

# see also: https://unix.stackexchange.com/questions/510744/conan-command-not-found

git submodule init && git submodule update

cd 3rdparty/cpp_redis
git submodule init && git submodule update
cmake .
cd ../

cd 3rdparty/config4cpp
git submodule init && git submodule update
make
cd ../

mkdir build
cd build
conan install ..

cd ../

make RedisCPP

cmake .
make

chmod -R 777 bin