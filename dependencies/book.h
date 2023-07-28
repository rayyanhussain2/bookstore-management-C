struct bookNode{
    char title [201]; //Requires a dynamic \0
    char ISBN[14]; 
    char author [71]; //Requires a dynamic \0
    char publisher[71]; //Requires a dynamic \0
    char year[5];
    short copies;
    short genre;
    unsigned int height;    
    struct bookNode* pLeft;
    struct bookNode* pRight;
};

#include "front.h"

#include "customAVL.h"

void setupBookFile(struct bookNode** genreHeads, FILE* pFile);

void setupBookInput(struct bookNode** genreHeads);

void searchBooks(struct bookNode** genreHeads);

void listBooks(struct bookNode** genreHeads);

void writeBookFile(struct bookNode* pBook, FILE* pFile);

void preDisplayWrite(struct bookNode* pRoot, FILE* pFile);

void writeBooksFile(struct bookNode** genreHeads, FILE* pFile);

#include "src/book.c"