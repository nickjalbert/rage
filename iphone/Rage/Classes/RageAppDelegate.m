/*
 * RageAppDelegate.m
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */

#import "RageAppDelegate.h"
#import "RageView.h"

@implementation RageAppDelegate

@synthesize window;
@synthesize viewController;


- (BOOL)application:(UIApplication *)application 
        didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    RageView *avc = [[RageView alloc] 
        initWithNibName:@"RageView" bundle:[NSBundle mainBundle]];

    self.viewController = avc;
    [avc release];

    UIView *controllerView = [viewController view];
    [window addSubview:controllerView];

    [window makeKeyAndVisible];

    return YES;
}


- (void)dealloc {
    [window release];
    [viewController release];
    [super dealloc];
}


@end
