//
//  MobileKVMessage.h
//  Rage
//
//  Created by Nick Jalbert on 5/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ASIFormDataRequest.h"

@interface MobileKVMessage : NSObject {
    NSMutableDictionary * key_dict;
    NSString * url;
    NSOperationQueue * queue;
}

+(MobileKVMessage*) getNewMobileKVMessage: (NSString*) target;
-(id) initWithTarget: (NSString*) target;
-(void) addKeyValue: (NSString*) k andValue: (NSString*) v;
-(void) send;
-(NSString*) getIncidentXML;


@property (retain) NSMutableDictionary* key_dict;
@property (retain) NSString* url;
@property (nonatomic, retain) NSOperationQueue* queue;

@end
