#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

- (void)startWithWindow:(UIWindow*)window;
- (void) update:(CADisplayLink*)displayLink;
- (void)stop;



@end

