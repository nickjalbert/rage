//
//  RageView.h
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface RageView : UIViewController {
    NSMutableArray * img_array;
    IBOutlet UIImageView * my_img;
    IBOutlet UIImageView * animation_img;
}

@property (nonatomic, retain) IBOutlet UIImageView * my_img;
@property (nonatomic, retain) IBOutlet UIImageView * animation_img;
-(IBAction)rageOn:(id)sender;


@end
