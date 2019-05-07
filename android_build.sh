#!/bin/bash
#
# Usage
# > android_build.sh
#

AND_PLATFORM=android-24
BUILD_DIR=./build_andx86

shopt -s expand_aliases

# Add QT/android paths to environment
source ./env.sh android_x86

qmake_andx86
make
make install INSTALL_ROOT=$BUILD_DIR
qtdeploy_andx86 --output $BUILD_DIR \
                --input android-librpicamview.so-deployment-settings.json \
                --android-platform $AND_PLATFORM \
                --verbose \
                --gradle
