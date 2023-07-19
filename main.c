#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "customAVL.c"

int main()
{
    FILE* pFile = fopen("data.txt", "r");
    struct nodeAVL* avlRoot = NULL;

    //Loop
    char currChar = fgetc(pFile);
    while(currChar != EOF){
        ungetc(currChar, pFile);
        struct book* pCurrBook = (struct book*) malloc (sizeof(struct book));
        setupBook(pCurrBook, pFile);
        avlRoot = insertAVL(avlRoot, pCurrBook);
        currChar = fgetc(pFile);
    }
        
    fclose(pFile);
    pFile = NULL;


    preDisplay(avlRoot);
    
}