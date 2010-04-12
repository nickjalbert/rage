//
//  RageView.h
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface RageView : UIViewController {
  UILabel* label;

}

@property (nonatomic, retain) IBOutlet UILabel * label;

-(IBAction)rageOn:(id)sender;

@end
