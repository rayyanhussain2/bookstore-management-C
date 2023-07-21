#include <stdlib.h>

struct book{
    char title [201]; //Requires a dynamic \0
    char ISBN[14]; 
    char author [71]; //Requires a dynamic \0
    char publisher[71]; //Requires a dynamic \0
    char year[5];
    char charsAvailability[6]; //Requires a dynamic \0
    short availability;

};

void setupBook(struct book* pCurrBook, FILE* pFile);

#include "src/book.c"
