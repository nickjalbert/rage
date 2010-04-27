#ifndef POST_H
#define POST_H

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "const.h"

int post_rage_data(double latitude, double longitude, double rage, int userid);

#endif
