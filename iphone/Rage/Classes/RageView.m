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

- (void)viewDidLoad {
    [super viewDidLoad];
    img_array = [[NSMutableArray alloc] initWithCapacity:NUMPICS];
    for (int i = NUMPICS; i >= 0; i--) {
        [img_array addObject:[UIImage imageNamed:[NSString stringWithFormat:@"rage%d.png", i]]];
    }
}

- (IBAction)rageOn:(id)sender {
    UIImageView * rage_meter = [[UIImageView alloc] initWithFrame: CGRectMake(20,20,280,360)];
    rage_meter.animationImages = img_array;
    rage_meter.animationRepeatCount = 1;
    rage_meter.contentMode = UIViewContentModeBottomLeft;
    [self.view addSubview:rage_meter];
    [rage_meter startAnimating];
    [rage_meter release];
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
