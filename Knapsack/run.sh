#!/bin/bash

mkdir -p build
g++ -std=c++17 -Iinclude -o build/main src/*.cpp && \
./build/main
