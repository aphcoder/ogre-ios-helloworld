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

OgreApplication::OgreApplication(): OgreBites::ApplicationContext("OgreApplication") {
    mRoot = 0;
    mSceneManager = 0;
    mRenderWindow = 0;
    mCamera = 0;
    mViewport = 0;
    
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
    mResourcesRoot = Ogre::macBundlePath() + "/";
    mPluginsCfg = Ogre::StringUtil::BLANK; // statically linked
#else
    mResourcesRoot = Ogre::StringUtil::BLANK;
    mPluginsCfg = mResourcesRoot + "plugins.cfg";
#endif
    mResourcesCfg = mResourcesRoot + "resources.cfg";
    mOgreCfg = mResourcesRoot + "ogre.cfg";
    
    OgreAssert(FileExists(mResourcesCfg), "resources.cfg");
    OgreAssert(FileExists(mOgreCfg), "ogre.cfg");
}

OgreApplication::~OgreApplication(void) {
    delete mRoot;
}

void OgreApplication::setup() {
    
    // Check/debug loaded render systems: (if empty => init error: no render system selected)
    mRoot = &(Root::getSingleton());
    
    Ogre::RenderSystem *renderSystem;
    const Ogre::RenderSystemList renderers =
    Ogre::Root::getSingleton().getAvailableRenderers();
    for (Ogre::RenderSystemList::const_iterator it = renderers.begin();
         it != renderers.end(); it++) {
        renderSystem = (*it);
        const  Ogre::String renderSystemName = renderSystem->getName();
        const char *renderSystemNameCstr = renderSystemName.c_str();
        (void)renderSystemNameCstr; // fix warning
    }
    renderSystem = (*renderers.begin());
    mRoot->setRenderSystem(renderSystem);
    
    
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
    mRenderWindow = ret.render;
#else
    createWindow(mAppName);
#endif
    
    locateResources();
    initialiseRTShaderSystem();
    loadResources();
    
    // adds context as listener to process context-level (above the sample level) events
    mRoot->addFrameListener(this);
}

void OgreApplication::start(void* uiWindow, void* uiView, unsigned int width, unsigned int height) {

    mUiWindow = uiWindow;
    mUiView = uiView;
    mWidth = width;
    mHeight = height;
    
    ApplicationContext::initApp();
    
    /*
    // Old style init
    initializeRenderer(uiWindow, uiView, width, height);
    loadResources();
    initialiseRTShaderSystem();
    */
    
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
    
    // No need to specify mPluginsCfg at first param (all are statically loaded)
    mRoot = new Ogre::Root(mPluginsCfg, mResourcesRoot + "ogre.cfg");
    
    // Load RenderSystem static libraries
    mStaticPluginLoader.load();
    
    // Check/debug loaded render systems: (if empty => init error: no render system selected)
    Ogre::RenderSystem *renderSystem;
    const Ogre::RenderSystemList renderers =
    Ogre::Root::getSingleton().getAvailableRenderers();
    for (Ogre::RenderSystemList::const_iterator it = renderers.begin();
        it != renderers.end(); it++) {
        renderSystem = (*it);
        const  Ogre::String renderSystemName = renderSystem->getName();
        const char *renderSystemNameCstr = renderSystemName.c_str();
        (void)renderSystemNameCstr; // fix warning
    }
    renderSystem = (*renderers.begin());
    mRoot->setRenderSystem(renderSystem);
    
    Ogre::NameValuePairList miscParams;
    
    miscParams["colourDepth"] = "32";
    miscParams["contentScalingFactor"] = "2.0";
    miscParams["FSAA"] = "4";
    miscParams["Video Mode"] = Ogre::StringConverter::toString(width) + "x" + Ogre::StringConverter::toString(height);
     
    miscParams["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)uiWindow);
    miscParams["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)uiView);
    
    // Initialize without creating a RenderWindow
    mRoot->initialise(false);
    
    // Create the window and attach it to the given UI stuffs.
    mRenderWindow = mRoot->createRenderWindow("", width, height, false, &miscParams);
}

void OgreApplication::terminateRenderer() {
    mRoot->queueEndRendering();
    mStaticPluginLoader.unload();
    
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

    // Create the camera
    mCamera = mSceneManager->createCamera("PlayerCam");
    
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0,0,150));
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

void OgreApplication::createScene() {
    
    // Process like ApplicationContext::createDummyScene()
    //mWindows[0].render->removeAllViewports();
    mSceneManager = mRoot->createSceneManager("DefaultSceneManager", "DummyScene");

    createCameraAndViewport();

    mShaderGenerator->addSceneManager(mSceneManager);

    
    // Add entity
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
