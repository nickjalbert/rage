#ifndef LOCATION_H
#define LOCATION_H

#include <location/location-gps-device.h>
#include <location/location-gpsd-control.h>
#include "const.h"
#include "post.h"
#include "shake.h"

static void on_error(LocationGPSDControl *control, LocationGPSDControlError error, gpointer data);

static void on_changed(LocationGPSDevice *device, gpointer data);

static void on_changed(LocationGPSDevice *device, gpointer data);

static void on_changed(LocationGPSDevice *device, gpointer data);

#endif

