#include <stdio.h>
#include <stdlib.h>

int main(){
  char buffer[10];
  fgets(&buffer[0], 10, stdin);
  printf("%i %i\n", buffer[8], buffer[9]);
  char *ptr;
  printf("%li\n", strtol("fjsdklfjdl", &ptr, 5));
} 