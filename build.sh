#!/bin/sh

for BUILD_TYPE in Debug Release; do
    mkdir -p $BUILD_TYPE
    ( cd $BUILD_TYPE ; CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE .. && make -k "$@" && make test "$@") || exit 1
done
