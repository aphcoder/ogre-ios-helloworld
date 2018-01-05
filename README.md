# ogre-ios-helloworld
IOS ogre helloworld sample for ogremesh display


# Why

* A very simple sample is mandatory to test the full chain deploiement to a device as according to many articles it could be very time consuming to have a version work with any device/platform/OS when recompiling by oneself.

* Lots of blogs/articles are out of date.

* Trying by myself to recompile from source and deploy to embedded but encountered some issues.

* Opened a forum thread for community help at https://forums.ogre3d.org/viewtopic.php?f=21&t=93868


# Status

* TRIAL/EXPERIMENTAL, NOT FULLY FUNCTIONAL YET

* For IOS SIMU, the renderer and viewport are initialized properly




## ogre 1.10.11 compilation


```bash
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


// *************************
// zlib 1.2.11 (not needed, but here the procedure in case of)
// *************************
mkdir ~/zlib && cd zlib
curl -LO https://zlib.net/zlib-1.2.11.tar.gz
tar xvzf zlib-1.2.11.tar.gz && cd zlib-1.2.11
./configure --prefix=/usr/local/zlib
make
sudo make install



// ******************************************************
// ogre modifications
// ******************************************************

gedit ./CMake/toolchain/ios.toolchain.xcode.cmake

l153: removed arm7 (targeting device latest IOS 11.x only support 64bits arm9)
if (${IOS_PLATFORM} STREQUAL "OS")
set (IOS_ARCH arm64)
else ()
set (IOS_ARCH x86_64)
endif ()


// ******************************************************
// Generate xcodeproj for ogre
// ******************************************************

// From the forum help, for the moment, the best way is to do like the CI build (ci-build.make)
cd ogre-1.10.11

// SIMU
export IOS=TRUE
cmake -P ci-build.cmake
cmake --build .


/* Instead of specific cmake commands:
// SIMU
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=SIMULATOR -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode .

// IOS Generic Device
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode .

// IOS DEVICES
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=OS -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -G Xcode .

// MAC 64bits:
cmake -D OGRE_BUILD_PLATFORM_APPLE_IOS=1 -G Xcode ..
*/


find . -name "*.a"
./lib/iphonesimulator/Debug/libSample_VolumeTerrain.a
./lib/iphonesimulator/Debug/libSample_SkeletalAnimation.a
./lib/iphonesimulator/Debug/libSample_DeferredShading.a
./lib/iphonesimulator/Debug/libSample_SkyBox.a
./lib/iphonesimulator/Debug/libSample_PNTriangles.a
./lib/iphonesimulator/Debug/libSample_ShaderSystemTexturedFog.a
./lib/iphonesimulator/Debug/libSample_TextureArray.a
./lib/iphonesimulator/Debug/libSample_SkyPlane.a
./lib/iphonesimulator/Debug/libSample_BezierPatch.a
./lib/iphonesimulator/Debug/libVTests.a
./lib/iphonesimulator/Debug/libSample_ShaderSystem.a
./lib/iphonesimulator/Debug/libSample_FacialAnimation.a
./lib/iphonesimulator/Debug/libSample_Water.a
./lib/iphonesimulator/Debug/libSample_Transparency.a
./lib/iphonesimulator/Debug/libSample_Lighting.a
./lib/iphonesimulator/Debug/libSample_NewInstancing.a
./lib/iphonesimulator/Debug/libSample_Smoke.a
./lib/iphonesimulator/Debug/libSample_CelShading.a
./lib/iphonesimulator/Debug/libSample_Character.a
./lib/iphonesimulator/Debug/libSample_CameraTrack.a
./lib/iphonesimulator/Debug/libSample_ParticleFX.a
./lib/iphonesimulator/Debug/libSample_HLMS.a
./lib/iphonesimulator/Debug/libSample_SkyDome.a
./lib/iphonesimulator/Debug/libOgreGLSupportStatic.a
./lib/iphonesimulator/Debug/libSample_DualQuaternion.a
./lib/iphonesimulator/Debug/libRenderSystem_GLES2Static.a
./lib/iphonesimulator/Debug/libSample_Grass.a
./lib/iphonesimulator/Debug/libSample_Shadows.a
./lib/iphonesimulator/Debug/libSample_Fresnel.a
./lib/iphonesimulator/Debug/libSample_ShaderSystemMultiLight.a
./lib/iphonesimulator/Debug/libSample_Terrain.a
./lib/iphonesimulator/Debug/libSample_ParticleGS.a
./lib/iphonesimulator/Debug/libSample_VolumeCSG.a
./lib/iphonesimulator/Debug/libSample_Compute.a
./lib/iphonesimulator/Debug/libSample_EndlessWorld.a
./lib/iphonesimulator/Debug/libSample_Compositor.a
./lib/iphonesimulator/Debug/libSample_BSP.a
./lib/iphonesimulator/Debug/libOgreMainStatic.a
./lib/iphonesimulator/Debug/libSample_Ocean.a
./lib/iphonesimulator/Debug/libSample_DynTex.a
./lib/iphonesimulator/Debug/libSample_PBR.a
./lib/iphonesimulator/Debug/libSample_VolumeTex.a
./lib/iphonesimulator/Debug/libSample_Instancing.a
./lib/iphonesimulator/Debug/libSample_TextureFX.a
./lib/iphonesimulator/Debug/libSample_CubeMapping.a
./lib/iphonesimulator/Debug/libSample_Tessellation.a
./lib/iphonesimulator/Debug/libSample_SSAO.a
./lib/iphonesimulator/Debug/libSample_SphereMapping.a
./lib/iphonesimulator/Debug/libSample_Isosurf.a
./lib/iphonesimulator/Debug/libPlayPenTests.a
./lib/iphonesimulator/Debug/libSample_Dot3Bump.a
./lib/iphonesimulator/Debug/libSample_MeshLod.a
./ogredeps/lib/libzzip.a
./ogredeps/lib/libfreetyped.a

./lib/iphonesimulator/Debug/Plugin_BSPSceneManagerStatic.framework
./lib/iphonesimulator/Debug/Plugin_ParticleFXStatic.framework
./lib/iphonesimulator/Debug/OgrePropertyStatic.framework
./lib/iphonesimulator/Debug/Plugin_OctreeZoneStatic.framework
./lib/iphonesimulator/Debug/Plugin_OctreeSceneManagerStatic.framework
./lib/iphonesimulator/Debug/OgreRTShaderSystemStatic.framework
./lib/iphonesimulator/Debug/OgrePagingStatic.framework
./lib/iphonesimulator/Debug/Plugin_PCZSceneManagerStatic.framework
./lib/iphonesimulator/Debug/OgreBitesStatic.framework
./lib/iphonesimulator/Debug/OgreOverlayStatic.framework
./lib/iphonesimulator/Debug/OgreVolumeStatic.framework
./lib/iphonesimulator/Debug/OgreMeshLodGeneratorStatic.framework
./lib/iphonesimulator/Debug/OgreHLMSStatic.framework
./lib/iphonesimulator/Debug/OgreTerrainStatic.framework


// Check
find ./lib -name "*.a" | xargs ls -l
xcrun -sdk iphoneos lipo -info libOgreMainStatic.a



```


## Sample


```
References:

https://github.com/cloderic/ios-ogre
http://wiki.ogre3d.org/Ogre+Wiki+Tutorial+Framework

Used Java style coding.
```


## TODO

[X] Resolve Cannot initialise - no render system has been selected (DONE with SIMU)
[] Have OgreMesh properly displayed on iphone simulator
[] Have OgreMesh properly displayed on iphone device
[] Port application to new style Ogre Bites


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




