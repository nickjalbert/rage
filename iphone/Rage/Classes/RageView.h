/*
 * RageView.h
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */

#import <UIKit/UIKit.h>
#import "MyCLController.h"

@interface RageView : UIViewController <MyCLControllerDelegate>{
    MyCLController * locationController;
    IBOutlet UILabel *  locationLabel;
    UIImageView * heat_img;
}

@property (nonatomic, retain) UIImageView * heat_img;
@property (nonatomic, retain) IBOutlet UILabel * locationLabel;
-(IBAction)rageOn:(id)sender;
-(void)locationUpdate:(CLLocation *) location;
-(void)locationError:(NSError *) error;

@end
