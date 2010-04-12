//
//  RageAppDelegate.m
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "RageAppDelegate.h"
#import "RageView.h"

@implementation RageAppDelegate

@synthesize window;
@synthesize viewController;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
  RageView *avc = [[RageView alloc] initWithNibName:@"RageView" bundle:[NSBundle mainBundle]];
  
  self.viewController = avc;
  [avc release];
  
  UIView *controllerView = [viewController view];
  [window addSubview:controllerView];
    // Override point for customization after application launch
	
    [window makeKeyAndVisible];
	
	return YES;
}


- (void)dealloc {
    [window release];
  [viewController release];
    [super dealloc];
}


@end
