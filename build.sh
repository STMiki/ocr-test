#/usr/bin/env bash

set -e

info "Building test app"

mkdir -p build
cd build

cmake ..
make
