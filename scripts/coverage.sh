#!/bin/bash

ROOT_DIR="$(pwd)"
echo "ROOT_DIR: $ROOT_DIR"

mkdir -p build/coverage
cd build/ut

find . -type f \( -name "*.gcda" -o -name "*.gcov" \) -delete
rm -rf "$ROOT_DIR/build/ut/main/app/CMakeFiles/BasicGUI.dir/src"
ctest --output-on-failure

gcovr -r  "$ROOT_DIR" \
        --filter "$ROOT_DIR/main/.*\.cpp$"\
        --filter "$ROOT_DIR/main/.*\.hpp$"\
        --exclude "$ROOT_DIR/main/app/source/main\.cpp$" \
        --print-summary \
        --html --html-details -o $ROOT_DIR/build/coverage/coverage.html