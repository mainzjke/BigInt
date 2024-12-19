#!/bin/bash

if ! -d "include"; then
    mkdir include
fi

cd include
ln -s ../src/BigInt/bigint.h

cd ..

if ! -d "build"; then
    mkdir build
fi

cd build
cmake .. && make -j5
