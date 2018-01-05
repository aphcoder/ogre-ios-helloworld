#ifndef __OgreApplication_h__
#define __OgreApplication_h__



#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreStaticPluginLoader.h>
#include <OgreRTShaderSystem.h>
#include <OgreMaterialManager.h>

using namespace Ogre;
using namespace OgreBites;


/** This class demonstrates basic usage of the RTShader system.
 It sub class the material manager listener class and when a target scheme callback
 is invoked with the shader generator scheme it tries to create an equivalent shader
 based technique based on the default technique of the given material.
 */
class ShaderGeneratorTechniqueResolverListener : public Ogre::MaterialManager::Listener
{
public:
    
    ShaderGeneratorTechniqueResolverListener(Ogre::RTShader::ShaderGenerator* pShaderGenerator);
    
    /** This is the hook point where shader based technique will be created.
     It will be called whenever the material manager won't find appropriate technique
     that satisfy the target scheme name. If the scheme name is out target RT Shader System
     scheme name we will try to create shader generated technique for it.
     */
    virtual Ogre::Technique* handleSchemeNotFound(unsigned short schemeIndex, const Ogre::String& schemeName, Ogre::Material* originalMaterial, unsigned short lodIndex, const Ogre::Renderable* rend);
protected:
    Ogre::RTShader::ShaderGenerator *mShaderGenerator;            // The shader generator instance.
};


class OgreApplication {
    
protected:
    Ogre::Root *mRoot;
    Ogre::SceneManager *mSceneManager;
    Ogre::RenderWindow *mRenderWindow;
    Ogre::Camera *mCamera;
    Ogre::Viewport* mViewport;
    
    Ogre::String mResourcesRoot;
    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;
    Ogre::String mOgreCfg;
    OgreBites::StaticPluginLoader mStaticPluginLoader;
    
    Ogre::RTShader::ShaderGenerator *mShaderGenerator; // The Shader generator instance.
    ShaderGeneratorTechniqueResolverListener *mMaterialMgrListener; // Shader generator material manager listener.
    
public:
    OgreApplication(void);
    virtual ~OgreApplication(void);
    
    void start(void* uiWindow, void* uiView, unsigned int width, unsigned int height);
    void stop();
    
    bool isStarted();
    void update(double elapsedTime);
    void draw();
    
private:
    void initializeRenderer(void *uiWindow, void *uiView,
                            unsigned int width, unsigned int height);
    void terminateRenderer();
    void loadResources();
    void unloadResources();
    
    bool initializeRTShaderSystem();
    void terminateRTShaderSystem();
    
    void createCameraAndViewport();
    void createScene();

};

#endif // #ifndef __OgreApplication_h__


