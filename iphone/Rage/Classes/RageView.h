/*
 * RageView.h
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 *
 * Accelerometer code based on "iPhone Tutorial - Reading the Accelerometer"
 * www.switchonthecode.com/tuorials/iphone-tutorial-reading-the-accelerometer
 *
 */

#import <UIKit/UIKit.h>
#import "MyCLController.h"

@interface RageView : UIViewController <MyCLControllerDelegate, UIAccelerometerDelegate, UITextFieldDelegate>{
    MyCLController * locationController;
    IBOutlet UILabel *  locationLabel;
  UITextView * my_textview;
  IBOutlet UITextField * my_textfield;
    UIImageView * heat_img;
    IBOutlet UILabel * labelX;
    IBOutlet UILabel * labelY;
    IBOutlet UILabel * labelZ;
    UIAccelerometer * my_accelerometer;
  NSOperationQueue * queue;
}

@property (nonatomic, retain) IBOutlet UILabel * labelX;
@property (nonatomic, retain) IBOutlet UILabel * labelY;
@property (nonatomic, retain) IBOutlet UILabel * labelZ;
@property (nonatomic, retain) IBOutlet UITextField * my_textfield;
@property (nonatomic, retain) IBOutlet  UITextView  * my_textview;
@property (nonatomic, retain) UIAccelerometer * my_accelerometer;
@property (nonatomic, retain) UIImageView * heat_img;
@property (nonatomic, retain) NSOperationQueue * queue;
@property (nonatomic, retain) IBOutlet UILabel * locationLabel;

-(IBAction)rageOn:(id)sender;
-(IBAction)httpOn:(id)sender;
-(void)locationUpdate:(CLLocation *) location;
-(void)locationError:(NSError *) error;
-(void)accelerometer:(UIAccelerometer *) accel didAccelerate:(UIAcceleration *) a;
-(BOOL)textFieldShouldReturn:(UITextField *)thetxt;

@end
