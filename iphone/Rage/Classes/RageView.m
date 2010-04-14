//
//  RageView.m
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "RageView.h"

#define NUMPICS 19

@implementation RageView
@synthesize my_img;
@synthesize animation_img;
@synthesize locationLabel;

- (void)viewDidLoad {
    [super viewDidLoad];
  
  next_direction_is_up = YES;
  /*
  mylayer = [CALayer layer];
  UIImage * mylayer_img = [UIImage imageNamed:@"rage10.png"];
  mylayer.contents = (id) mylayer_img.CGImage;
  mylayer.bounds = CGRectMake(0, 0, mylayer_img.size.width, mylayer_img.size.height);
  
  [self.view.layer addSublayer:mylayer];
  locationController = [[MyCLController alloc] init];
  locationController.delegate =self;
  [locationController.locationManager startUpdatingLocation];
  */

    img_array = [[NSMutableArray alloc] initWithCapacity:NUMPICS];
    for (int i = NUMPICS; i >= 0; i--) {
        [img_array addObject:[UIImage imageNamed:[NSString stringWithFormat:@"rage%d.png", i]]];
    }

    UIImageView * bkg = [[UIImageView alloc] initWithFrame:CGRectMake(10, 10, 20, 100)];
    [self.view addSubview:bkg];
  [bkg setBackgroundColor:[UIColor whiteColor]];
    [bkg release];

    animation_img = [[UIImageView alloc] initWithFrame:CGRectMake(10,10,20,100)];
    [self.view addSubview:animation_img];
  [animation_img setBackgroundColor:[UIColor colorWithRed:(221.0f/255.0f) green:(21.0f/255.0f) blue:(21.0f/255.0f) alpha:1.0]];
     
}

- (IBAction)rageOn:(id)sender {
  
  CALayer * lay = [animation_img layer];
  CALayer * mypre = [lay presentationLayer];
  //CGRect visRect =[mylayer visibleRect];  
  
  
  CGRect mybd = [mypre bounds];
  //CGRect mybd = [[[animation_img  layer]  presentationLayer] bounds];
  NSLog(@"pres rect: %@", NSStringFromCGRect(mybd));
  NSLog(@"layout rect: %@", NSStringFromCGRect([lay bounds]));
  [animation_img setFrame:CGRectMake(10, 10, CGRectGetWidth([mypre bounds]), CGRectGetHeight([mypre bounds]))];
  if (next_direction_is_up == YES) {
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:1.5];
    [animation_img setFrame:CGRectMake(10,10,20,20)];
    [UIView commitAnimations];
    next_direction_is_up = NO;
  } else {    
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:1.5];
    [animation_img setFrame:CGRectMake(10,10,20,100)];
    [UIView commitAnimations];
    next_direction_is_up = YES;
  }
  
  return;
  
  if ([animation_img pointInside:CGPointMake(15, 60) withEvent:nil] == NO) {
         [UIView beginAnimations:nil context:NULL];
         [UIView setAnimationDuration:1.5];
         [animation_img setFrame:CGRectMake(10,10,20,100)];
         [UIView commitAnimations];
         return;

  }
  UIImageView * rage_meter = [[UIImageView alloc] initWithFrame: CGRectMake(20,20,280,360)];
  rage_meter.animationImages = img_array;
  rage_meter.animationRepeatCount = 1;
  rage_meter.contentMode = UIViewContentModeBottomLeft;
  [self.view addSubview:rage_meter];
  [rage_meter startAnimating];
  [rage_meter release];
   


  //[animation_img setBackgroundColor:hit_result.backgroundColor];
  //[animation_img drawRect:CGRectMake(10, 10 ,50 , 100)];  
  [UIView beginAnimations:nil context:NULL];
  [UIView setAnimationDuration:1.5];
  [animation_img setFrame:CGRectMake(10,10,20,20)];
  [UIView commitAnimations];

  /*
     [self.my_img setImage:[UIImage imageNamed:@"rage10.png"]];
     UIImageView * other = [[UIImageView alloc] initWithFrame: CGRectMake(10,10,100,100)];
     [other setBackgroundColor:[UIColor redColor]];
     UIImageView * other2 = [[UIImageView alloc] initWithFrame: CGRectMake(10,10,100,100)];
     [other2 setBackgroundColor:[UIColor whiteColor]];
     [self.view addSubview:other];
     [self.view addSubview:other2];
     [other release];
     */
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
    [img_array release];
}


- (void)dealloc {
  [locationController release];
    [super dealloc];
}


@end
