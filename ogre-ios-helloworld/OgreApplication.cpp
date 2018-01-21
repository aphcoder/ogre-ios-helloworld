#include "OgreApplication.h"

#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreSceneNode.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include <macUtils.h>
# else
#include <direct.h>
#endif

bool fileExists(std::string filepath) {
	return Ogre::FileSystemLayer::fileExists(filepath);
}


OgreApplication::OgreApplication(): OgreBites::ApplicationContext("OgreApplication") {
    mRoot = 0;
    mSceneManager = 0;
    mRenderWindow = 0;
    mCamera = 0;
    mViewport = 0;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    Ogre::String mResourcesRoot = Ogre::macBundlePath() + "/";
#else
	Ogre::String mResourcesRoot = _getcwd(NULL, 0);
	mResourcesRoot += "\\";
#endif
    Ogre::String mOgreCfg = mResourcesRoot + "ogre.cfg";
    bool ret = fileExists(mOgreCfg);
    
    Ogre::String mMediaFile = mResourcesRoot + "Media/packs/Sinbad.zip";
    ret = fileExists(mMediaFile);
    
   // OgreAssert(fileExists(mOgreCfg), "ogre.cfg");
	
}

OgreApplication::~OgreApplication(void) {
    delete mRoot;
}

void OgreApplication::setup() {
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    mRoot->setRenderSystem(mRoot->getRenderSystemByName("OpenGL ES 2.x Rendering Subsystem"));
#else
	mRoot->setRenderSystem(mRoot->getRenderSystemByName("Direct3D11 Rendering Subsystem"));
#endif
    //Process like: OgreBites::ApplicationContext::setup();
    mRoot->initialise(false);
    
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    Ogre::NameValuePairList miscParams;
    miscParams["colourDepth"] = "32";
    miscParams["contentScalingFactor"] = "2.0";
    miscParams["FSAA"] = "4";
    miscParams["Video Mode"] = Ogre::StringConverter::toString(mWidth) + "x" + Ogre::StringConverter::toString(mHeight);
    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)mUiWindow);
    miscParams["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)mUiView);
    
    NativeWindowPair ret = createWindow(mAppName, mWidth, mHeight, miscParams);
#else
	NativeWindowPair ret = createWindow(mAppName);
#endif
	mRenderWindow = ret.render;

    locateResources();
    initialiseRTShaderSystem();
    loadResources();
    
    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);

	createScene();
}

void OgreApplication::start(void* uiWindow, void* uiView, unsigned int width, unsigned int height) {

    mUiWindow = uiWindow;
    mUiView = uiView;
    mWidth = width;
    mHeight = height;
    
    ApplicationContext::initApp();
}

void OgreApplication::stop() {

}

bool OgreApplication::isStarted() {
    return mRoot != 0;
}

void OgreApplication::update(double elapseTime) {
    if (isStarted()) {
        if ((mRenderWindow) && (mRenderWindow->isActive())) {
            // TODO UPDATE
        }
    }
}

void OgreApplication::draw() {
    if (isStarted()) {
        if ((mRenderWindow) && (mRenderWindow->isActive())) {
            mRoot->renderOneFrame();
        }
    }
}

bool OgreApplication::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	mTrayMgr->frameRendered(evt);
	return true;
}

void OgreApplication::createCameraAndViewport() {
    // Create the camera
    mCamera = mSceneManager->createCamera("PlayerCam");
    
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,20));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);
    
    // create viewports
    // Create one viewport, entire window
    Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0xFF,0x00, 0xFF));
    
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

void OgreApplication::createDebugMenu() {
	// Process like ogre/Samples/Common/include/SdkSample.h
	mSceneManager->addRenderQueueListener(mOverlaySystem);
	// create a tray interface
	mTrayMgr = new TrayManager("SampleControls", mRenderWindow, this);
	// show stats and logo and hide the cursor
	mTrayMgr->showFrameStats(TL_BOTTOMLEFT);
	mTrayMgr->showLogo(TL_BOTTOMRIGHT);
	mTrayMgr->hideCursor();
}

void OgreApplication::createScene() {
    
    // Process like ApplicationContext::createDummyScene()
    //mWindows[0].render->removeAllViewports();
    mSceneManager = mRoot->createSceneManager("DefaultSceneManager", "DummyScene");

	createDebugMenu();
    createCameraAndViewport();

    mShaderGenerator->addSceneManager(mSceneManager);

    
    // Add entity
    // Sinbad mesh and materials are in packs/Sinbad.zip
    Ogre::Entity* ogreHead = mSceneManager->createEntity("Sinbad", "Sinbad.mesh");
    Ogre::SceneNode* rootNode = mSceneManager->getRootSceneNode();
    Ogre::SceneNode* headNode = rootNode->createChildSceneNode();
    headNode->attachObject(ogreHead);
    
    // Set ambient light
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    // Create a light
    Ogre::Light *light = mSceneManager->createLight("MainLight");
    light->setPosition(Vector3(20, 80, 50));
}
