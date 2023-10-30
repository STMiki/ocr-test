#/usr/bin/env bash

set -e

TESSDATA_PREFIX=/usr/share/tesseract-ocr/5/tessdata

function info {
    echo -e "\e[1;32m[INFO]\e[0m $1"
}

function error {
    echo -e "\e[1;31m[ERROR]\e[0m $1"
}

function warning {
    echo -e "\e[1;33m[WARNING]\e[0m $1"
}

function installLanguage {
    if [ ! -f "/usr/share/tessdata/$1.traineddata" ]; then
        info "Installing $1 language"
        sudo wget https://github.com/tesseract-ocr/tessdata/raw/main/$1.traineddata -qO $TESSDATA_PREFIX/$1.traineddata
    fi
}

info "** Installing dependencies"
sudo apt install xorg-dev libudev-dev cmake clang libtesseract-dev vim git libopenal-dev libvorbis-dev libflac-dev libsfml-dev -y

installLanguage eng
installLanguage fra

info "** Installing test app"
if [ -d "ocr-test" ]; then
    warning "Removing old test app"
    rm -rf ocr-test
fi
git clone https://github.com/STMiki/ocr-test.git
cd ocr-test
mkdir -p build
cd build

info "** Building test app"
cmake ..
make

info "** Running test app"
DISPLAY=:0 ./OcrTest

info "** Done"
