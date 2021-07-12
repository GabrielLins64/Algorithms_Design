#!/bin/bash

DATAPATH="inputs/in.txt"

mkdir -p bin
g++ -std=c++17 -o bin/main src/*.cpp -Iinclude && \
./bin/main < $DATAPATH
