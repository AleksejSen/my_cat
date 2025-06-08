#!/bin/bash

set -e

conan install . --output-folder=build --build=missing -pr:b=debug -pr:h=debug
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
cmake --build build
