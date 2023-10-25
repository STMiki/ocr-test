#/usr/bin/env bash

set -e

echo "Installing dependencies"
sudo apt install xorg-dev libudev-dev cmake clang libtesseract-dev vim git libopenal-dev libvorbis-dev libflac-dev libsfml-dev -y

echo "Installing test app"
git clone https://github.com/STMiki/ocr-test.git
cd ocr-test
mkdir -p build
cd build

echo "Building test app"
cmake ..
make

echo "Running test app"
./ocr-test

echo "Done"
