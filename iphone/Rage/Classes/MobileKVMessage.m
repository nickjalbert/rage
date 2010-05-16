//
//  MobileKVMessage.m
//  Rage
//
//  Created by Nick Jalbert on 5/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "MobileKVMessage.h"


@implementation MobileKVMessage

@synthesize key_dict;
@synthesize url;
@synthesize queue;

+(MobileKVMessage*) getNewMobileKVMessage: (NSString*) target {
    MobileKVMessage* msg = [[MobileKVMessage alloc] initWithTarget:target];
    return msg;
}

- (id) init {
    self = [super init];
    if (self) {
        key_dict = [[NSMutableDictionary alloc] initWithCapacity:5];
    }
    return self;
}

-(id) initWithTarget: (NSString*) target {
    self = [super init];
    if (self) {
        key_dict = [[NSMutableDictionary alloc] initWithCapacity:5];
        url = target;
    }
    return self;
}

-(NSString*) getIncidentXML {
    NSString* incident = [NSString stringWithFormat:@"<incident>"];
    for (NSString* k in key_dict) {
        incident = [incident stringByAppendingFormat:@"<%@>", k];
        NSString* tmp_val = [key_dict objectForKey:k];
        incident = [incident stringByAppendingFormat:@"%@", tmp_val];
        incident = [incident stringByAppendingFormat:@"</%@>", k];
    }
    incident = [incident stringByAppendingString:@"</incident>"];
    return incident;
}

-(void) addKeyValue: (NSString*) k andValue: (NSString*) v {
    if (key_dict != nil) {
        [key_dict setObject:v forKey:k];
    }
}

-(void) send {
    if (url != nil) {
        NSString* incident = [self getIncidentXML];
        
        if (![self queue]) {
            [self setQueue:[[[NSOperationQueue alloc] init] autorelease]];
        }
        
        NSURL * target_url = [NSURL URLWithString:url];
        ASIFormDataRequest* request = [ASIFormDataRequest requestWithURL:target_url];
        [request setPostValue:incident forKey:@"incident"];
        //[request startSynchronous];
        //[request setDelegate:self];
        [[self queue] addOperation:request];
    }
}

- (void) dealloc {
    [key_dict release];
    [queue release];
    [url release];
    [super dealloc];
}
@end
