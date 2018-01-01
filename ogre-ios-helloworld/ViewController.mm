#import "ViewController.h"
#import "OgreView.h"
#import "OgreApplication.h"

// Privat fields
@interface ViewController () {
    
    // Ogre3D application
    OgreApplication application;
    
    // Gameloop timer / Framerate computing
    CADisplayLink *displayLink;
    NSDate *date;
    double startTime;
    double lastFrameTime;
}

@property (retain) OgreView *ogreView;

@end

@implementation ViewController

@synthesize ogreView;


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (void)startWithWindow:(UIWindow*)window {

    unsigned int width  = self.view.frame.size.width;
    unsigned int height = self.view.frame.size.height;
    
    ogreView = [[OgreView alloc] initWithFrame:CGRectMake(0, 0, width, height)];
    [self.view addSubview:ogreView];
    
    // Gameloop timer init
    displayLink = [CADisplayLink displayLinkWithTarget:self
                                             selector:@selector(update:)];
    [displayLink addToRunLoop:[NSRunLoop mainRunLoop]
                      forMode:NSRunLoopCommonModes]; // High priority // (default=NSDefaultRunLoopMode)

    try {
        application.start((__bridge void *)window, (__bridge void *)ogreView, width, height);
    } catch (Ogre::Exception& e) {
        NSLog(@"ViewController::startWithWindow Exception: %s", e.getFullDescription().c_str());
    }
    
    startTime = 0;
    lastFrameTime = 1;
    date = [[NSDate alloc] init];
    lastFrameTime = -[date timeIntervalSinceNow];
}


- (void)stop {
    
    try {
        application.stop();
    } catch(Ogre::Exception& e) {
        NSLog(@"ViewController::stop Exception: %s", e.getFullDescription().c_str());
    }
    
    // ARC mode
    date = nil;
    [displayLink invalidate];
    displayLink = nil;
    ogreView = nil;
}

// Get called when the screen updates
- (void) update:(CADisplayLink*)displayLink {
    double currentFrameTime = -[date timeIntervalSinceNow];
    double elapsedFrametime = currentFrameTime - lastFrameTime;
    
    application.update(elapsedFrametime);
    application.draw();
    
    lastFrameTime = currentFrameTime;
}

@end
