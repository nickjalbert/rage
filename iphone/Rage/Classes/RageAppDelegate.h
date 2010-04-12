//
//  RageAppDelegate.h
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RageAppDelegate : NSObject <UIApplicationDelegate> {
    UIWindow *window;
  UIViewController *viewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) UIViewController* viewController;

@end

