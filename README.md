# Requirements

Following tools were used
* Qt 5.6.2
* Android SDK 25.2.5 (Newer SDKs are not compatible with newest Qt
  versions up to Qt 5.9)
* Android NDK (version?)
* Apache ANT 1.10.1
* Android API 21


Additional yum packages that were installed
* SDL-devel
* glibc
* libgcc_s.so.1
* openjdk
* openjdk-devel
* @viritualization

# Compilation

Must have following in path:
* `ANDROID_HOME`
* `ANDROID_NDK_ROOT`
* `ANDROID_NDK_TOOLCHAIN_PREFIX`
* `ANDROID_NDK_TOOLS_PREFIX`
* `ANDROID_NDK_PLATFORM`
* `ANDROID_SDK_ROOT`
* `ANDROID_ROOT_PATH`
* `ANT bin root`

General build command:
```
qmake (armv7 or x86 depending on target platform)
qmake
make install INSTALL_ROOT=$BUILD_DIR
androiddeployqt --output $BUILD_DIR --input /path/to/jsonfile.json android-platform $ANDROID_NDK_PLATFORM --verbose
```
