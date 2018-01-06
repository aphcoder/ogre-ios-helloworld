#ifndef __OgreApplication_h__
#define __OgreApplication_h__



#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreStaticPluginLoader.h>

#include <OgreApplicationContext.h>
#include <OgreInput.h>

using namespace Ogre;
using namespace OgreBites;


class OgreApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener {
    
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

    
    void* mUiWindow;
    void* mUiView;
    unsigned int mWidth;
    unsigned int mHeight;
    
public:
    OgreApplication(void);
    virtual ~OgreApplication(void);
    
    void start(void* uiWindow, void* uiView, unsigned int width, unsigned int height);
    void stop();
    
    bool isStarted();
    void update(double elapsedTime);
    void draw();
    
    void setup();
    
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


