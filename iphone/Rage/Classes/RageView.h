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
    UITextFieldDelegate,
    UIAlertViewDelegate> {
        MyCLController * locationController;
        UIAccelerometer * my_accelerometer;
        UIImageView * heat_img;
        
        UIAlertView * alert;
        UIAlertView * send_success;
        
        UILabel * rage_label;
        
        UITextField * my_comments;
        UITextField * my_uid;
        
        BOOL is_frozen;
        float curr_lat;
        float curr_lng;
    }

@property (nonatomic, retain) UIAccelerometer * my_accelerometer;
@property (nonatomic, retain) UIImageView * heat_img;
@property (nonatomic, retain) UIAlertView * alert;
@property (nonatomic, retain) UIAlertView * send_success;
@property (nonatomic, retain) IBOutlet UILabel * rage_label;
@property (nonatomic, retain) IBOutlet UITextField * my_uid;
@property (nonatomic, retain) UITextField  * my_comments;
@property (nonatomic) BOOL is_frozen;
@property (nonatomic) float curr_lat;
@property (nonatomic) float curr_lng;

-(IBAction)rageOn:(id)sender;
-(IBAction)rageFreezeToggle:(id)sender;
-(IBAction)httpOn:(id)sender;
-(IBAction)numberTyped:(id)sender;
-(IBAction)visitRageWeb:(id)sender;
-(void)sendRageToWeb;
-(void)locationUpdate:(CLLocation *) location;
-(void)locationError:(NSError *) error;
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
- (void)alertViewCancel:(UIAlertView *)alertView;
-(void)accelerometer:(UIAccelerometer *) accel didAccelerate:(UIAcceleration *) a;
-(void)bumpThermometer;
-(void)bumpThermometerByAmount:(int) amount;
-(void)increaseMercuryHeight:(int)amount;
-(void)freezeThermometer;
-(void) lazyInitializeAlert;
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
