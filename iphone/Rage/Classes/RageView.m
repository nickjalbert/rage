//
//  RageView.m
//  Rage
//
//  Created by Nick Jalbert on 4/11/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "RageView.h"


@implementation RageView

@synthesize label;

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

- (IBAction)rageOn:(id)sender {
  
  NSString * label_text = [label text];
  
  if ([label_text isEqualToString:@""]) {
    NSString * ragelabel = [[NSString alloc] initWithFormat:@"RAGE"];
    
    
    [label setText:ragelabel];
    [ragelabel release];
  } else {
    
    NSString * emptylabel = [[NSString alloc] initWithFormat:@""];
    [label setText:emptylabel];
    [emptylabel release];
  }
  
  NSMutableArray * imgArray = [[NSMutableArray alloc] initWithCapacity:20];
  
  for (int i = 19; i >= 0; i--) {
    [imgArray addObject:[UIImage imageNamed:[NSString stringWithFormat:@"rage%d.png", i]]];
  }
  
  /*
  
  NSArray * imgArray = [[NSArray alloc] initWithObjects:
                        [UIImage imageNamed:@"rage0.png"],
                        [UIImage imageNamed:@"rage1.png"],
                        [UIImage imageNamed:@"rage2.png"],
                        [UIImage imageNamed:@"rage3.png"],
                        [UIImage imageNamed:@"rage4.png"],
                        [UIImage imageNamed:@"rage5.png"],
                        [UIImage imageNamed:@"rage6.png"],
                        [UIImage imageNamed:@"rage7.png"],
                        [UIImage imageNamed:@"rage8.png"],
                        [UIImage imageNamed:@"rage9.png"],
                        [UIImage imageNamed:@"rage10.png"],
                        [UIImage imageNamed:@"rage11.png"],
                        [UIImage imageNamed:@"rage12.png"],
                        [UIImage imageNamed:@"rage13.png"],
                        [UIImage imageNamed:@"rage14.png"],
                        [UIImage imageNamed:@"rage15.png"],
                        [UIImage imageNamed:@"rage16.png"],
                        [UIImage imageNamed:@"rage17.png"],
                        [UIImage imageNamed:@"rage18.png"],
                        [UIImage imageNamed:@"rage19.png"],
                        nil];
  */
  UIImageView * rage_meter = [[UIImageView alloc] initWithFrame: CGRectMake(20,20,280,360)];
  rage_meter.animationImages = imgArray;
  //rage_meter.animationDuration =  1;
  rage_meter.animationRepeatCount = 1;
  rage_meter.contentMode = UIViewContentModeBottomLeft;
  [self.view addSubview:rage_meter];
  [rage_meter startAnimating];
  
  
  
  
  
  
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
