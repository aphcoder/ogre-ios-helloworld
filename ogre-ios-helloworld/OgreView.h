#import <UIKit/UIKit.h>

#import <OgreString.h>
#import <OgreRenderWindow.h>

@interface OgreView : UIView {
    Ogre::String mWindowName;
    Ogre::RenderWindow* mRenderWindow;
}

@property Ogre::String mWindowName;
@property Ogre::RenderWindow* mRenderWindow;

@end
