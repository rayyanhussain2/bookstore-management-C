#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char test[] = "lolwa";
  FILE* pFile = fopen("test.txgt", "w");

  fputs(&test[0], pFile);

  fclose(pFile);
  pFile = NULL;
  return 0;
} 