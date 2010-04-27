#include "post.h"

// Dummy WriteFunction to disable curl writing to stdout
size_t dummy (void* v1, size_t size, size_t nmemb, void* v2){
return size*nmemb;
}

int post_rage_data(double latitude, double longitude, double rage, int userid)
{
  CURL *curl;
  CURLcode res;

  char postdata[BUFFERSIZE];
//if(DEBUGGING > 0)
  printf("Rage coordinates received. Sending to server: \n lat: %f / long: %f / rage: %f / user: %u \n",
	latitude, longitude, rage, userid);

  snprintf(postdata, BUFFERSIZE, "la=%f&lo=%f&r=%f&u=%u&add=Add!", latitude, longitude, rage, userid);

  
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://rage.calmensvball.com/index.php");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata);
 
    /* if we don't provide POSTFIELDSIZE, libcurl will strlen() by
       itself */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postdata));
curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

if(DEBUGGING > 0){
//Leave on debugging output
}else{
curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dummy);
curl_easy_setopt(curl, CURLOPT_WRITEDATA, dummy);
}
    res = curl_easy_perform(curl);
 
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
  
}
