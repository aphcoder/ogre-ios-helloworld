#import "OgreView.h"

#import <QuartzCore/CAEAGLLayer.h>


#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreCamera.h>

@implementation OgreView

@synthesize mWindowName;
@synthesize mRenderWindow;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (void)layoutSubviews {
    
    if (mRenderWindow != NULL) {
        unsigned int width = (uint)self.bounds.size.width;
        unsigned int height = (uint)self.bounds.size.height;
        
        // Resize the window
        mRenderWindow->resize(width, height);
        
        // After rotation the aspect ratio of the viewport has changed, update that as well.
        if(mRenderWindow->getNumViewports() > 0) {
            Ogre::Viewport *viewPort = mRenderWindow->getViewport(0);
            viewPort->getCamera()->setAspectRatio((Ogre::Real) width / (Ogre::Real) height);
        }
    }
}

@end
