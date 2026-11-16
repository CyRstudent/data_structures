#!/bin/bash

# Exit immediately if any command returns a non-zero exit code
set -e

# Always start from the directory where this script is located
cd "$(dirname "$0")"

# Clean and recreate build directory
rm -rf build
mkdir build
cd build

# Configure and compile
cmake ..
cmake --build .

./data_structures_c &> ../res.txt
