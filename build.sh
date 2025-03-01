#!/bin/bash
set -e
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
cmake ..
cmake --build . --parallel
if [ $? -eq 0 ]; then
    ./main
else
    exit 1
fi

