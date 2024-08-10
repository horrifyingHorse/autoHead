#!/bin/bash

currentDir=$(pwd)

echo "create & cd /build directory"
mkdir "$currentDir/build"
cd "$currentDir/build"

echo "initiating cmake"
cmake ..

# defualt project is autoHead
echo "build cmake 'autoHead'"
cmake --build . --target autoHead

echo "reset cd"
cd "../"

echo ""
echo ""

# run the built project
./build/autoHead
