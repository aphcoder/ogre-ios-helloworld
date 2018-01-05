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

* [X] Resolve Cannot initialise - no render system has been selected (DONE with SIMU)
* [] Fix Shader initialization due to OgreMesh material
* [] Have OgreMesh properly displayed on iphone simulator
* [] Have OgreMesh properly displayed on iphone device
* [] Port application to new style Ogre Bites


## Last run logs/status


```
SIMU: Expected Fushia screen color afer properly static lib loading and viewport rendering.

```


```
2018-01-05 08:22:27.599789+0100 ogre-ios-helloworld[48568:1711746] +[CATransaction synchronize] called within transaction
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
CPU Identifier & Features
-------------------------
*   CPU ID: GenuineIntel: Intel(R) Core(TM) i5-7267U CPU @ 3.10GHz
*          SSE: yes
*         SSE2: yes
*         SSE3: yes
*        SSE41: yes
*        SSE42: yes
*          MMX: yes
*       MMXEXT: yes
*        3DNOW: no
*     3DNOWEXT: no
*         CMOV: yes
*          TSC: yes
*INVARIANT TSC: yes
*          FPU: yes
*          PRO: yes
*           HT: no
-------------------------
Registering ResourceManager for type Texture
GLES2RenderSystem::_createRenderWindow "", 320x480 windowed  miscParams: FSAA=4 Video Mode=320x480 colourDepth=32 contentScalingFactor=2.0 externalViewHandle=140283965609568 externalWindowHandle=140283962506208
iOS: Using an external window handle
iOS: Using an external view handle
iOS: Window created 320 x 480 with backing store size 320 x 480 using content scaling factor 1.0
GL_VERSION = 3.0.0.0
GL_VENDOR = Apple Inc.
GL_RENDERER = Apple Software Renderer
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
Device Name: Apple Software Renderer
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
* Number of floating-point constants for geometry programs: 0
* Number of integer constants for geometry programs: 0
* Number of boolean constants for geometry programs: 0
* Tessellation Hull programs: no
* Number of floating-point constants for tessellation hull programs: 0
* Number of integer constants for tessellation hull programs: 0
* Number of boolean constants for tessellation hull programs: 0
* Tessellation Domain programs: no
* Number of floating-point constants for tessellation domain programs: 0
* Number of integer constants for tessellation domain programs: 0
* Number of boolean constants for tessellation domain programs: 0
* Compute programs: no
* Number of floating-point constants for compute programs: 0
* Number of integer constants for compute programs: 0
* Number of boolean constants for compute programs: 0
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
* Multiple Render Targets: 8
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
Creating resource group Bootstrap
Added resource location '/Users/aphcoder/Library/Developer/CoreSimulator/Devices/426054DF-601C-45B6-9EA6-108EFAD6F034/data/Containers/Bundle/Application/446A7F99-F023-419E-A1F9-2D254D0937C4/ogre-ios-helloworld.app/media/packs/SdkTrays.zip' of type 'Zip' to resource group 'Bootstrap'
Parsing scripts for resource group Bootstrap
Parsing script SdkTrays.material
Finished parsing scripts for resource group Bootstrap
Creating resources for group Bootstrap
All done
Parsing scripts for resource group General
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
Mesh: Loading ogrehead.mesh.
2018-01-05 08:22:27.847894+0100 ogre-ios-helloworld[48568:1711746] ViewController::startWithWindow Exception: FileNotFoundException: Cannot locate resource ogrehead.mesh in resource group OgreAutodetect. in ResourceGroupManager::openResource at /Users/aphcoder/ogre/ogre-1.10.11/OgreMain/src/OgreResourceGroupManager.cpp (line 708)

```




