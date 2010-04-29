#include "shake.h"

int main(void){
  int magnitude;
  while(1){
    if(is_shaking(2000, &magnitude)){
      printf("shaking! at magnitude of: %u \n", magnitude);
    }
  }
  return 0;
}
