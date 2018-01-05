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

void OgreApplication::start(void* uiWindow, void* uiView, unsigned int width, unsigned int height) {
    initializeRenderer(uiWindow, uiView, width, height);
    createCameraAndViewport();
    
    loadResources();
    
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
    
    Ogre::NameValuePairList params;
    params["colourDepth"] = "32";
    params["contentScalingFactor"] = "2.0";
    params["FSAA"] = "4";
    params["Video Mode"] = Ogre::StringConverter::toString(width) + "x" + Ogre::StringConverter::toString(height);
    params["externalWindowHandle"] = Ogre::StringConverter::toString((unsigned long)uiWindow);
    params["externalViewHandle"] = Ogre::StringConverter::toString((unsigned long)uiView);
    
    // Initialize without creating a RenderWindow
    mRoot->initialise(false);
    
    // Create the window and attach it to the given UI stuffs.
    mRenderWindow = mRoot->createRenderWindow("", width, height, false, &params);
    
    mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
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

bool OgreApplication::initializeRTShaderSystem() {
#if 0
    if (Ogre::RTShader::ShaderGenerator::initialize())
    {
        mShaderGenerator = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        
        mShaderGenerator->addSceneManager(mSceneManager);
        
        // Setup core libraries and shader cache path.
        Ogre::StringVector groupVector = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
        Ogre::StringVector::iterator itGroup = groupVector.begin();
        Ogre::StringVector::iterator itGroupEnd = groupVector.end();
        Ogre::String shaderCoreLibsPath;
        Ogre::String shaderCachePath;
        
        for (; itGroup != itGroupEnd; ++itGroup)
        {
            Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(*itGroup);
            Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
            Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();
            bool coreLibsFound = false;
            
            // Try to find the location of the core shader lib functions and use it
            // as shader cache path as well - this will reduce the number of generated files
            // when running from different directories.
            for (; it != itEnd; ++it)
            {
                if ((*it)->archive->getName().find("RTShaderLib") != Ogre::String::npos)
                {
                    shaderCoreLibsPath = (*it)->archive->getName() + "/";
                    shaderCachePath = shaderCoreLibsPath;
                    coreLibsFound = true;
                    break;
                }
            }
            // Core libs path found in the current group.
            if (coreLibsFound)
                break;
        }
        
        // Core shader libs not found -> shader generating will fail.
        if (shaderCoreLibsPath.empty())
            return false;
        
        // Create and register the material manager listener.
        mMaterialMgrListener = new ShaderGeneratorTechniqueResolverListener(mShaderGenerator);
        Ogre::MaterialManager::getSingleton().addListener(mMaterialMgrListener);
        
        Ogre::MaterialPtr baseWhite = Ogre::MaterialManager::getSingleton().getByName("BaseWhite", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
        baseWhite->setLightingEnabled(false);
        
        mShaderGenerator->createShaderBasedTechnique("BaseWhite",
                                                     Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                                                     Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        
        mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
                                           "BaseWhite");
        baseWhite->getTechnique(0)->getPass(0)->setVertexProgram(
                                                                 baseWhite->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
        baseWhite->getTechnique(0)->getPass(0)->setFragmentProgram(
                                                                   baseWhite->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
        
        // creates shaders for base material BaseWhiteNoLighting using the RTSS
        mShaderGenerator->createShaderBasedTechnique("BaseWhiteNoLighting",
                                                     Ogre::MaterialManager::DEFAULT_SCHEME_NAME,
                                                     Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME);
        mShaderGenerator->validateMaterial(Ogre::RTShader::ShaderGenerator::DEFAULT_SCHEME_NAME,
                                           "BaseWhiteNoLighting");
        Ogre::MaterialPtr baseWhiteNoLighting = Ogre::MaterialManager::getSingleton().getByName("BaseWhiteNoLighting", Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
        baseWhiteNoLighting->getTechnique(0)->getPass(0)->setVertexProgram(
                                                                           baseWhiteNoLighting->getTechnique(1)->getPass(0)->getVertexProgram()->getName());
        baseWhiteNoLighting->getTechnique(0)->getPass(0)->setFragmentProgram(
                                                                             baseWhiteNoLighting->getTechnique(1)->getPass(0)->getFragmentProgram()->getName());
    }
#endif // 0
    
    return true;
}

void OgreApplication::terminateRTShaderSystem()
{
    mShaderGenerator->removeSceneManager(mSceneManager);
    
    // Restore default scheme.
    Ogre::MaterialManager::getSingleton().setActiveScheme(Ogre::MaterialManager::DEFAULT_SCHEME_NAME);
    
    // Unregister the material manager listener.
    if (mMaterialMgrListener != NULL)
    {
        Ogre::MaterialManager::getSingleton().removeListener(mMaterialMgrListener);
        delete mMaterialMgrListener;
        mMaterialMgrListener = NULL;
    }
    
    // Finalize RTShader system.
    if (mShaderGenerator != NULL)
    {
        //TODO Ogre::RTShader::ShaderGenerator::finalize();
        mShaderGenerator = NULL;
    }
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
    vp->setBackgroundColour(Ogre::ColourValue(0xFF,0x00, 0xFF));
    
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
