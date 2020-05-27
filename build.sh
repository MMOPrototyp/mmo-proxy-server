#!/bin/bash

# see also: https://stackoverflow.com/questions/1125968/how-do-i-force-git-pull-to-overwrite-local-files

mkdir build
cd build
conan install ..

cd ../
cmake .
make

chmod -R 777 bin