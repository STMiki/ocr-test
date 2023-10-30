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

IMAGE_NAME="ocr-test.png"
IMAGE_PATH="/usr/local/share/$IMAGE_NAME"
IMAGE_URL="https://en.wikipedia.org/wiki/File:Schlegel_wireframe_8-cell.png"

EXECUTABLE="ocr-test"
EXECUTABLE_PATH="/usr/local/bin/$EXECUTABLE"

DESKTOP_FILE="ocr-test.desktop"
DESKTOP_FILE_PATH="/usr/share/applications/$DESKTOP_FILE"
DESKTOP_FILE_CONTENT="[Desktop Entry]
Type=Application
Encoding=UTF-8
Name=OcrTest
Comment=Ocr test app
Icon=/usr/local/share/ocr-test.png
Exec=$EXECUTABLE_PATH
Terminal=false
"

info "Installing test app"

echo "$DESKTOP_FILE_CONTENT"

sudo cp build/OcrTest $EXECUTABLE_PATH
sudo wget $IMAGE_URL -qO $IMAGE_PATH
sudo chmod +x $EXECUTABLE_PATH
echo "$DESKTOP_FILE_CONTENT" | sudo tee $DESKTOP_FILE_PATH > /dev/null
sudo chmod 644 $DESKTOP_FILE_PATH

info "Done"
