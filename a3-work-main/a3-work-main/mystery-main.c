/* Complete the C version of the driver program for mystery. This C code does
 * not need to compile. */

#include <stdio.h>

extern long crunch(long, long);

int main(int argc, char *argv[]) {
  if(argc != 3){
    printf("Two arguments required.\n");
    return 1;
  }
  long result = crunch(strtol(argv[1], NULL, 10), strtol(argv[2], NULL, 10));
  if(result < 0){
    printf("hat\n");
  }else if(result == 0){
    printf("tea\n");
  }else{
    printf("beer\n");
  }
  return 0;
}

