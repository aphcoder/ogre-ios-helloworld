#include "OgreApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT nCmdShow) {
#else
int main(int argc, char *argv[]) {
#endif
	try {
		OgreApplication app;
		app.initApp();
		app.getRoot()->startRendering();
		app.closeApp();
	} catch (Ogre::Exception& e) {

	}
	return 0;
}

