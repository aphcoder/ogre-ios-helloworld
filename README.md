# ogre-ios-helloworld
IOS ogre helloworld sample for ogremesh display


# Why

* A very simple sample is mandatory to test the full chain deploiement to a device as according to many articles it could be very time consuming to have a version work with any device/platform/OS when recompiling by oneself.

* Lots of blogs/articles are out of date. (1.10 initialization is simplified with OgreBites::ApplicationContext)

* Trying by myself to recompile from source and deploy to embedded but encountered some issues.

* Opened a forum thread for community help at https://forums.ogre3d.org/viewtopic.php?f=21&t=93868


# STATUS



* For IOS SIMU, viewport, Sinbad and SdkTray are rendered properly

* For IOS Device, viewport, Sinbad and SdkTray are rendered properly
    * need to sign a development team for xcode project
    * The media resources is "Media" and not "media"
    * Very tricky part to compile first for SIMU, keep track of some generated stuffs, clean and build for Device

* For Win10 VS Community 2017 (Debug x64) viewport, Sinbad and SdkTray are rendered properly
    * Convenient for people working with Win environment (VS Studio, Blender)
    * Debug x64 (for development env purpose only)



# COMPILATION

## ogre 1.10.11 compilation for IOS


```bash
Configuration:
Ogre source https://www.ogre3d.org/download/sdk
1.10.11

MacOS 10.13.2
XCode 9.2 / Build SDK 11.2 / IOS Deploy Target 11.2
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


brew update && brew install freetype libzzip sdl2

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

> gedit ci-build.make &
set(BUILD_DEPS TRUE)
-DIOS_PLATFORM=SIMULATOR

rm -f CMakeCache.txt && rm -fr CMakeFiles && rm -fr ogredeps && rm -fr iOSDependencies && rm -fr ZZIPlib-master && rm -fr freetype-2.6.5 && rm -fr OGRE.xcodeproj


// SIMU
export IOS=TRUE && cmake -P ci-build.cmake && cmake --build .
(Generated ZZIPlib-master project)
cp ./ogredeps/lib/*.a lib/iphonesimulator/Debug/


// DEVICE
rm -f CMakeCache.txt
-DIOS_PLATFORM=OS
export IOS=TRUE && cmake -P ci-build.cmake && cmake --build .
Change ZZIPlib-master.xcode for all arm9 and remove all dynlib (dynamic options)
=> link fine (no Factory missing for ZIP)



/* Instead of specific cmake commands:(missing some libs generation)
// SIMU
export IOS=TRUE &&
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=SIMULATOR -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -DOGRE_BUILD_DEPENDENCIES=TRUE -DOGRE_DEPENDENCIES_DIR="/Users/aphcoder/ogre/ogre-1.10.11/MyDeps" -G Xcode .
cmake --build .
(missing Overlay and OgreBites Should pass -DOGRE_BUILD_DEPENDENCIES=TRUE -DOGRE_DEPENDENCIES_DIR="./MyDeps" )


// IOS DEVICES
cmake -DCMAKE_TOOLCHAIN_FILE=CMake/toolchain/ios.toolchain.xcode.cmake -DIOS_PLATFORM=OS -DFREETYPE_FT2BUILD_INCLUDE_DIR=/usr/local/freetype/include/freetype2 -DOGRE_BUILD_DEPENDENCIES=TRUE -DOGRE_DEPENDENCIES_DIR="./MyDeps" -G Xcode .

-DOGRE_DEPENDENCIES_DIR="/Users/aphcoder/ogre/ogre-1.10.11/MyDeps"

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


// Check for arm64
find . -name "*.a" | xargs xcrun -sdk iphoneos lipo -info

xcrun -sdk iphoneos lipo -info libOgreMainStatic.a



```





## ogre 1.10.11 compilation for Win10 / Direct X11

Compilation is much easier for Win10 / VS Community 2017


```bash

Install VS Studio Community 2017

Install Cmake GUI 3.10.1


Open Cmake GUI 3.10.1 and set:
VS Studio 15 2017 Win64
Native Compiler

ogre-1.10.11
ogre-1.10.11/build


Open Ogre.sln with VS Studio then compile ALL


Check .lib:
$(OGRE_SDK_ROOT)\build\lib\Debug\*.lib

Chek for .dll:
$(OGRE_SDK_ROOT)\build\bin\debug\*.dll


```




# SAMPLE


## xcode

```bash
References:

https://github.com/cloderic/ios-ogre
http://wiki.ogre3d.org/Ogre+Wiki+Tutorial+Framework
https://ogrecave.github.io/ogre/api/1.10/setup.html

Used Java style coding.


Framework and library search paths:
$(OGRE_SDK_ROOT)/lib/$(PLATFORM_NAME)/Debug


Header search paths:
$(OGRE_SDK_ROOT)/OgreMain/include
$(OGRE_SDK_ROOT)/include
$(OGRE_SDK_ROOT)/OgreMain/include/iOS
$(OGRE_SDK_ROOT)/Components/Bites/include
$(OGRE_SDK_ROOT)/Components/RTShaderSystem/include
$(OGRE_SDK_ROOT)/Components/Overlay/include
$(OGRE_SDK_ROOT)/ZZIPlib-master

$(OGRE_SDK_ROOT)/build/include
$(OGRE_SDK_ROOT)/build/Dependencies/include
$(OGRE_SDK_ROOT)/build/Dependencies/include/SDL2

```

## VS 2017

* [VS settings instructions](https://github.com/aphcoder/ogre-ios-helloworld/blob/master/ogre-helloworld.vs/README.md)

```bash

Should use (Debug x64):
plugins_d.cfg
ogre.cfg
resources_d.cfg



```

# TODO



# Last run logs/status

## xcode

```
2018-01-11 00:06:56.601028+0100 ogre-ios-helloworld[835:232235] [DYMTLInitPlatform] platform initialization successful
2018-01-11 00:06:57.239422+0100 ogre-ios-helloworld[835:232117] +[CATransaction synchronize] called within transaction
Creating resource group General
Creating resource group OgreInternal
Creating resource group OgreAutodetect
SceneManagerFactory for type 'DefaultSceneManager' registered.
Registering ResourceManager for type Material
Registering ResourceManager for type Mesh
Registering ResourceManager for type Skeleton
MovableObjectFactory for type 'ParticleSystem' registered.
ArchiveFactory for archive type FileSystem registered.
ArchiveFactory for archive type Zip registered.
ArchiveFactory for archive type EmbeddedZip registered.
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
Installing plugin: OpenGL ES 2.0 RenderSystem
OpenGL ES 2.x Rendering Subsystem created.
Plugin successfully installed
Installing plugin: Octree Scene Manager
Plugin successfully installed
Installing plugin: ParticleFX
Particle Emitter Type 'Point' registered
Particle Emitter Type 'Box' registered
Particle Emitter Type 'Ellipsoid' registered
Particle Emitter Type 'Cylinder' registered
Particle Emitter Type 'Ring' registered
Particle Emitter Type 'HollowEllipsoid' registered
Particle Affector Type 'LinearForce' registered
Particle Affector Type 'ColourFader' registered
Particle Affector Type 'ColourFader2' registered
Particle Affector Type 'ColourImage' registered
Particle Affector Type 'ColourInterpolator' registered
Particle Affector Type 'Scaler' registered
Particle Affector Type 'Rotator' registered
Particle Affector Type 'DirectionRandomiser' registered
Particle Affector Type 'DeflectorPlane' registered
Plugin successfully installed
Installing plugin: BSP Scene Manager
Plugin successfully installed
OverlayElementFactory for type Panel registered.
OverlayElementFactory for type BorderPanel registered.
OverlayElementFactory for type TextArea registered.
Registering ResourceManager for type Font
CPU Identifier & Features
-------------------------
*   CPU ID: ARM64v8
*          VFP: no
*         NEON: no
-------------------------
Registering ResourceManager for type Texture
GLES2RenderSystem::_createRenderWindow "OgreApplication", 320x480 windowed  miscParams: FSAA=4 Video Mode=320x480 colourDepth=32 contentScalingFactor=2.0 externalViewHandle=4330119488 externalWindowHandle=4331428560
iOS: Using an external window handle
iOS: Using an external view handle
iOS: Window created 320 x 480 with backing store size 320 x 480 using content scaling factor 1.0
GL_VERSION = 3.0.0.0
GL_VENDOR = Apple Inc.
GL_RENDERER = Apple A7 GPU
GL_EXTENSIONS = GL_OES_standard_derivatives GL_EXT_color_buffer_half_float GL_EXT_debug_label GL_EXT_debug_marker GL_EXT_pvrtc_sRGB GL_EXT_read_format_bgra GL_EXT_separate_shader_objects GL_EXT_shader_framebuffer_fetch GL_EXT_shader_texture_lod GL_EXT_shadow_samplers GL_EXT_texture_filter_anisotropic GL_APPLE_clip_distance GL_APPLE_color_buffer_packed_float GL_APPLE_copy_texture_levels GL_APPLE_rgb_422 GL_APPLE_texture_format_BGRA8888 GL_IMG_read_format GL_IMG_texture_compression_pvrtc
**************************************
*** OpenGL ES 2.x Renderer Started ***
**************************************
Shading language version: OpenGL ES GLSL ES 3.00
Registering ResourceManager for type GpuProgram
GL ES 2: Using FBOs for rendering to textures
FBO PF_L8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_BYTE_LA depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R5G6B5 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_A4R4G4B4 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_A1R5G5B5 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_B8G8R8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_A8B8G8R8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_A2B10G10R10 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_FLOAT16_RGB depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_FLOAT16_RGBA depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_X8B8G8R8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_FLOAT16_R depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_FLOAT16_GR depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R11G11B10_FLOAT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8G8_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8G8B8A8_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16G16_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16G16B16A16_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32G32_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32G32B32A32_UINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8G8_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8G8B8A8_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16G16_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R16G16B16A16_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32G32_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R32G32B32A32_SINT depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R9G9B9E5_SHAREDEXP depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_R8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
FBO PF_RG8 depth/stencil support: D0S0 D0S8 D16S0 D24S0 D32S0 Packed-D24S8 Packed-D32S8
[GLES2] : Valid FBO targets PF_L8 PF_BYTE_LA PF_R5G6B5 PF_A4R4G4B4 PF_A1R5G5B5 PF_B8G8R8 PF_A8B8G8R8 PF_A2B10G10R10 PF_FLOAT16_RGB PF_FLOAT16_RGBA PF_X8B8G8R8 PF_FLOAT16_R PF_FLOAT16_GR PF_R11G11B10_FLOAT PF_R8_UINT PF_R8G8_UINT PF_R8G8B8A8_UINT PF_R16_UINT PF_R16G16_UINT PF_R16G16B16A16_UINT PF_R32_UINT PF_R32G32_UINT PF_R32G32B32A32_UINT PF_R8_SINT PF_R8G8_SINT PF_R8G8B8A8_SINT PF_R16_SINT PF_R16G16_SINT PF_R16G16B16A16_SINT PF_R32_SINT PF_R32G32_SINT PF_R32G32B32A32_SINT PF_R9G9B9E5_SHAREDEXP PF_R8 PF_RG8
RenderSystem capabilities
-------------------------
RenderSystem Name: OpenGL ES 2.x Rendering Subsystem
GPU Vendor: apple
Device Name: Apple A7 GPU
Driver Version: 3.0.0.0
* Fixed function pipeline: no
* Anisotropic texture filtering: yes
* Cube mapping: yes
* Hardware stencil buffer: yes
- Stencil depth: 8
- Two sided stencil support: yes
- Wrap stencil values: yes
* 32-bit index buffers: yes
* Vertex programs: yes
* Number of floating-point constants for vertex programs: 2048
* Number of integer constants for vertex programs: 2048
* Number of boolean constants for vertex programs: 2048
* Fragment programs: yes
* Number of floating-point constants for fragment programs: 896
* Number of integer constants for fragment programs: 896
* Number of boolean constants for fragment programs: 896
* Geometry programs: no
* Number of floating-point constants for geometry programs: 25963
* Number of integer constants for geometry programs: 8306
* Number of boolean constants for geometry programs: 19527
* Tessellation Hull programs: no
* Number of floating-point constants for tessellation hull programs: 29793
* Number of integer constants for tessellation hull programs: 24421
* Number of boolean constants for tessellation hull programs: 26739
* Tessellation Domain programs: no
* Number of floating-point constants for tessellation domain programs: 25697
* Number of integer constants for tessellation domain programs: 29285
* Number of boolean constants for tessellation domain programs: 28511
* Compute programs: no
* Number of floating-point constants for compute programs: 27234
* Number of integer constants for compute programs: 25445
* Number of boolean constants for compute programs: 29556
* Supported Shader Profiles: glsl300es glsles
* Texture Compression: yes
- DXT: no
- VTC: no
- PVRTC: yes
- ATC: no
- ETC1: no
- ETC2: yes
- BC4/BC5: no
- BC6H/BC7: no
- ASTC: no
- Mipmaps for compressed formats: no
* Hardware Occlusion Query: yes
* User clip planes: no
* VET_UBYTE4 vertex element type: yes
* Infinite far plane projection: yes
* Hardware render-to-texture: yes
* Floating point textures: yes
* Non-power-of-two textures: yes
* 1d textures: yes
* Volume textures: yes
* Multiple Render Targets: 4
- With different bit depths: yes
* Point Sprites: yes
* Hardware Gamma: yes
* Extended point parameters: yes
* Max Point Size: 0
* Vertex texture fetch: no
* Number of texture units: 16
* Number of vertex attributes: 16
* Stencil buffer depth: 8
* Number of vertex blend matrices: 0
* Render to Vertex Buffer : yes
* Hardware Atomic Counters: no
* PBuffer support: no
* Vertex Array Objects: yes
* Separate shader objects: yes
* GLSL SSO redeclare interface block: yes
* Debugging/ profiling events: yes
* Map buffer storage: yes
DefaultWorkQueue('Root') initialising on thread main.
Particle Renderer Type 'billboard' registered
SceneManagerFactory for type 'OctreeSceneManager' registered.
SceneManagerFactory for type 'BspSceneManager' registered.
Registering ResourceManager for type BspLevel
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/models' of type 'FileSystem' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/packs' of type 'FileSystem' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/packs/Sinbad.zip' of type 'Zip' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/materials/programs/GLSLES' of type 'FileSystem' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/RTShaderLib/materials' of type 'FileSystem' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/RTShaderLib/GLSL' of type 'FileSystem' to resource group 'General'
Added resource location '/var/containers/Bundle/Application/4DDC3251-318C-41D6-8E8B-750B3D810899/ogre-ios-helloworld.app/Media/RTShaderLib/GLSLES' of type 'FileSystem' to resource group 'General'
Parsing scripts for resource group General
Parsing script Sinbad.material
Parsing script DualQuaternionSkinning_Shadow.material
Parsing script HardwareSkinningShadow.material
Parsing script RTShaderSystem.material
Parsing script TriplanarTexturing.material
Finished parsing scripts for resource group General
Creating resources for group General
All done
Parsing scripts for resource group OgreAutodetect
Finished parsing scripts for resource group OgreAutodetect
Creating resources for group OgreAutodetect
All done
Parsing scripts for resource group OgreInternal
Finished parsing scripts for resource group OgreInternal
Creating resources for group OgreInternal
All done
Mesh: Loading Sinbad.mesh.
Skeleton: Loading Sinbad.skeleton
GLES2Texture::create - Name: sinbad_body.tga ID: 1 Width: 512 Height: 512 Internal Format: 0x8051
Texture: sinbad_body.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,512x512x1.
GLES2TextureBuffer::upload - ID: 1 Target: 3553 Format: PF_B8G8R8 Origin format: 0x1907 Data type: 0x1401
GLES2Texture::create - Name: sinbad_clothes.tga ID: 2 Width: 512 Height: 512 Internal Format: 0x8051
Texture: sinbad_clothes.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,512x512x1.
GLES2TextureBuffer::upload - ID: 2 Target: 3553 Format: PF_B8G8R8 Origin format: 0x1907 Data type: 0x1401
GLES2Texture::create - Name: sinbad_sword.tga ID: 3 Width: 256 Height: 256 Internal Format: 0x8051
Texture: sinbad_sword.tga: Loading 1 faces(PF_B8G8R8,256x256x1) with 8 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,256x256x1.
GLES2TextureBuffer::upload - ID: 3 Target: 3553 Format: PF_B8G8R8 Origin format: 0x1907 Data type: 0x1401
Warning: the mesh 'Sinbad.mesh' includes vertices with more than 4 bone assignments. The lowest weighted assignments beyond this limit have been removed, so your animation may look slightly different. To eliminate this, reduce the number of bone assignments per vertex on your mesh to 4.
Vertex Program:0369b6fd3565713ef085ad6153f68a12_VS Fragment Program:261169c92d2de4a41d1c4058f1f40751_FS
GLSL vertex program result :
WARNING: Could not find vertex shader attribute 'blendWeights' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv5' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'secondary_colour' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv1' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv4' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'blendIndices' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv6' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv2' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'colour' to match BindAttributeLocation request.

WARNING: Could not find vertex shader attribute 'position' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'tangent' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv3' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv7' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'binormal' to match BindAttributeLocation request.
Vertex Program:0369b6fd3565713ef085ad6153f68a12_VS Fragment Program:261169c92d2de4a41d1c4058f1f40751_FS
GLSL program pipeline result :
WARNING: Could not find vertex shader attribute 'blendWeights' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv5' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'secondary_colour' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv1' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv4' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'blendIndices' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv6' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv2' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'colour' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'position' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'tangent' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv3' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv7' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'binormal' to match BindAttributeLocation request.
Vertex Program:1f1c82ae619b18309d69663ce577b6f3_VS Fragment Program:18850cb0ce807df2a404e86fee49c28b_FS
GLSL vertex program result :
WARNING: Could not find vertex shader attribute 'blendWeights' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv5' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'secondary_colour' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv1' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv4' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'blendIndices' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv6' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv2' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'colour' to match BindAttributeLocation request.

WARNING: Could not find vertex shader attribute 'position' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'tangent' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv3' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'uv7' to match BindAttributeLocation request.
WARNING: Could not find vertex shader attribute 'binormal' to match BindAttributeLocation request.


```





## VS 2017


```bash
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\ogre-helloworld.vs.exe'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntdll.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\kernel32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Program Files\AVAST Software\Avast\x64\aswhooka.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\KernelBase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreBites_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreMain_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\user32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\win32u.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\gdi32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\gdi32full.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcp_win.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ucrtbase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\shell32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcrt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\cfgmgr32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\SHCore.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\rpcrt4.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\combase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\bcryptprimitives.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\windows.storage.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\advapi32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\sechost.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\shlwapi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\kernel.appcore.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\powrprof.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\profapi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreRTShaderSystem_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcp140d.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140d.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ucrtbased.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreOverlay_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\SDL2.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\imm32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ole32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\oleaut32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\zlib.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\winmm.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\version.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\winmmbase.dll'. Cannot find or open the PDB file.
Ogre: Creating resource group General
Ogre: Creating resource group Internal
Ogre: Creating resource group Autodetect
Ogre: SceneManagerFactory for type 'DefaultSceneManager' registered.
Ogre: Registering ResourceManager for type Material
Ogre: Registering ResourceManager for type Mesh
Ogre: Registering ResourceManager for type Skeleton
Ogre: MovableObjectFactory for type 'ParticleSystem' registered.
Ogre: ArchiveFactory for archive type FileSystem registered.
Ogre: ArchiveFactory for archive type Zip registered.
Ogre: ArchiveFactory for archive type EmbeddedZip registered.
Ogre: DDS codec registering
Ogre: ETC codec registering
Ogre: stb_image - v2.15 - public domain JPEG/PNG reader
Ogre: Supported formats: jpeg,jpg,png,bmp,psd,tga,gif,pic,ppm,pgm,hdr
Ogre: Registering ResourceManager for type HighLevelGpuProgram
Ogre: Registering ResourceManager for type Compositor
Ogre: MovableObjectFactory for type 'Entity' registered.
Ogre: MovableObjectFactory for type 'Light' registered.
Ogre: MovableObjectFactory for type 'BillboardSet' registered.
Ogre: MovableObjectFactory for type 'ManualObject' registered.
Ogre: MovableObjectFactory for type 'BillboardChain' registered.
Ogre: MovableObjectFactory for type 'RibbonTrail' registered.
Ogre: Loading library RenderSystem_Direct3D11_d
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\RenderSystem_Direct3D11_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\d3d11.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\dxgi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\D3DCompiler_47.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\cryptsp.dll'. Cannot find or open the PDB file.
Ogre: Installing plugin: D3D11 RenderSystem
Ogre: D3D11: Direct3D11 Rendering Subsystem created.
Ogre: D3D11: Driver Detection Starts
Ogre: D3D11: "Intel(R) HD Graphics 4000"
Ogre: D3D11: "Microsoft Basic Render Driver (software)"
Ogre: D3D11: Driver Detection Ends
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ResourcePolicyClient.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\ResourcePolicyClient.dll'
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igd10iumd64.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\bcrypt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ncrypt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntasn1.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igdusc64.dll'. Cannot find or open the PDB file.
Ogre: Plugin successfully installed
Ogre: *-*-* OGRE Initialising
Ogre: *-*-* Version 1.10.11 (Xalafu)
Ogre: OverlayElementFactory for type Panel registered.
Ogre: OverlayElementFactory for type BorderPanel registered.
Ogre: OverlayElementFactory for type TextArea registered.
Ogre: Registering ResourceManager for type Font
Ogre: D3D11: RenderSystem Option: Allow NVPerfHUD = No
Ogre: D3D11: RenderSystem Option: Backbuffer Count = Auto
Ogre: D3D11: RenderSystem Option: Driver type = Hardware
Ogre: D3D11: RenderSystem Option: FSAA = 1
Ogre: D3D11: RenderSystem Option: Floating-point mode = Fastest
Ogre: D3D11: RenderSystem Option: Full Screen = No
Ogre: D3D11: RenderSystem Option: Information Queue Exceptions Bottom Level = Info (exception on any message)
Ogre: D3D11: RenderSystem Option: Max Requested Feature Levels = 11.0
Ogre: D3D11: RenderSystem Option: Min Requested Feature Levels = 9.1
Ogre: D3D11: RenderSystem Option: Rendering Device = (default)
Ogre: D3D11: RenderSystem Option: VSync = No
Ogre: D3D11: RenderSystem Option: VSync Interval = 1
Ogre: D3D11: RenderSystem Option: Video Mode = 800 x 600 @ 32-bit colour
Ogre: D3D11: RenderSystem Option: sRGB Gamma Conversion = No
Ogre: CPU Identifier & Features
Ogre: -------------------------
Ogre:  *   CPU ID: GenuineIntel: Intel(R) Core(TM) i5-3320M CPU @ 2.60GHz
Ogre:  *          SSE: yes
Ogre:  *         SSE2: yes
Ogre:  *         SSE3: yes
Ogre:  *        SSE41: yes
Ogre:  *        SSE42: yes
Ogre:  *          MMX: yes
Ogre:  *       MMXEXT: yes
Ogre:  *        3DNOW: no
Ogre:  *     3DNOWEXT: no
Ogre:  *         CMOV: yes
Ogre:  *          TSC: yes
Ogre:  *INVARIANT TSC: yes
Ogre:  *          FPU: yes
Ogre:  *          PRO: yes
Ogre:  *           HT: no
Ogre: -------------------------
Ogre: D3D11: Subsystem Initialising
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\igdusc64.dll'
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\ntasn1.dll'
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\ncrypt.dll'
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\igd10iumd64.dll'
Ogre: D3D11: Driver Detection Starts
Ogre: D3D11: "Intel(R) HD Graphics 4000"
Ogre: D3D11: "Microsoft Basic Render Driver (software)"
Ogre: D3D11: Driver Detection Ends
Ogre: D3D11: Requested "(default)", selected "Intel(R) HD Graphics 4000"
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\DXGIDebug.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igd10iumd64.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ncrypt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntasn1.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\d3d11_3SDKLayers.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igdusc64.dll'. Cannot find or open the PDB file.
Ogre: ***************************************
Ogre: *** D3D11: Subsystem Initialized OK ***
Ogre: ***************************************
Ogre: D3D11RenderSystem::_createRenderWindow "OgreApplication", 800x600 windowed  miscParams: FSAA=1 externalWindowHandle=332358 gamma=No vsync=No 
Ogre: D3D11: Created D3D11 Rendering Window 'OgreApplication' : 800x600, 32bpp
Ogre: Warning: D3D11: disabling VSync in windowed mode can cause timing issues at lower frame rates, turn VSync on if you observe this problem.
Ogre: Registering ResourceManager for type Texture
Ogre: Registering ResourceManager for type GpuProgram
Ogre: RenderSystem capabilities
Ogre: -------------------------
Ogre: RenderSystem Name: Direct3D11 Rendering Subsystem
Ogre: GPU Vendor: intel
Ogre: Device Name: Intel(R) HD Graphics 4000
Ogre: Driver Version: 10.18.10.4425
Ogre:  * Fixed function pipeline: no
Ogre:  * Anisotropic texture filtering: yes
Ogre:  * Cube mapping: yes
Ogre:  * Hardware stencil buffer: yes
Ogre:    - Stencil depth: 8
Ogre:    - Two sided stencil support: yes
Ogre:    - Wrap stencil values: yes
Ogre:  * 32-bit index buffers: yes
Ogre:  * Vertex programs: yes
Ogre:  * Number of floating-point constants for vertex programs: 512
Ogre:  * Number of integer constants for vertex programs: 16
Ogre:  * Number of boolean constants for vertex programs: 16
Ogre:  * Fragment programs: yes
Ogre:  * Number of floating-point constants for fragment programs: 512
Ogre:  * Number of integer constants for fragment programs: 16
Ogre:  * Number of boolean constants for fragment programs: 16
Ogre:  * Geometry programs: yes
Ogre:  * Number of floating-point constants for geometry programs: 512
Ogre:  * Number of integer constants for geometry programs: 16
Ogre:  * Number of boolean constants for geometry programs: 16
Ogre:  * Tessellation Hull programs: yes
Ogre:  * Number of floating-point constants for tessellation hull programs: 512
Ogre:  * Number of integer constants for tessellation hull programs: 16
Ogre:  * Number of boolean constants for tessellation hull programs: 16
Ogre:  * Tessellation Domain programs: yes
Ogre:  * Number of floating-point constants for tessellation domain programs: 512
Ogre:  * Number of integer constants for tessellation domain programs: 16
Ogre:  * Number of boolean constants for tessellation domain programs: 16
Ogre:  * Compute programs: yes
Ogre:  * Number of floating-point constants for compute programs: 512
Ogre:  * Number of integer constants for compute programs: 16
Ogre:  * Number of boolean constants for compute programs: 16
Ogre:  * Supported Shader Profiles: cs_4_0 cs_4_1 cs_5_0 ds_5_0 gs_4_0 gs_4_1 gs_5_0 hlsl hs_5_0 ps_2_0 ps_2_a ps_2_b ps_2_x ps_3_0 ps_3_x ps_4_0 ps_4_0_level_9_1 ps_4_0_level_9_3 ps_4_1 ps_5_0 vs_2_0 vs_2_a vs_2_x vs_3_0 vs_4_0 vs_4_0_level_9_1 vs_4_0_level_9_3 vs_4_1 vs_5_0
Ogre:  * Texture Compression: yes
Ogre:    - DXT: yes
Ogre:    - VTC: no
Ogre:    - PVRTC: no
Ogre:    - ATC: no
Ogre:    - ETC1: no
Ogre:    - ETC2: no
Ogre:    - BC4/BC5: no
Ogre:    - BC6H/BC7: yes
Ogre:    - ASTC: no
Ogre:    - Mipmaps for compressed formats: yes
Ogre:  * Hardware Occlusion Query: yes
Ogre:  * User clip planes: yes
Ogre:  * VET_UBYTE4 vertex element type: yes
Ogre:  * Infinite far plane projection: yes
Ogre:  * Hardware render-to-texture: yes
Ogre:  * Floating point textures: yes
Ogre:  * Non-power-of-two textures: yes
Ogre:  * 1d textures: yes
Ogre:  * Volume textures: yes
Ogre:  * Multiple Render Targets: 8
Ogre:    - With different bit depths: yes
Ogre:  * Point Sprites: yes
Ogre:  * Hardware Gamma: no
Ogre:  * Extended point parameters: yes
Ogre:  * Max Point Size: 256
Ogre:  * Vertex texture fetch: yes
Ogre:  * Number of texture units: 16
Ogre:  * Number of vertex attributes: 32
Ogre:  * Stencil buffer depth: 8
Ogre:  * Number of vertex blend matrices: 0
Ogre:    - Max vertex textures: 4
Ogre:    - Vertex textures shared: no
Ogre:  * Render to Vertex Buffer : yes
Ogre:  * Hardware Atomic Counters: no
Ogre: DefaultWorkQueue('Root') initialising on thread main.
Ogre: Particle Renderer Type 'billboard' registered
Ogre: Added resource location 'Media' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/models' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/packs' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/packs/Sinbad.zip' of type 'Zip' to resource group 'General'
Ogre: Added resource location 'Media/packs/SdkTrays.zip' of type 'Zip' to resource group 'General'
Ogre: Added resource location 'Media/materials/programs/HLSL' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/materials/programs/HLSL_Cg' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/RTShaderLib/materials' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/RTShaderLib/HLSL' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/RTShaderLib/HLSL_Cg' of type 'FileSystem' to resource group 'General'
Ogre: Parsing scripts for resource group Autodetect
Ogre: Finished parsing scripts for resource group Autodetect
Ogre: Creating resources for group Autodetect
Ogre: All done
Ogre: Parsing scripts for resource group General
Ogre: Parsing script Sinbad.material
Ogre: Parsing script SdkTrays.material
Ogre: Parsing script DualQuaternionSkinning_Shadow.material
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\uxtheme.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msctf.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\dwmapi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\clbcatq.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\TextInputFramework.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\CoreUIComponents.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\CoreMessaging.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntmarta.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\WinTypes.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\rsaenh.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\cryptbase.dll'. Cannot find or open the PDB file.
Ogre: Parsing script HardwareSkinningShadow.material
Ogre: Parsing script RTShaderSystem.material
Ogre: Parsing script TriplanarTexturing.material
Ogre: Parsing script SdkTrays.fontdef
Ogre: Parsing script SdkTrays.overlay
Ogre: Bad element attribute line: '# you can offset the image to change the cursor "hotspot"' for element SdkTrays/Cursor in overlay 
Ogre: Texture: sdk_cursor.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_cursor.png' with 5 mip map levels
Ogre: Texture: sdk_tray.png: Loading 1 faces(PF_A8B8G8R8,64x64x1) with 6 generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x64x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_tray.png' with 6 mip map levels
Ogre: Texture: sdk_button_up.png: Loading 1 faces(PF_A8B8G8R8,128x32x1) with 7 generated mipmaps from Image. Internal format is PF_A8B8G8R8,128x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_button_up.png' with 7 mip map levels
Ogre: Texture: sdk_text_box.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_text_box.png' with 5 mip map levels
Ogre: Texture: sdk_mini_tray.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_mini_tray.png' with 5 mip map levels
Ogre: Texture: sdk_track.png: Loading 1 faces(PF_A8B8G8R8,16x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,16x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_track.png' with 5 mip map levels
Ogre: Texture: sdk_handle.png: Loading 1 faces(PF_A8B8G8R8,16x16x1) with 4 generated mipmaps from Image. Internal format is PF_A8B8G8R8,16x16x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_handle.png' with 4 mip map levels
Ogre: Texture: sdk_mini_text_box.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_mini_text_box.png' with 5 mip map levels
Ogre: Texture: sdk_label.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_label.png' with 5 mip map levels
Ogre: Texture: sdk_separator.png: Loading 1 faces(PF_A8B8G8R8,64x16x1) with 6 generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x16x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_separator.png' with 6 mip map levels
Ogre: Texture: sdk_logo.png: Loading 1 faces(PF_A8B8G8R8,128x64x1) with 7 generated mipmaps from Image. Internal format is PF_A8B8G8R8,128x64x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_logo.png' with 7 mip map levels
Ogre: Texture: sdk_shade.png: Loading 1 faces(PF_A8B8G8R8,64x48x1) with 6 generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x48x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_shade.png' with 6 mip map levels
Ogre: Texture: sdk_frame.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_frame.png' with 5 mip map levels
Ogre: Texture: sdk_mini_text_box_over.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_mini_text_box_over.png' with 5 mip map levels
Ogre: Texture: sdk_pulse.png: Loading 1 faces(PF_B8G8R8,8x1x1) with 3 generated mipmaps from Image. Internal format is PF_A8B8G8R8,8x1x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sdk_pulse.png' with 3 mip map levels
Ogre: Finished parsing scripts for resource group General
Ogre: Creating resources for group General
Ogre: All done
Ogre: Parsing scripts for resource group Internal
Ogre: Finished parsing scripts for resource group Internal
Ogre: Creating resources for group Internal
Ogre: All done
Ogre: Mesh: Loading Sinbad.mesh.
Ogre: Skeleton: Loading Sinbad.skeleton
Ogre: Texture: sinbad_body.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 generated mipmaps from Image. Internal format is PF_A8B8G8R8,512x512x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sinbad_body.tga' with 9 mip map levels
Ogre: Texture: sinbad_clothes.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 generated mipmaps from Image. Internal format is PF_A8B8G8R8,512x512x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sinbad_clothes.tga' with 9 mip map levels
Ogre: Texture: sinbad_sword.tga: Loading 1 faces(PF_B8G8R8,256x256x1) with 8 generated mipmaps from Image. Internal format is PF_A8B8G8R8,256x256x1.
Ogre: D3D11: Loading 2D Texture, image name : 'sinbad_sword.tga' with 8 mip map levels
Ogre: Warning: the mesh 'Sinbad.mesh' includes vertices with more than 4 bone assignments. The lowest weighted assignments beyond this limit have been removed, so your animation may look slightly different. To eliminate this, reduce the number of bone assignments per vertex on your mesh to 4.
Ogre: Font SdkTrays/Caption using texture size 256x256
Ogre: Texture: SdkTrays/CaptionTexture: Loading 1 faces(PF_BYTE_LA,256x256x1) with 0 generated mipmaps from Image. Internal format is PF_A8B8G8R8,256x256x1.
Ogre: Font SdkTrays/Value using texture size 512x256
Ogre: Texture: SdkTrays/ValueTexture: Loading 1 faces(PF_BYTE_LA,512x256x1) with 0 generated mipmaps from Image. Internal format is PF_A8B8G8R8,512x256x1.

```


## VS 2017

```bash

'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\ogre-helloworld.vs.exe'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntdll.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\kernel32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Program Files\AVAST Software\Avast\x64\aswhooka.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\KernelBase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreBites_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreMain_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\user32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\win32u.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\gdi32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\gdi32full.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcp_win.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ucrtbase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\shell32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcrt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\cfgmgr32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\SHCore.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\rpcrt4.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\combase.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\bcryptprimitives.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\windows.storage.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\advapi32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\sechost.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\shlwapi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\kernel.appcore.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\powrprof.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\profapi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreRTShaderSystem_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msvcp140d.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140d.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ucrtbased.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\OgreOverlay_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\SDL2.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\imm32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ole32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\oleaut32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\zlib.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\winmm.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\version.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\vcruntime140.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\winmmbase.dll'. Cannot find or open the PDB file.
Ogre: Creating resource group General
Ogre: Creating resource group Internal
Ogre: Creating resource group Autodetect
Ogre: SceneManagerFactory for type 'DefaultSceneManager' registered.
Ogre: Registering ResourceManager for type Material
Ogre: Registering ResourceManager for type Mesh
Ogre: Registering ResourceManager for type Skeleton
Ogre: MovableObjectFactory for type 'ParticleSystem' registered.
Ogre: ArchiveFactory for archive type FileSystem registered.
Ogre: ArchiveFactory for archive type Zip registered.
Ogre: ArchiveFactory for archive type EmbeddedZip registered.
Ogre: DDS codec registering
Ogre: ETC codec registering
Ogre: stb_image - v2.15 - public domain JPEG/PNG reader
Ogre: Supported formats: jpeg,jpg,png,bmp,psd,tga,gif,pic,ppm,pgm,hdr
Ogre: Registering ResourceManager for type HighLevelGpuProgram
Ogre: Registering ResourceManager for type Compositor
Ogre: MovableObjectFactory for type 'Entity' registered.
Ogre: MovableObjectFactory for type 'Light' registered.
Ogre: MovableObjectFactory for type 'BillboardSet' registered.
Ogre: MovableObjectFactory for type 'ManualObject' registered.
Ogre: MovableObjectFactory for type 'BillboardChain' registered.
Ogre: MovableObjectFactory for type 'RibbonTrail' registered.
Ogre: Loading library RenderSystem_GL_d
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Users\aphcoder\Documents\Virtual Machines\sharedfolder\ogre-ios-helloworld\ogre-helloworld.vs\x64\Debug\RenderSystem_GL_d.dll'. Symbols loaded.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\opengl32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\glu32.dll'. Cannot find or open the PDB file.
Ogre: Installing plugin: GL RenderSystem
Ogre: OpenGL Rendering Subsystem created.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\uxtheme.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\msctf.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ig7icd64.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igdusc64.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\wtsapi32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\dwmapi.dll'. Cannot find or open the PDB file.
The thread 0x29c0 has exited with code 0 (0x0).
The thread 0x8e8 has exited with code 0 (0x0).
The thread 0x24c4 has exited with code 0 (0x0).
The thread 0x2608 has exited with code 0 (0x0).
Ogre: Plugin successfully installed
Ogre: *-*-* OGRE Initialising
Ogre: *-*-* Version 1.10.11 (Xalafu)
Ogre: OverlayElementFactory for type Panel registered.
Ogre: OverlayElementFactory for type BorderPanel registered.
Ogre: OverlayElementFactory for type TextArea registered.
Ogre: Registering ResourceManager for type Font
Exception thrown at 0x00007FFD84B44008 in ogre-helloworld.vs.exe: Microsoft C++ exception: Ogre::FileNotFoundException at memory location 0x0000001C12CFE890.
Exception thrown at 0x00007FFD84B44008 in ogre-helloworld.vs.exe: Microsoft C++ exception: Ogre::FileNotFoundException at memory location 0x0000001C12CFE860.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\WinSxS\amd64_microsoft.windows.common-controls_6595b64144ccf1df_6.0.16299.248_none_15ced204935f55d7\comctl32.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\TextInputFramework.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\CoreUIComponents.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\CoreMessaging.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntmarta.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\WinTypes.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\clbcatq.dll'. Cannot find or open the PDB file.
Ogre: CPU Identifier & Features
Ogre: -------------------------
Ogre:  *   CPU ID: GenuineIntel: Intel(R) Core(TM) i5-3320M CPU @ 2.60GHz
Ogre:  *          SSE: yes
Ogre:  *         SSE2: yes
Ogre:  *         SSE3: yes
Ogre:  *        SSE41: yes
Ogre:  *        SSE42: yes
Ogre:  *          MMX: yes
Ogre:  *       MMXEXT: yes
Ogre:  *        3DNOW: no
Ogre:  *     3DNOWEXT: no
Ogre:  *         CMOV: yes
Ogre:  *          TSC: yes
Ogre:  *INVARIANT TSC: yes
Ogre:  *          FPU: yes
Ogre:  *          PRO: yes
Ogre:  *           HT: no
Ogre: -------------------------
Ogre: *** Starting Win32GL Subsystem ***
Ogre: Registering ResourceManager for type Texture
Ogre: GLRenderSystem::_createRenderWindow "OgreApplication", 640x480 windowed  miscParams: FSAA=0 externalWindowHandle=919240 gamma=No vsync=Yes 
Ogre: Supported WGL extensions: WGL_EXT_depth_float WGL_ARB_buffer_region WGL_ARB_extensions_string WGL_ARB_make_current_read WGL_ARB_pixel_format WGL_ARB_pbuffer WGL_EXT_extensions_string WGL_EXT_swap_control WGL_EXT_swap_control_tear WGL_ARB_multisample WGL_ARB_pixel_format_float WGL_ARB_framebuffer_sRGB WGL_ARB_create_context WGL_ARB_create_context_profile WGL_EXT_pixel_format_packed_float WGL_EXT_create_context_es_profile WGL_EXT_create_context_es2_profile WGL_NV_DX_interop WGL_ARB_create_context_robustness 
Ogre: GL_VERSION = 4.0.0 - Build 10.18.10.4425
Ogre: GL_VENDOR = Intel
Ogre: GL_RENDERER = Intel(R) HD Graphics 4000
Ogre: GL_EXTENSIONS = GL_EXT_blend_minmax GL_EXT_blend_subtract GL_EXT_blend_color GL_EXT_abgr GL_EXT_texture3D GL_EXT_clip_volume_hint GL_EXT_compiled_vertex_array GL_SGIS_texture_edge_clamp GL_SGIS_generate_mipmap GL_EXT_draw_range_elements GL_SGIS_texture_lod GL_EXT_rescale_normal GL_EXT_packed_pixels GL_EXT_texture_edge_clamp GL_EXT_separate_specular_color GL_ARB_multitexture GL_ARB_map_buffer_alignment GL_ARB_conservative_depth GL_EXT_texture_env_combine GL_EXT_bgra GL_EXT_blend_func_separate GL_EXT_secondary_color GL_EXT_fog_coord GL_EXT_texture_env_add GL_ARB_texture_cube_map GL_ARB_transpose_matrix GL_ARB_internalformat_query GL_ARB_internalformat_query2 GL_ARB_texture_env_add GL_IBM_texture_mirrored_repeat GL_EXT_multi_draw_arrays GL_SUN_multi_draw_arrays GL_NV_blend_square GL_ARB_texture_compression GL_3DFX_texture_compression_FXT1 GL_EXT_texture_filter_anisotropic GL_ARB_texture_border_clamp GL_ARB_point_parameters GL_ARB_texture_env_combine GL_ARB_texture_env_dot3 GL_ARB_texture_env_crossbar GL_EXT_texture_compression_s3tc GL_ARB_shadow GL_ARB_window_pos GL_EXT_shadow_funcs GL_EXT_stencil_wrap GL_ARB_vertex_program GL_EXT_texture_rectangle GL_ARB_fragment_program GL_EXT_stencil_two_side GL_ATI_separate_stencil GL_ARB_vertex_buffer_object GL_EXT_texture_lod_bias GL_ARB_occlusion_query GL_ARB_fragment_shader GL_ARB_shader_objects GL_ARB_shading_language_100 GL_ARB_texture_non_power_of_two GL_ARB_vertex_shader GL_NV_texgen_reflection GL_ARB_point_sprite GL_ARB_fragment_program_shadow GL_EXT_blend_equation_separate GL_ARB_depth_texture GL_ARB_texture_rectangle GL_ARB_draw_buffers GL_ARB_color_buffer_float GL_ARB_half_float_pixel GL_ARB_texture_float GL_ARB_pixel_buffer_object GL_EXT_framebuffer_object GL_ARB_draw_instanced GL_ARB_half_float_vertex GL_ARB_occlusion_query2 GL_EXT_draw_buffers2 GL_WIN_swap_hint GL_EXT_texture_sRGB GL_ARB_multisample GL_EXT_packed_float GL_EXT_texture_shared_exponent GL_ARB_texture_rg GL_ARB_texture_compression_rgtc GL_NV_conditional_render GL_ARB_texture_swizzle GL_EXT_texture_swizzle GL_ARB_texture_gather GL_ARB_sync GL_ARB_framebuffer_sRGB GL_EXT_packed_depth_stencil GL_ARB_depth_buffer_float GL_EXT_transform_feedback GL_ARB_transform_feedback2 GL_ARB_draw_indirect GL_EXT_framebuffer_blit GL_EXT_framebuffer_multisample GL_ARB_framebuffer_object GL_ARB_framebuffer_no_attachments GL_EXT_texture_array GL_EXT_texture_integer GL_ARB_map_buffer_range GL_ARB_texture_buffer_range GL_EXT_texture_buffer GL_EXT_texture_snorm GL_ARB_blend_func_extended GL_INTEL_performance_queries GL_INTEL_performance_query GL_ARB_copy_buffer GL_ARB_sampler_objects GL_NV_primitive_restart GL_ARB_seamless_cube_map GL_ARB_uniform_buffer_object GL_ARB_depth_clamp GL_ARB_vertex_array_bgra GL_ARB_shader_bit_encoding GL_ARB_draw_buffers_blend GL_ARB_geometry_shader4 GL_EXT_geometry_shader4 GL_ARB_texture_query_lod GL_ARB_explicit_attrib_location GL_ARB_draw_elements_base_vertex GL_ARB_instanced_arrays GL_ARB_base_instance GL_ARB_fragment_coord_conventions GL_EXT_gpu_program_parameters GL_ARB_texture_buffer_object_rgb32 GL_ARB_compatibility GL_ARB_texture_rgb10_a2ui GL_ARB_texture_multisample GL_ARB_vertex_type_2_10_10_10_rev GL_ARB_timer_query GL_ARB_tessellation_shader GL_ARB_vertex_array_object GL_ARB_provoking_vertex GL_ARB_sample_shading GL_ARB_texture_cube_map_array GL_EXT_gpu_shader4 GL_ARB_gpu_shader5 GL_ARB_gpu_shader_fp64 GL_ARB_shader_subroutine GL_ARB_transform_feedback3 GL_ARB_get_program_binary GL_ARB_separate_shader_objects GL_ARB_shader_precision GL_ARB_vertex_attrib_64bit GL_ARB_viewport_array GL_ARB_transform_feedback_instanced GL_ARB_compressed_texture_pixel_storage GL_ARB_shader_atomic_counters GL_ARB_shading_language_packing GL_ARB_shading_language_420pack GL_ARB_texture_storage GL_EXT_texture_storage GL_ARB_vertex_attrib_binding GL_ARB_multi_draw_indirect GL_ARB_program_interface_query GL_ARB_texture_storage_multisample GL_ARB_buffer_storage GL_ARB_debug_output GL_KHR_debug GL_ARB_arrays_of_arrays GL_INTEL_map_texture GL_ARB_texture_compression_bptc GL_ARB_ES2_compatibility GL_ARB_ES3_compatibility GL_ARB_robustness GL_EXT_texture_sRGB_decode GL_KHR_blend_equation_advanced GL_EXT_shader_integer_mix GL_ARB_stencil_texturing 
Ogre: ***************************
Ogre: *** GL Renderer Started ***
Ogre: ***************************
Ogre: Registering ResourceManager for type GpuProgram
Ogre: GLSL support detected
Ogre: GL: Using GL_EXT_framebuffer_object for rendering to textures (best)
Ogre: FBO PF_UNKNOWN depth/stencil support: D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_A8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_R5G6B5 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_B5G6R5 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_A4R4G4B4 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_A1R5G5B5 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_R8G8B8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_B8G8R8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_A8R8G8B8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_A8B8G8R8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_B8G8R8A8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_FLOAT16_RGB depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_FLOAT16_RGBA depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_FLOAT32_RGB depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_FLOAT32_RGBA depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_X8R8G8B8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_X8B8G8R8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_R8G8B8A8 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_SHORT_RGBA depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_R3G3B2 depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: FBO PF_SHORT_RGB depth/stencil support: D0S0 D0S1 D0S4 D0S8 D0S16 D16S0 D16S1 D16S4 D16S8 D16S16 D24S0 D24S1 D24S4 D24S8 D24S16 D32S0 D32S1 D32S4 D32S8 D32S16 Packed-D24S8 
Ogre: [GL] : Valid FBO targets PF_UNKNOWN PF_A8 PF_R5G6B5 PF_B5G6R5 PF_A4R4G4B4 PF_A1R5G5B5 PF_R8G8B8 PF_B8G8R8 PF_A8R8G8B8 PF_A8B8G8R8 PF_B8G8R8A8 PF_FLOAT16_RGB PF_FLOAT16_RGBA PF_FLOAT32_RGB PF_FLOAT32_RGBA PF_X8R8G8B8 PF_X8B8G8R8 PF_R8G8B8A8 PF_SHORT_RGBA PF_R3G3B2 PF_SHORT_RGB 
Ogre: RenderSystem capabilities
Ogre: -------------------------
Ogre: RenderSystem Name: OpenGL Rendering Subsystem
Ogre: GPU Vendor: intel
Ogre: Device Name: Intel(R) HD Graphics 4000
Ogre: Driver Version: 4.0.0.0
Ogre:  * Fixed function pipeline: yes
Ogre:  * Anisotropic texture filtering: yes
Ogre:  * Cube mapping: yes
Ogre:  * Hardware stencil buffer: yes
Ogre:    - Stencil depth: 8
Ogre:    - Two sided stencil support: yes
Ogre:    - Wrap stencil values: yes
Ogre:  * 32-bit index buffers: yes
Ogre:  * Vertex programs: yes
Ogre:  * Number of floating-point constants for vertex programs: 256
Ogre:  * Number of integer constants for vertex programs: 0
Ogre:  * Number of boolean constants for vertex programs: 0
Ogre:  * Fragment programs: yes
Ogre:  * Number of floating-point constants for fragment programs: 256
Ogre:  * Number of integer constants for fragment programs: 0
Ogre:  * Number of boolean constants for fragment programs: 0
Ogre:  * Geometry programs: yes
Ogre:  * Number of floating-point constants for geometry programs: 4096
Ogre:  * Number of integer constants for geometry programs: 0
Ogre:  * Number of boolean constants for geometry programs: 0
Ogre:  * Tessellation Hull programs: no
Ogre:  * Number of floating-point constants for tessellation hull programs: 52685
Ogre:  * Number of integer constants for tessellation hull programs: 52685
Ogre:  * Number of boolean constants for tessellation hull programs: 52685
Ogre:  * Tessellation Domain programs: no
Ogre:  * Number of floating-point constants for tessellation domain programs: 52685
Ogre:  * Number of integer constants for tessellation domain programs: 52685
Ogre:  * Number of boolean constants for tessellation domain programs: 52685
Ogre:  * Compute programs: no
Ogre:  * Number of floating-point constants for compute programs: 52685
Ogre:  * Number of integer constants for compute programs: 52685
Ogre:  * Number of boolean constants for compute programs: 52685
Ogre:  * Supported Shader Profiles: arbfp1 arbvp1 glsl glsl100 glsl110 glsl120
Ogre:  * Texture Compression: yes
Ogre:    - DXT: yes
Ogre:    - VTC: no
Ogre:    - PVRTC: no
Ogre:    - ATC: no
Ogre:    - ETC1: no
Ogre:    - ETC2: no
Ogre:    - BC4/BC5: no
Ogre:    - BC6H/BC7: no
Ogre:    - ASTC: no
Ogre:    - Mipmaps for compressed formats: yes
Ogre:  * Hardware Occlusion Query: yes
Ogre:  * User clip planes: yes
Ogre:  * VET_UBYTE4 vertex element type: yes
Ogre:  * Infinite far plane projection: yes
Ogre:  * Hardware render-to-texture: yes
Ogre:  * Floating point textures: yes
Ogre:  * Non-power-of-two textures: yes
Ogre:  * 1d textures: yes
Ogre:  * Volume textures: yes
Ogre:  * Multiple Render Targets: 8
Ogre:    - With different bit depths: yes
Ogre:  * Point Sprites: yes
Ogre:  * Hardware Gamma: yes
Ogre:  * Extended point parameters: yes
Ogre:  * Max Point Size: 255
Ogre:  * Vertex texture fetch: yes
Ogre:  * Number of texture units: 16
Ogre:  * Number of vertex attributes: 16
Ogre:  * Stencil buffer depth: 8
Ogre:  * Number of vertex blend matrices: 0
Ogre:    - Max vertex textures: 16
Ogre:    - Vertex textures shared: yes
Ogre:  * Render to Vertex Buffer : no
Ogre:  * Hardware Atomic Counters: no
Ogre:  * PBuffer support: yes
Ogre:  * Vertex Array Objects: no
Ogre:  * Separate shader objects: no
Ogre:  * GLSL SSO redeclare interface block: no
Ogre:  * Debugging/ profiling events: no
Ogre:  * Map buffer storage: yes
Ogre: DefaultWorkQueue('Root') initialising on thread main.
Ogre: Particle Renderer Type 'billboard' registered
Ogre: Added resource location 'Media' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/models' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/packs' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/packs/Sinbad.zip' of type 'Zip' to resource group 'General'
Ogre: Added resource location 'Media/packs/SdkTrays.zip' of type 'Zip' to resource group 'General'
Ogre: Added resource location 'Media/materials/programs/GLSL120' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/materials/programs/GLSL' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/RTShaderLib/materials' of type 'FileSystem' to resource group 'General'
Ogre: Added resource location 'Media/RTShaderLib/GLSL' of type 'FileSystem' to resource group 'General'
Ogre: Parsing scripts for resource group Autodetect
Ogre: Finished parsing scripts for resource group Autodetect
Ogre: Creating resources for group Autodetect
Ogre: All done
Ogre: Parsing scripts for resource group General
Ogre: Parsing script Sinbad.material
Ogre: Parsing script SdkTrays.material
Ogre: Parsing script DualQuaternionSkinning_Shadow.material
Ogre: Parsing script HardwareSkinningShadow.material
Ogre: Parsing script RTShaderSystem.material
Ogre: Parsing script TriplanarTexturing.material
Ogre: Parsing script SdkTrays.fontdef
Ogre: Parsing script SdkTrays.overlay
Ogre: Bad element attribute line: '# you can offset the image to change the cursor "hotspot"' for element SdkTrays/Cursor in overlay 
Ogre: Texture: sdk_cursor.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_tray.png: Loading 1 faces(PF_A8B8G8R8,64x64x1) with 6 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x64x1.
Ogre: Texture: sdk_button_up.png: Loading 1 faces(PF_A8B8G8R8,128x32x1) with 7 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,128x32x1.
Ogre: Texture: sdk_text_box.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_mini_tray.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_track.png: Loading 1 faces(PF_A8B8G8R8,16x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,16x32x1.
Ogre: Texture: sdk_handle.png: Loading 1 faces(PF_A8B8G8R8,16x16x1) with 4 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,16x16x1.
Ogre: Texture: sdk_mini_text_box.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_label.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_separator.png: Loading 1 faces(PF_A8B8G8R8,64x16x1) with 6 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x16x1.
Ogre: Texture: sdk_logo.png: Loading 1 faces(PF_A8B8G8R8,128x64x1) with 7 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,128x64x1.
Ogre: Texture: sdk_shade.png: Loading 1 faces(PF_A8B8G8R8,64x48x1) with 6 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,64x48x1.
Ogre: Texture: sdk_frame.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_mini_text_box_over.png: Loading 1 faces(PF_A8B8G8R8,32x32x1) with 5 hardware generated mipmaps from Image. Internal format is PF_A8B8G8R8,32x32x1.
Ogre: Texture: sdk_pulse.png: Loading 1 faces(PF_B8G8R8,8x1x1) with 3 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,8x1x1.
Ogre: Finished parsing scripts for resource group General
Ogre: Creating resources for group General
Ogre: All done
Ogre: Parsing scripts for resource group Internal
Ogre: Finished parsing scripts for resource group Internal
Ogre: Creating resources for group Internal
Ogre: All done
Ogre: Mesh: Loading Sinbad.mesh.
Ogre: Skeleton: Loading Sinbad.skeleton
Ogre: Texture: sinbad_body.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,512x512x1.
Ogre: Texture: sinbad_clothes.tga: Loading 1 faces(PF_B8G8R8,512x512x1) with 9 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,512x512x1.
Ogre: Texture: sinbad_sword.tga: Loading 1 faces(PF_B8G8R8,256x256x1) with 8 hardware generated mipmaps from Image. Internal format is PF_B8G8R8,256x256x1.
Ogre: Warning: the mesh 'Sinbad.mesh' includes vertices with more than 4 bone assignments. The lowest weighted assignments beyond this limit have been removed, so your animation may look slightly different. To eliminate this, reduce the number of bone assignments per vertex on your mesh to 4.
Ogre: Texture: Warning: Loading 1 faces(PF_R5G6B5,8x8x1) with 3 hardware generated mipmaps from Image. Internal format is PF_R5G6B5,8x8x1.
Ogre: Font SdkTrays/Caption using texture size 256x256
Ogre: Texture: SdkTrays/CaptionTexture: Loading 1 faces(PF_BYTE_LA,256x256x1) Internal format is PF_BYTE_LA,256x256x1.
Ogre: Font SdkTrays/Value using texture size 512x256
Ogre: Texture: SdkTrays/ValueTexture: Loading 1 faces(PF_BYTE_LA,512x256x1) Internal format is PF_BYTE_LA,512x256x1.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\dxgi.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\d3d11.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ResourcePolicyClient.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Unloaded 'C:\Windows\System32\ResourcePolicyClient.dll'
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\igd10iumd64.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\bcrypt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ncrypt.dll'. Cannot find or open the PDB file.
'ogre-helloworld.vs.exe' (Win32): Loaded 'C:\Windows\System32\ntasn1.dll'. Cannot find or open the PDB file.
The thread 0xc24 has exited with code 0 (0x0).
The thread 0x211c has exited with code 0 (0x0).
The thread 0x1384 has exited with code 0 (0x0).
The thread 0xcd0 has exited with code 0 (0x0).
The program '[9376] ogre-helloworld.vs.exe' has exited with code 0 (0x0).

```

