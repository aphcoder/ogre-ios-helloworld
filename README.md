# ogre-ios-helloworld
IOS ogre helloworld sample for ogremesh display


TRIAL/EXPERIMENTAL, NOT FUNCTIONAL YET


Lots of blogs/articles are out of date

Trying by myself to recompile from source and deploy to embedded but encountered some issues




## ogre 1.10.11 compilation


```
Configuration:
Ogre source https://www.ogre3d.org/download/sdk
1.10.11

MacOS 10.13.2
XCode 9.2
target: arm9 for idevices / x86_64 simulator



// ******************************************************
// Prerequisites installations:
// ******************************************************

// *************************
// CMAKE 3.10.1
// *************************

mkdir ~/cmake && cd cmake
curl --remote-name --location https://cmake.org/files/v3.10/cmake-3.10.1-Darwin-x86_64.tar.gz
tar xvzf cmake-3.10.1-Darwin-x86_64.tar.gz

Add in ./bash_profile
export CMAKE_HOME=~/cmake/cmake-3.10.1-Darwin-x86_64/CMake.app/Contents
export PATH=$PATH:$CMAKE_HOME/bin


// *************************
// FreeType 2.6.5
// *************************

mkdir ~/freetype && cd freetype
curl --remote-name --location http://download.savannah.gnu.org/releases/freetype/freetype-2.6.5.tar.gz
tar xvzf freetype-2.6.5.tar.gz && cd freetype-2.6.5
./configure --prefix=/usr/local/$LOGNAME/freetype-2.6.5
make
sudo make install
sudo ln -s /usr/local/$LOGNAME/freetype-2.6.5 /usr/local/freetype




// ******************************************************
// ogre modifications
// ******************************************************

gedit ./CMake/toolchain/ios.toolchain.xcode.cmake

l153: removed arm7
if (${IOS_PLATFORM} STREQUAL "OS")
set (IOS_ARCH arm64)
else ()
set (IOS_ARCH x86_64)
endif ()


// ******************************************************
// Generate xcodeproj for ogre
// ******************************************************


// SIMU
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=SIMULATOR -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode ..


// IOS Generic Device
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode ..


// IOS DEVICES
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=OS -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode ..


// MAC 64bits:
cmake -D OGRE_BUILD_PLATFORM_APPLE_IOS=1 -G Xcode ..



// Check
find ./lib -name "*.a" | xargs ls -l
xcrun -sdk iphoneos lipo -info libOgreMainStatic.a



find . -name "*.a"
./iOSDependencies/lib/libfreetype.a
./freetype-2.6.5/objs/RelWithDebInfo-iphoneos/libfreetype.a
./lib/iphoneos/Debug/libOgreGLSupportStatic.a
./lib/iphoneos/Debug/libRenderSystem_GLES2Static.a
./lib/iphoneos/Debug/libOgreMainStatic.a
./lib/iphonesimulator/Debug/libOgreGLSupportStatic.a
./lib/iphonesimulator/Debug/libRenderSystem_GLES2Static.a
./lib/iphonesimulator/Debug/libOgreMainStatic.a

find . -name "*.framework"
./lib/iphoneos/Debug/Plugin_BSPSceneManagerStatic.framework
./lib/iphoneos/Debug/Plugin_ParticleFXStatic.framework
./lib/iphoneos/Debug/OgrePropertyStatic.framework
./lib/iphoneos/Debug/Plugin_OctreeZoneStatic.framework
./lib/iphoneos/Debug/Plugin_OctreeSceneManagerStatic.framework
./lib/iphoneos/Debug/OgreRTShaderSystemStatic.framework
./lib/iphoneos/Debug/OgrePagingStatic.framework
./lib/iphoneos/Debug/Plugin_PCZSceneManagerStatic.framework
./lib/iphoneos/Debug/OgreVolumeStatic.framework
./lib/iphoneos/Debug/OgreMeshLodGeneratorStatic.framework
./lib/iphoneos/Debug/OgreHLMSStatic.framework
./lib/iphoneos/Debug/OgreTerrainStatic.framework

```


## Sample


```
References:

https://github.com/cloderic/ios-ogre
http://wiki.ogre3d.org/Ogre+Wiki+Tutorial+Framework

Used Java style coding.
```


## TODO

[X] Resolve Cannot initialise - no render system has been selected
[X] Have OgreMesh properly displayed on iphone simulator
[X] Have OgreMesh properly displayed on iphone device
[X] Port application to new style Ogre Bites


## Last run logs/status


```
SIMU: Black screen/nothing appears due to init failed

```


```
2018-01-01 14:47:23.906288+0100 ogre-ios-helloworld[15973:526328] +[CATransaction synchronize] called within transaction
Creating resource group General
Creating resource group Internal
Creating resource group Autodetect
SceneManagerFactory for type 'DefaultSceneManager' registered.
Registering ResourceManager for type Material
Registering ResourceManager for type Mesh
Registering ResourceManager for type Skeleton
MovableObjectFactory for type 'ParticleSystem' registered.
ArchiveFactory for archive type FileSystem registered.
DDS codec registering
PVRTC codec registering
ETC codec registering
stb_image - v2.15 - public domain JPEG/PNG reader
Supported formats: jpeg,jpg,png,bmp,psd,tga,gif,pic,ppm,pgm,hdr
Registering ResourceManager for type HighLevelGpuProgram
Registering ResourceManager for type Compositor
MovableObjectFactory for type 'Entity' registered.
MovableObjectFactory for type 'Light' registered.
MovableObjectFactory for type 'BillboardSet' registered.
MovableObjectFactory for type 'ManualObject' registered.
MovableObjectFactory for type 'BillboardChain' registered.
MovableObjectFactory for type 'RibbonTrail' registered.
*-*-* OGRE Initialising
*-*-* Version 1.10.11 (Xalafu)
2018-01-01 14:47:23.993133+0100 ogre-ios-helloworld[15973:526328] ViewController::startWithWindow Exception: InvalidStateException: Cannot initialise - no render system has been selected. in Root::initialise at /Users/aphcoder/Projects/Ogre3D/ogre-1.10.11/OgreMain/src/OgreRoot.cpp (line 663)
```




