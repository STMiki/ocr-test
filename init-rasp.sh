#/usr/bin/env bash

set -e

TESSDATA_PREFIX=/usr/share/tesseract-ocr/5/tessdata
PACKAGES="          xorg-dev"
PACKAGES="$PACKAGES libudev-dev"
PACKAGES="$PACKAGES cmake"
PACKAGES="$PACKAGES clang"
PACKAGES="$PACKAGES vim"
PACKAGES="$PACKAGES git"
PACKAGES="$PACKAGES libopenal-dev"
PACKAGES="$PACKAGES libvorbis-dev"
PACKAGES="$PACKAGES libflac-dev"
PACKAGES="$PACKAGES libsfml-dev"
PACKAGES="$PACKAGES libtesseract-dev"
PACKAGES="$PACKAGES tesseract-ocr"
PACKAGES="$PACKAGES tesseract-ocr-eng"
PACKAGES="$PACKAGES tesseract-ocr-fra"

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

info "Installing dependencies"
sudo apt install $PACKAGES -y

info "Installing test app"
if [ -d "ocr-test" ]; then
    warning "Removing old test app"
    rm -rf ocr-test
fi
git clone https://github.com/STMiki/ocr-test.git
cd ocr-test
mkdir -p build
cd build

info "Building test app"
cmake ..
make

info "Running test app"
DISPLAY=:0 ./OcrTest

info "Done"
