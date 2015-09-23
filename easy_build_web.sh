#!/bin/bash
source ~/emscripten/emsdk_portable/emsdk_env.sh

make clean
emmake make main.html CXXFLAGS="-std=c++11 -Os -s USE_SDL=2" LDFLAGS="-s USE_SDL=2"
firefox main.html

