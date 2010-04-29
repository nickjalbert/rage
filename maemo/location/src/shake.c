#include "shake.h"

//Returns 1 if shaking is detected, 0 if not. parameter threshold specifies magnitude (in micro Gs) to count as shaking. *amount is set to the magnitude of shaking occuring.
int is_shaking(int threshold, int *amount)
{
  FILE *fd;
  int rs;
  int newX;
  int newY;
  int newZ;
  int deltaX;
  int deltaY;
  int deltaZ;

  //Perform sensor read
  fd = fopen(accel_filename, "r");
  if(fd==NULL){ printf("liqaccel, cannot open for reading"); return -1;}	
  rs=fscanf((FILE*) fd,"%i %i %i",&newX,&newY,&newZ);	
  fclose(fd);	
  if(rs != 3){ printf("liqaccel, cannot read information"); return -2;}

  //Detect shaking
  deltaX = abs(newX - currentX);
  deltaY = abs(newY - currentY);
  deltaZ = abs(newZ - currentZ);

  //Update current values
  currentX = newX;
  currentY = newY;
  currentZ = newZ;

  //Set magnitude
  *amount = deltaX + deltaY + deltaZ;

  if(*amount > threshold){
    return 1;
  }else{
    return 0;
  }
}
