#ifndef SHAKE_H
#define SHAKE_H

#include <stdio.h>
#include <stdlib.h>

static int currentX=0;
static int currentY=0;
static int currentZ=0;

static const char *accel_filename = "/sys/class/i2c-adapter/i2c-3/3-001d/coord";

int is_shaking(int threshold, int *amount);

#endif
