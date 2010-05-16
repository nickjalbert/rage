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
#import "MobileKVMessage.h"

@interface RageView : UIViewController <MyCLControllerDelegate,
    UIAccelerometerDelegate,
    UITextFieldDelegate> {
        MyCLController * locationController;
        UIAccelerometer * my_accelerometer;
        UIImageView * heat_img;
        
        UILabel * rage_label;
        
        UITextField * my_comments;
        UITextField * my_uid;
        
        BOOL is_frozen;
        float curr_lat;
        float curr_lng;
        
    }

@property (nonatomic, retain) UIAccelerometer * my_accelerometer;
@property (nonatomic, retain) UIImageView * heat_img;
@property (nonatomic, retain) IBOutlet UILabel * rage_label;
@property (nonatomic, retain) IBOutlet UITextField * my_uid;
@property (nonatomic, retain) IBOutlet  UITextField  * my_comments;
@property (nonatomic) BOOL is_frozen;
@property (nonatomic) float curr_lat;
@property (nonatomic) float curr_lng;

-(IBAction)rageOn:(id)sender;
-(IBAction)rageFreezeToggle:(id)sender;
-(IBAction)httpOn:(id)sender;
-(IBAction)numberTyped:(id)sender;
-(void)sendRageToWeb;
-(void)locationUpdate:(CLLocation *) location;
-(void)locationError:(NSError *) error;
-(void)accelerometer:(UIAccelerometer *) accel didAccelerate:(UIAcceleration *) a;
-(void)bumpThermometer;
-(void)bumpThermometerByAmount:(int) amount;
-(void)increaseMercuryHeight:(int)amount;
-(void)freezeThermometer;
-(void)unfreezeThermometer;
-(BOOL)textFieldShouldReturn:(UITextField *)thetxt;
-(NSString *) getUnixTimestampString; 
-(NSString *) getUIDString;
-(int) getRage;
-(NSString *) getRageString;
-(NSString *) getLngString;
-(NSString *) getLatString;
-(NSString *) getComment;
- (void) clearRageLabel;
- (void) setRageLabel;
- (void) cleanUpAfterSend;


@end
