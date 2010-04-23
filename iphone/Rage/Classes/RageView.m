/*
 * RageView.m
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */

#import "RageView.h"
#import "ASIFormDataRequest.h"

#define PIXEL_INCREASE_PER_RAGE 15
#define RAGE_DECAY_SPEED 1.5
#define ACCEL_THRESHOLD 1.7

@implementation RageView

@synthesize heat_img;
@synthesize locationLabel;
@synthesize my_accelerometer;
@synthesize labelX;
@synthesize labelY;
@synthesize labelZ;
@synthesize my_textview;
@synthesize queue;
@synthesize my_textfield;
@synthesize is_frozen;

- (void)viewDidLoad {
    [super viewDidLoad];

    self.is_frozen = NO;
  
    /* Accelerometer Tracking */
    self.my_accelerometer = [UIAccelerometer sharedAccelerometer];
    self.my_accelerometer.updateInterval = .1;
    self.my_accelerometer.delegate = self;
    labelX.text = [NSString stringWithString:@"X:  "];
    labelY.text = [NSString stringWithString:@"Y:  "];
    labelZ.text = [NSString stringWithString:@"Z:  "];

    /* Location Tracking Interface */
    locationController = [[MyCLController alloc] init];
    locationController.delegate = self;
    [locationController.locationManager startUpdatingLocation];

    /*Thermometer Interface */
    UIImageView * bkg = 
        [[UIImageView alloc] initWithFrame:CGRectMake(140, 65, 42, 220)];
    [bkg setBackgroundColor:[UIColor colorWithRed:(1.0) green:(253.0f/255.0f) blue:(253.0f/255.0f) alpha:1.0]];

    [self.view addSubview:bkg];

    heat_img = [[UIImageView alloc] initWithFrame:CGRectMake(140,285,42,-20)];
    [heat_img setBackgroundColor:[UIColor colorWithRed:(221.0f/255.0f) green:(21.0f/255.0f) blue:(21.0f/255.0f) alpha:1.0]];
    [self.view addSubview:heat_img];

    [self.view sendSubviewToBack:heat_img];
    [self.view sendSubviewToBack:bkg];

    [bkg release];
}

- (void)accelerometer:(UIAccelerometer *) accelerometer 
        didAccelerate:(UIAcceleration *) acceleration {
    labelX.text = [NSString stringWithFormat:@"X:%f", acceleration.x];
    labelY.text = [NSString stringWithFormat:@"Y:%f", acceleration.y];
    labelZ.text = [NSString stringWithFormat:@"Z:%f", acceleration.z];
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

-(void)sendRageToWeb {
  if (![self queue]) {
    [self setQueue:[[[NSOperationQueue alloc] init] autorelease]];
  }
  NSURL * url = [NSURL URLWithString:@"http://www.nickjalbert.com/test.php"];
  ASIFormDataRequest* request = [ASIFormDataRequest requestWithURL:url];
  NSString * my_name = [NSString stringWithFormat:@"%@", my_textfield.text];
  if ([my_name length] == 0) {
    my_name = [NSString stringWithString:@"Anon"];
  }
  [request setPostValue:my_name forKey:@"name"];
  
  CALayer * heat_layer = [heat_img layer];
  CALayer * heat_presentation = [heat_layer presentationLayer];
  CGRect current_disp = [heat_presentation bounds];
  
  float current_height = CGRectGetHeight(current_disp) - 20;
  NSString * my_rage = [NSString stringWithFormat:@"%.1f", current_height];
  [request setPostValue:my_rage forKey:@"rage"];
  [request setDelegate:self];
  [request setDidFinishSelector:@selector(requestDone:)];
  [request setDidFailSelector:@selector(requestWentWrong:)];
  [[self queue] addOperation:request];}

- (void)requestDone:(ASIHTTPRequest *) request {
    NSString * response = [request responseString];
    my_textview.text = @"";
    my_textview.text = response;
}

- (void)requestWentWrong:(ASIHTTPRequest *) request { }

- (IBAction)rageOn:(id)sender {
    [self bumpThermometer];
}


-(IBAction)rageFreezeToggle:(id)sender {
    if (self.is_frozen == NO) {
        [self freezeThermometer];
        [self sendRageToWeb];
    } else {
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
    [heat_img setFrame:CGRectMake(140,285,42,-20)];
    [UIView commitAnimations];
}

-(void)bumpThermometer {
    [self bumpThermometerByAmount:PIXEL_INCREASE_PER_RAGE];
}

-(void)increaseMercuryHeight:(int) amount {
    CALayer * heat_layer = [heat_img layer];
    CALayer * heat_presentation = [heat_layer presentationLayer];
    CGRect current_disp = [heat_presentation bounds];

    float new_height = CGRectGetHeight(current_disp);
    new_height = new_height + amount;
    new_height = new_height * -1;
    if (new_height < -220) {
        new_height = -220;
    }

    [heat_img setFrame:CGRectMake(140, 285, 42, new_height)];
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
    locationLabel.text = [location description];
}

-(void)locationError:(NSError *) error{
    locationLabel.text = [error description];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

-(BOOL)textFieldShouldReturn:(UITextField *)thetxt {
    if (thetxt == my_textfield) {
        [my_textfield resignFirstResponder];
    }
    return YES;
}

- (void)dealloc {
    [locationController release];
    [my_accelerometer release];
    [heat_img release];
    [queue release];
    [labelX release];
    [labelY release];
    [labelZ release];
    [my_textfield release];
    [my_textview release];
    [locationLabel release];
    [super dealloc];
}


@end
