#!/bin/bash
#
# Add QT/android to path
#
# Usage:
#
# > source <path/to/this/script> <platform>
#
# where platform is one of {android_armv7, gcc_64, android_x86} (look
# under `Qt/version/` for available platforms.
#

function print_usage(){
    echo "Usage:"
    echo "source <this-script> <target_platform>"
    echo "where <target_platform> = {android_armv7, gcc_64, android_x86}"
}

if  [ "$#" -ne "1" ]; then
    print_usage
    # if sourced, exiting will close the user's shell process
fi

# Configurable paths/versions
QT_VER='5.12.2'                 # {5.6, 5.12.2}
QT_ROOT='/opt/Qt5.12.2/'        # {/opt/Qt5.6.2/, /opt/Qt5.12.2}
target_platform=$1

export ANDROID_HOME='/opt/android/android-sdk/'
export ANDROID_SDK='/opt/android/android-sdk/'

# needed for android-...-....json
export ANDROID_SDK_ROOT='/opt/android/android-sdk/'

export ANDROID_NDK='/opt/android/android-ndk-r19c/'
export ANDROID_NDK_ROOT='/opt/android/android-ndk-r19c/'

# Qt
alias qmake64="${QT_ROOT}/${QT_VER}/gcc_64/bin/qmake"
alias qmake_andx86="${QT_ROOT}/${QT_VER}/android_x86/bin/qmake"
alias qmake_arm7="${QT_ROOT}/${QT_VER}/android_armv7/bin/qmake"
alias qmlscene="${QT_ROOT}/${QT_VER}/gcc_64/bin/qmlscene"
alias qtcreator="${QT_ROOT}/Tools/QtCreator/bin/qtcreator"
alias qtdeploy_andx86="${QT_ROOT}/${QT_VER}/android_x86/bin/androiddeployqt"
alias qtdeploy_armv7="${QT_ROOT}/${QT_VER}/android_armv7/bin/androiddeployqt"

# Needed for running desktop builds
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"${QT_ROOT}/${QT_VER}/${target_platform}/lib/"
export QML2_IMPORT_PATH="${QT_ROOT}/${QT_VER}/${target_platform}/qml/"
export QT_PLUGIN_PATH="${QT_ROOT}/${QT_VER}/${target_platform}/plugins/"
export QT_QPA_PLATFORM_PLUGIN_PATH="${QT_ROOT}/${QT_VER}/${target_platform}/plugins/platforms/"

# Android
alias avdmanager="${ANDROID_SDK}/tools/bin/avdmanager"
alias androidemulator="${ANDROID_SDK}/tools/emulator"
alias adb="${ANDROID_HOME}/platform-tools/adb"
