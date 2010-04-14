/*
 * RageAppDelegate.h
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */


#import <UIKit/UIKit.h>

@interface RageAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow * window;
    UIViewController * viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow * window;
@property (nonatomic, retain) UIViewController * viewController;

@end

