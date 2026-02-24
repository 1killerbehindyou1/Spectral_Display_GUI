#!/bin/bash

ROOT_DIR="$(pwd)"
echo "ROOT_DIR: $ROOT_DIR"

mkdir -p build/coverage
cd build/ut
ctest --output-on-failure

gcovr -r  "$ROOT_DIR" \
        --filter "$ROOT_DIR/main/.*\.cpp$"\
        --filter "$ROOT_DIR/main/.*\.hpp$"\
        --print-summary \
        --html --html-details -o $ROOT_DIR/build/coverage/coverage.html