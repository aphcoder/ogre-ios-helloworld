Visual Studio Community 2017
(Install Language English (Removed native or else))


user Env variable define  + Reboot PC
OGRE_SDK_ROOT=G:\PROJECTS\ogre\ogre-1.10.11




SET VS ALL PLATFORM CONFIGURATION (not only x86 or x64)


Prefer project in Debug/x64
Configuration Properties/C C++/SDL chgecks/No (avoid deprecated as errors)


INCLUDES PATH:
-------------------------------------------------
Configuration Properties/VC++ Directories/Include Directories 
(Check first the $OGRE_SDK_ROOT macro evaluation)

$(OGRE_SDK_ROOT)/OgreMain/include
$(OGRE_SDK_ROOT)/include
$(OGRE_SDK_ROOT)/OgreMain/include/iOS
$(OGRE_SDK_ROOT)/Components/Bites/include
$(OGRE_SDK_ROOT)/Components/RTShaderSystem/include
$(OGRE_SDK_ROOT)/ZZIPlib-master


$(OGRE_SDK_ROOT)/build/include
$(OGRE_SDK_ROOT)/build/Dependencies/include
$(OGRE_SDK_ROOT)/build/Dependencies/include/SDL2



LIBRAIRIES PATH (Debug mode):
-------------------------------------------------
Configuration Properties/VC++ Directories/Library Directories 
$(OGRE_SDK_ROOT)/build\lib\Debug


LIBRAIRIES (Debug mode):
-------------------------------------------------
Configuration Properties/Linker/Input/Additional Dependencies

OgreBites_d.lib
OgreHLMS_d.lib
OgreMain_d.lib
OgreMeshLodGenerator_d.lib
OgreOverlay_d.lib
OgrePaging_d.lib
OgreProperty_d.lib
OgreRTShaderSystem_d.lib
OgreTerrain_d.lib
OgreVolume_d.lib
Plugin_BSPSceneManager_d.lib
Plugin_OctreeSceneManager_d.lib
Plugin_OctreeZone_d.lib
Plugin_ParticleFX_d.lib
Plugin_PCZSceneManager_d.lib


POST BUILD EVENT COMMAND:
-------------------------------------------------
echo "OGRE CUSTOM: Copy content to $(TargetDir)"

copy /Y "$(OGRE_SDK_ROOT)\build\bin\debug\*.dll" "$(TargetDir)"
xcopy /E /Y "$(SolutionDir)..\ogre-ios-helloworld\resources\*" "$(TargetDir)"
del "$(TargetDir)resources.cfg"
del "$(TargetDir)plugins.cfg"
copy /Y "$(SolutionDir)..\ogre-ios-helloworld\resources\resources.cfg" "$(TargetDir)resources_d.cfg"
copy /Y "$(SolutionDir)plugins_d.cfg" "$(TargetDir)"
copy /Y "$(SolutionDir)ogre.cfg" "$(TargetDir)"



WORKING DIR: (for debugging)
-------------------------------------------------
Changed from $(ProjectDir) to $(TargetDir)


CUSTOM CLEAN:
-------------------------------------------------
Configuration Properties/Custom Build Step/General


Command line:
echo "OGRE CUSTOM: Delete $(TargetDir) content"

rd /s /q "$(TargetDir)"



Description:
Delete $(TargetDir) content

Outputs:
$(TargetDir)

Execute Before:
Clean



Ogre outputs here:
-------------------------------------------------
C:\Users\aphcoder\Documents\Ogre\OgreApplication
For log

