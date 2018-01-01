#include "OgreApplication.h"

#include <OgreLogManager.h>
#include <OgreViewport.h>
#include <OgreConfigFile.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreSceneNode.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include <macUtils.h>
#endif

bool FileExists(std::string filepath) {
    FILE* fp = NULL;
    
    fp = fopen( filepath.c_str(), "rb");
    if(fp != NULL)
    {
        fclose(fp);
        return true;
    }
    
    return false;
}

OgreApplication::OgreApplication(void) {
    mRoot = 0;
    mSceneManager = 0;
    mRenderWindow = 0;
    mCamera = 0;
    mViewport = 0;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    mResourcesRoot = Ogre::macBundlePath() + "/";
#else
    mResourcesRoot = Ogre::StringUtil::BLANK;
#endif
    mResourcesCfg = mResourcesRoot + "resources.cfg";
    mPluginsCfg = mResourcesRoot + "plugins.cfg";
    
    bool ret = FileExists(mResourcesCfg);
    ret = ret;
    ret = FileExists(mPluginsCfg);
    ret = ret;
    
}

OgreApplication::~OgreApplication(void) {
    delete mRoot;
}

void OgreApplication::start(void* uiWindow, void* uiView, unsigned int width, unsigned int height) {
    initializeRenderer(uiWindow, uiView, width, height);
    createCameraAndViewport();
    
    //loadResources();
    
    //initializeRTShaderSystem();
    
    createScene();
}

void OgreApplication::stop() {
    //terminateRTShaderSystem();
    unloadResources();
    terminateRenderer();
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




void OgreApplication::initializeRenderer(void *uiWindow, void *uiView,
                                         unsigned int width, unsigned int height) {
    OgreAssert(!mRoot, "Existing root");
    OgreAssert(!mRenderWindow, "Existing render window");
    OgreAssert(!mSceneManager, "Existing scene manager");
    
    mRoot = new Ogre::Root("", mResourcesRoot + "ogre.cfg");
    //mRoot = new Ogre::Root(mPluginsCfg);
    //mStaticPluginLoader.load();
    
    Ogre::RenderSystem *renderSystem;
    const Ogre::RenderSystemList renderers =
    Ogre::Root::getSingleton().getAvailableRenderers();
    for (Ogre::RenderSystemList::const_iterator it = renderers.begin();
        it != renderers.end(); it++) {
        renderSystem = (*it);
        const  Ogre::String renderSystemName = renderSystem->getName();
        const char *renderSystemNameCstr = renderSystemName.c_str();
    }
    //renderSystem = (*renderers.begin());
    //Ogre::Root::getSingleton().setRenderSystem(renderSystem);
    
    Ogre::NameValuePairList params;
    params["colourDepth"] = "32";
    params["contentScalingFactor"] = "2.0";
    params["FSAA"] = "4";
    //params["Video Mode"] = Ogre::StringConverter::toString(width) + "x" + Ogre::StringConverter::toString(height);
    params["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)uiWindow);
    params["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)uiView);
    
    // Initialize w/o creating a renderwindow.
    mRoot->initialise(false);
    
    // Create the window and attach it to the given UI stuffs.
    mRenderWindow = mRoot->createRenderWindow("", width, height, false, &params);
    
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
}

void OgreApplication::terminateRenderer() {
    mRoot->queueEndRendering();
    //mStaticPluginLoader.unload();
    
    delete mRoot;
    mRoot = 0;
    mRenderWindow = 0;
    mSceneManager = 0;
}

void OgreApplication::loadResources() {
    Ogre::ConfigFile configFile;
    
    configFile.load(mResourcesCfg);
    
    Ogre::ConfigFile::SectionIterator sectionIter = configFile.getSectionIterator();
    Ogre::String secName, typeName, archName;
    while (sectionIter.hasMoreElements()) {
        secName = sectionIter.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = sectionIter.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator iter;
        for (iter = settings->begin(); iter != settings->end(); ++iter) {
            typeName = iter->first;
            archName = iter->second;
            
            // IOS specific
            archName = Ogre::String(mResourcesRoot + archName);

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    
    //Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreApplication::unloadResources() {
    
}



void OgreApplication::createCameraAndViewport() {
    /*
    OgreAssert(mSceneManager, "NULL scene manager");
    OgreAssert(!mCamera, "Existing camera");
    OgreAssert(!mViewport, "Existing viewport");
    
    mCamera = mSceneManager->createCamera("Camera");
    
    mViewport = mRenderWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.8f, 0.7f, 0.6f, 1.0f));
    
    resetCamera();
    
    mViewport->setCamera(mCamera);
    */
    
    
    // Create the camera
    mCamera = mSceneManager->createCamera("PlayerCam");
    
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);
    
    //-------------------------------------------------------------------------------------
    // create viewports
    // Create one viewport, entire window
    Ogre::Viewport* vp = mRenderWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0xFF,0));
    
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    
}

void OgreApplication::createScene() {
    
    // Create the scene
    Ogre::Entity* ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");
    
    Ogre::SceneNode* rootNode = mSceneManager->getRootSceneNode();
    Ogre::SceneNode* headNode = rootNode->createChildSceneNode();
    
    headNode->attachObject(ogreHead);
    
    // Set ambient light
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    
    // Create a light
    Ogre::Light *light = mSceneManager->createLight("MainLight");
    light->setPosition(20, 80, 50);
}
