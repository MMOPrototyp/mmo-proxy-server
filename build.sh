#!/bin/bash

mkdir build
cd build
conan install ..

cd ../
cmake .
make

chmod -R 777 bin