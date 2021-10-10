#!/bin/bash

rm -rf ./build
cmake -H. -Bbuild -G "Ninja" -DBUILD_GMOCK=ON
cmake --build build
cd build && ctest && cd ..
