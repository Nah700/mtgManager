#!/bin/bash

rm mtgManager
mkdir -p build
cd build/
cmake ..
cmake --build .
cd ..
