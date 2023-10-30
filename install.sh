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

DESKTOP_FILE="ocr-test.desktop"
DESKTOP_FILE_PATH="/usr/share/applications/$DESKTOP_FILE"
DESKTOP_FILE_CONTENT="[Desktop Entry]
Type=Application
Encoding=UTF-8
Name=OcrTest
Comment=Ocr test app
Icon=/usr/local/share/ocr-test.png
Exec=/usr/local/bin/ocr-test
Terminal=false
Categories=X-Debian-Applications-JMRI;
"

info "Installing test app"

sudo cp build/OcrTest /usr/local/bin/ocr-test
sudo wget https://en.wikipedia.org/wiki/File:Schlegel_wireframe_8-cell.png -qO /usr/local/share/ocr-test.png
sudo chmod +x /usr/local/bin/ocr-test
sudo touch $DESKTOP_FILE_PATH
sudo chmod 644 $DESKTOP_FILE_PATH
sudo echo "$DESKTOP_FILE_CONTENT" > $DESKTOP_FILE_PATH

info "Done"
