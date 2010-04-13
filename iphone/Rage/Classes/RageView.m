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

- (void)viewDidLoad {
    [super viewDidLoad];

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
    [animation_img setBackgroundColor:[UIColor redColor]];
}

- (IBAction)rageOn:(id)sender {
  
  [animation_img.layer 
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


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)viewDidUnload {
    [super viewDidUnload];
    [img_array release];
}


- (void)dealloc {
    [super dealloc];
}


@end
