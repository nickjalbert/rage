/*
 * RageView.m
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */

#import "RageView.h"

#define PIXEL_INCREASE_PER_RAGE 15
#define RAGE_DECAY_SPEED 1.5
#define ACCEL_THRESHOLD 1.7

@implementation RageView

@synthesize heat_img;
@synthesize my_accelerometer;
@synthesize my_uid;
@synthesize my_comments;
@synthesize is_frozen;
@synthesize curr_lat;
@synthesize curr_lng;
@synthesize rage_label;
@synthesize alert;
@synthesize send_success;


- (void)viewDidLoad {
    [super viewDidLoad];

    self.is_frozen = NO;
    
    self.my_uid.text = @"1337";
    self.rage_label.text = @"";
    
    /* Alert View */
    alert = nil;
    send_success = nil;
    
    /* Accelerometer Tracking */
    self.my_accelerometer = [UIAccelerometer sharedAccelerometer];
    self.my_accelerometer.updateInterval = .1;
    self.my_accelerometer.delegate = self;

    /* Location Tracking Interface */
    locationController = [[MyCLController alloc] init];
    locationController.delegate = self;
    [locationController.locationManager startUpdatingLocation];

    /*Thermometer Interface */
    UIImageView * bkg = 
        [[UIImageView alloc] initWithFrame:CGRectMake(140, 120, 42, 220)];
    [bkg setBackgroundColor:[UIColor colorWithRed:(1.0) green:(253.0f/255.0f) blue:(253.0f/255.0f) alpha:1.0]];

    [self.view addSubview:bkg];

    heat_img = [[UIImageView alloc] initWithFrame:CGRectMake(140,350,42,-20)];
    [heat_img setBackgroundColor:[UIColor colorWithRed:(221.0f/255.0f) green:(21.0f/255.0f) blue:(21.0f/255.0f) alpha:1.0]];
    [self.view addSubview:heat_img];

    [self.view sendSubviewToBack:heat_img];
    [self.view sendSubviewToBack:bkg];

    [bkg release];
}

- (void)accelerometer:(UIAccelerometer *) accelerometer 
        didAccelerate:(UIAcceleration *) acceleration {
    if (self.is_frozen == YES) {
        return;
    }
    if (abs(acceleration.z) > ACCEL_THRESHOLD) {
        [self bumpThermometer];
        return;
    }
    if (abs(acceleration.y) > ACCEL_THRESHOLD) {
        [self bumpThermometer];
        return;
    }
    if (abs(acceleration.x) > ACCEL_THRESHOLD) {
        [self bumpThermometer];
        return;
    }
}

- (IBAction) httpOn:(id)sender {
    [self sendRageToWeb];
}

-(IBAction)visitRageWeb:(id)sender {
    NSURL *rage_web = [NSURL URLWithString:@"http://rage.calmensvball.com"];
    [[UIApplication sharedApplication] openURL:rage_web];
}


-(IBAction)numberTyped:(id)sender {
    if ([my_uid.text length] > 4) {
        my_uid.text = [my_uid.text substringToIndex:4];
    }
    
    if ([my_uid.text length] == 4) {
        [my_uid resignFirstResponder];
    }
}


-(NSString *) getUnixTimestampString {
    float unixstamp = [[NSDate date] timeIntervalSince1970];
    NSString * timestamp = [NSString stringWithFormat:@"%0.0f", unixstamp];
    return timestamp;
}

-(NSString *) getUIDString {
    return my_uid.text;
}

-(int) getRage {
    CALayer * heat_layer = [heat_img layer];
    CALayer * heat_presentation = [heat_layer presentationLayer];
    CGRect current_disp = [heat_presentation bounds];
    
    float current_height = CGRectGetHeight(current_disp) - 20;
    float rage_percent = (current_height/190.0) * 100.0;
    return (int) rage_percent;
}

-(NSString *) getRageString {
    int rage = [self getRage];
    return [NSString stringWithFormat:@"%d", rage];
}

-(NSString *) getLngString {
    return [NSString stringWithFormat:@"%f", curr_lng];
}

-(NSString *) getLatString {
    return [NSString stringWithFormat:@"%f", curr_lat];
}

-(NSString *) getComment {
    [self lazyInitializeAlert];
    if (my_comments.text.length > 140) {
       return [my_comments.text substringToIndex:140]; 
    }
    return my_comments.text;
}

-(void)sendRageToWeb {
    NSString * target = [NSString stringWithString:@"http://rage.calmensvball.com/add.php5"];
    MobileKVMessage* msg = [MobileKVMessage getNewMobileKVMessage:target];
    
    NSString * timestamp = [self getUnixTimestampString];
    [msg addKeyValue:@"timestamp" andValue:timestamp];
    
    NSString * uid = [self getUIDString];
    [msg addKeyValue:@"uid" andValue:uid];
    
    NSString * rage = [self getRageString];
    [msg addKeyValue:@"rage" andValue:rage];
    
    NSString * lat = [self getLatString];
    [msg addKeyValue:@"lat" andValue:lat];
    
    NSString * lng = [self getLngString];
    [msg addKeyValue:@"long" andValue:lng];
    
    NSString * comment = [self getComment];
    [msg addKeyValue:@"comment" andValue:comment];
    
    [msg send];
}

- (IBAction)rageOn:(id)sender {
    [self bumpThermometer];
}

- (void) clearRageLabel {
    rage_label.text = @"";
}

- (void) setRageLabel {
    rage_label.text = [self getRageString];
    rage_label.text = [rage_label.text stringByAppendingString:@"%"];
}

- (void) cleanUpAfterSend {
    [self lazyInitializeAlert];
    my_comments.text = @"";
}


- (void) lazyInitializeAlert {
    if (alert == nil) {
        alert = [[UIAlertView alloc] initWithTitle:@"Let's Rage" message:@"\n" delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Send!", nil];
        my_comments = [[UITextField alloc] initWithFrame:CGRectMake(12, 45, 260, 25)];
        my_comments.placeholder = @"Reason for Rage";
        my_comments.textAlignment = UITextAlignmentCenter;
        my_comments.delegate = self;
        CGAffineTransform myTransform = CGAffineTransformMakeTranslation(0, 60);
        [alert setTransform:myTransform];
        [my_comments setBackgroundColor:[UIColor whiteColor]];
        [alert addSubview:my_comments];
    }
    
    if (send_success == nil) {
        send_success = [[UIAlertView alloc] initWithTitle:@"Rage Uploaded!" message:@"" delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil];
    }
}

-(IBAction)rageFreezeToggle:(id)sender {
    if (self.is_frozen == NO) {
        [self freezeThermometer];
        [self setRageLabel];
        [self lazyInitializeAlert];
        [alert show];
        [self cleanUpAfterSend];
    } else {
        [self clearRageLabel];
        [self unfreezeThermometer];
    }
}

-(void)bumpThermometerByAmount:(int) amount {
    if (self.is_frozen == YES) {
        return;
    }

    [self increaseMercuryHeight:amount];

    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration: RAGE_DECAY_SPEED];
    [heat_img setFrame:CGRectMake(140,350,42,-20)];
    [UIView commitAnimations];
}

-(void)bumpThermometer {
    int rage = [self getRage];
    int bumpAmount = PIXEL_INCREASE_PER_RAGE;
    if (rage >= 50) {
        bumpAmount = bumpAmount/2;
    }
    if (rage >= 75) {
        bumpAmount = bumpAmount/2;
    }
    if (rage >= 85) {
        bumpAmount = bumpAmount/2;
    }
    
    [self bumpThermometerByAmount:bumpAmount];
}

-(void)increaseMercuryHeight:(int) amount {
    CALayer * heat_layer = [heat_img layer];
    CALayer * heat_presentation = [heat_layer presentationLayer];
    CGRect current_disp = [heat_presentation bounds];

    float new_height = CGRectGetHeight(current_disp);
    new_height = new_height + amount;
    new_height = new_height * -1;
    if (new_height < -210) {
        new_height = -210;
    }

    [heat_img setFrame:CGRectMake(140, 350, 42, new_height)];
}

-(void)freezeThermometer {
    [self increaseMercuryHeight:0];
    [[heat_img layer] removeAllAnimations];
    self.is_frozen = YES;
}

-(void)unfreezeThermometer {
    self.is_frozen = NO;
    [self bumpThermometerByAmount:0];
}

-(void)locationUpdate:(CLLocation *) location {
    curr_lat = location.coordinate.latitude;
    curr_lng = location.coordinate.longitude;
}

-(void)locationError:(NSError *) error{ }

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

-(BOOL)textFieldShouldReturn:(UITextField *)thetxt {
    if (thetxt == my_uid) {
        [my_uid resignFirstResponder];
    }
    if (thetxt == my_comments) {
        [my_comments resignFirstResponder];
    }
    return YES;
}

- (void)dealloc {
    [locationController release];
    [my_accelerometer release];
    [alert release];
    [heat_img release];
    [my_comments release];
    [my_uid release];
    [super dealloc];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (alertView == alert) {
        if (buttonIndex == 0) {
            NSLog(@"Cancel");
        } else if (buttonIndex == 1) {
            NSLog(@"Send");
            [self sendRageToWeb];
            [send_success show];
        }
        [self cleanUpAfterSend];
    }
    
}
- (void)alertViewCancel:(UIAlertView *)alertView {
    [self cleanUpAfterSend];
}
@end
