#!/bin/bash
make clean
emmake make main.html CXXFLAGS="-s USE_SDL=2" LDFLAGS="-s USE_SDL=2"
firefox main.html

