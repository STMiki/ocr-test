#/usr/bin/env bash

set -e

source utils.sh

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

info "Installing dependencies"
sudo apt install $PACKAGES -y

info "Installing test app"
if [ ! -d "ocr-test" ]; then
    git clone https://github.com/STMiki/ocr-test.git
fi

info "Done"
