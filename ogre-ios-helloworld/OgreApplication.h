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

private:
    void* mUiWindow;
    void* mUiView;
    unsigned int mWidth;
    unsigned int mHeight;
    
protected:
    Ogre::SceneManager *mSceneManager;
    Ogre::RenderWindow *mRenderWindow;
    Ogre::Camera *mCamera;
    Ogre::Viewport* mViewport;
    

public:
    OgreApplication(void);
    virtual ~OgreApplication(void);
    
    void start(void* uiWindow, void* uiView, unsigned int width, unsigned int height);
    void stop();
    
    bool isStarted();
    void update(double elapsedTime);
    void draw();
    
    void setup();
    void createCameraAndViewport();
    void createScene();



};

#endif // #ifndef __OgreApplication_h__


