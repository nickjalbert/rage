/*
 * MyCLController.h
 *
 * Author - Nick Jalbert (jalbert@cs.berkeley.edu)
 *
 * Based on the Mobil Orchard Hello There: A CoreLocation Tutorial
 *
 */


@protocol MyCLControllerDelegate
@required
-(void) locationUpdate: (CLLocation *) location;
-(void) locationError: (NSError *) error;
@end


@interface MyCLController : NSObject <CLLocationManagerDelegate> {
    CLLocationManager *locationManager;
    id delegate;
}

@property (nonatomic, retain) CLLocationManager * locationManager;
@property (nonatomic, assign) id delegate;

-(void)locationManager:(CLLocationManager *)manager
    didUpdateToLocation:(CLLocation *) newLocation
    fromLocation: (CLLocation *) oldLocation;

-(void)locationManager:(CLLocationManager *) manager
    didFailWithError: (NSError *) error;

@end
