#ifndef __OgreApplication_h__
#define __OgreApplication_h__

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreTrays.h>

using namespace Ogre;
using namespace OgreBites;


class OgreApplication : public OgreBites::ApplicationContext, public OgreBites::InputListener, public OgreBites::TrayListener {

private:
    void *mUiWindow;
    void *mUiView;
    unsigned int mWidth;
    unsigned int mHeight;
    
protected:
    Ogre::SceneManager *mSceneMgr;
    Ogre::RenderWindow *mRenderWindow;
    Ogre::Camera *mCamera;
    Ogre::Viewport *mViewport;
	OgreBites::TrayManager *mTrayMgr;
    
public:
    OgreApplication(void);
    virtual ~OgreApplication(void);
    
    void start(void *uiWindow, void *uiView, unsigned int width, unsigned int height);
    void stop();
    
    bool isStarted();
    void update(double elapsedTime);
    void draw();
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    void setup();
    void createCameraAndViewport();
	void createDebugMenu();
    void createScene();


    bool keyPressed(const KeyboardEvent& evt);
    bool mousePressed(const MouseButtonEvent& evt);
    bool touchPressed(const TouchFingerEvent& evt);

};

#endif // #ifndef __OgreApplication_h__


