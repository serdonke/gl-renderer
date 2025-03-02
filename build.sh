#!/bin/bash
set -e
if [ ! -d "build" ]; then
    mkdir build
fi
cmake -B build
cmake --build build --parallel
if [ $? -eq 0 ]; then
    if [ -n "$1" ] && [ -x "build/$1" ]; then
        ./build/$1
    else
        printf "\n\nTo run examples: ./build.sh [NAME]\n"
        echo "Available options:"
        find build -maxdepth 1 -type f -executable -printf "\033[32m%f\033[0m\n"
    fi
else
    exit 1
fi

