#!/bin/bash

cp src/server.cpp example/.
cp src/server.hpp example/.
cp src/handlers.cpp example/.
cp src/handlers.hpp example/.


rm -rf build
mkdir build
cd build
cmake ..
make

cd build/example
cp ../../config.json .
