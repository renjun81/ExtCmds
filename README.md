# DemoCmds

## Overview

DemoCmds is a template and example project containing customized shape and command classes based on [vgcore](https://github.com/rhcad/vgcore).
You can customize the drawing behavior via implement your [CmdObserve class](core/cmds/cmds.cpp).

You can use [newproj.py](newproj.py) to create your library project:
Type `python newproj.py PrjName` or double click the file 'newproj.py'.

## Build

### Build for **iOS** platform on Mac OS X.

- Type `pod install` or `pod install --no-repo-update` with [CocoaPods](http://cocoapods.org). Need to remove `libPods.a` from Link Binary With Libraries.

- Or open `ios/DemoCmds/DemoCmds.xcodeproj` in Xcode, then build the library project.

- Or cd the 'ios' folder of this project and type `./build.sh` to build `ios/output/libDemoCmds.a`.
    - Type `./build.sh -arch arm64` to make iOS libraries for iOS 64-bit.
    - Type `./build.sh clean` to remove object files.

### Build for **Android** platform on Mac, Linux or Windows.

- Cd the 'android' directory of this project and type `./build.sh` to build with ndk-build. The library `libDemoCmds.a` will be outputed to `android/DemoCmds/obj/local/armeabi`.

    - Type `./build.sh -B` to rebuild the native libraries.
    - Type `./build.sh APP_ABI=x86` to build for the x86 (Intel Atom) Emulator.
    - MinGW and MSYS are recommend on Windows.    

    - To regenerate the kernel JNI classes, type `./build.sh -swig`
(Need to install [SWIG](http://sourceforge.net/projects/swig/files/), and add the location to PATH).

### Build for **Windows** platform with Visual Studio.

- Open `win\vs2010.sln` in Visual Studio 2010, then build the DemoCmds library project. Or open `win\vs2008.sln` in Visual Studio 2008.

- To regenerate `win/democmdslib/core/*.cs`, please enter `win` directory and type `./build.sh`
(Need to install [SWIG](http://sourceforge.net/projects/swig/files/), and add the location to PATH). Or change 'Excluded From Build' setting of `democmds|Swig Files|democmds.i` as 'No' in Visual Studio to compile it.
   
### Build for more platforms and targets.

- Cd the 'core' folder of this project and type `make` or `make all install` to generate libraries on Mac, Linux or Windows.
- Type `make java`, `make python` or `make csharp` to generate libraries for another language applications using Java, Python or C#.
- Type `make clean java.clean python.clean` to remove the program object files.
