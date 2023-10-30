#/usr/bin/env bash

set -e

function info {
    echo -e "\e[1;32m[INFO]\e[0m $1"
}

function warning {
    echo -e "\e[1;33m[WARNING]\e[0m $1"
}

function error {
    echo -e "\e[1;31m[ERROR]\e[0m $1"
}

function fatal {
    echo -e "\e[1;31m[FATAL]\e[0m ** $1 **"
    exit 1
}

set -e

info "Building test app"

mkdir -p build
cd build

cmake ..
make
