#!/bin/bash -xe
script_dir=$(pwd)
echo "Script dir: ${script_dir}"
cmake_root_dir="${script_dir}/../"

cd $cmake_root_dir && cmake --preset $1 
cmake --build --preset $1
