#!/bin/bash

cp src/server.cpp example/.
cp src/server.hpp example/.
rm -rf build
mkdir build
cd build
cmake ..
make
sudo make install
cd build/example
