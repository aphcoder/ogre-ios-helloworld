#ifndef __OgreApplication_h__
#define __OgreApplication_h__



#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

//#include <OgreStaticPluginLoader.h>


using namespace Ogre;

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
    //Ogre::StaticPluginLoader mStaticPluginLoader;
    
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
    
    void createCameraAndViewport();
    void createScene();

};

#endif // #ifndef __OgreApplication_h__


