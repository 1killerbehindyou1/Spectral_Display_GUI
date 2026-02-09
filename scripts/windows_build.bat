@echo off
echo Preset: %1

cmake --preset %1
cmake --build --preset %1
