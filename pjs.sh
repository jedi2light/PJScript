#!/usr/bin/env bash

# Script which is useful for debugging or for new users :)

if [ ! -f $1 ]; then echo "No source is given"; exit 1; fi

mkdir -p runtime/cxx/build  # create cmake build directory

cd ./runtime/cxx/build && cmake .. && make && cd ../../../

./pjs.py --cgen-mode $1 && ./pjs.py --mk-binary $1 && \
 LD_LIBRARY_PATH=runtime/cxx/build "$(dirname $1)/program"