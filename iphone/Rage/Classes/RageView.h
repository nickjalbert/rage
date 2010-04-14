//
//  RageView.h
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MyCLController.h"

@interface RageView : UIViewController <MyCLControllerDelegate>{
  MyCLController * locationController;
    NSMutableArray * img_array;
  IBOutlet UILabel *  locationLabel;
    IBOutlet UIImageView * my_img;
    IBOutlet UIImageView * animation_img;
  BOOL next_direction_is_up;
  CALayer * mylayer;
}

@property (nonatomic, retain) IBOutlet UIImageView * my_img;
@property (nonatomic, retain) IBOutlet UIImageView * animation_img;
@property (nonatomic, retain) IBOutlet UILabel * locationLabel;
-(IBAction)rageOn:(id)sender;
-(void)locationUpdate:(CLLocation *) location;
-(void)locationError:(NSError *) error;

@end
