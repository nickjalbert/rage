/*
 * RageView.m
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 */

#import "RageView.h"

#define PIXEL_INCREASE_PER_RAGE 15
#define RAGE_DECAY_SPEED 1.5

@implementation RageView

@synthesize heat_img;
@synthesize locationLabel;

- (void)viewDidLoad {
    [super viewDidLoad];

    /* Location Tracking Interface */
    locationController = [[MyCLController alloc] init];
    locationController.delegate = self;
    [locationController.locationManager startUpdatingLocation];

    /*Thermometer Interface */
    UIImageView * bkg = [[UIImageView alloc] initWithFrame:CGRectMake(140, 65, 42, 220)];
    [bkg setBackgroundColor:[UIColor colorWithRed:(1.0) green:(253.0f/255.0f) blue:(253.0f/255.0f) alpha:1.0]];
    [self.view addSubview:bkg];

    heat_img = [[UIImageView alloc] initWithFrame:CGRectMake(140,285,42,-20)];
    [heat_img setBackgroundColor:[UIColor colorWithRed:(221.0f/255.0f) green:(21.0f/255.0f) blue:(21.0f/255.0f) alpha:1.0]];
    [self.view addSubview:heat_img];
    
    [self.view sendSubviewToBack:heat_img];
    [self.view sendSubviewToBack:bkg];
    
    [bkg release];
}

- (IBAction)rageOn:(id)sender {

    CALayer * heat_layer = [heat_img layer];
    CALayer * heat_presentation = [heat_layer presentationLayer];
    CGRect current_disp = [heat_presentation bounds];

    float new_height = CGRectGetHeight(current_disp);
    new_height = new_height + PIXEL_INCREASE_PER_RAGE;
    new_height = new_height * -1;
    if (new_height < -220) {
        new_height = -220;
    }

    [heat_img setFrame:CGRectMake(140, 285, 42, new_height)];
    
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration: RAGE_DECAY_SPEED];
    [heat_img setFrame:CGRectMake(140,285,42,-20)];
    [UIView commitAnimations];
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


- (void)dealloc {
    [locationController release];
    [super dealloc];
}


@end
