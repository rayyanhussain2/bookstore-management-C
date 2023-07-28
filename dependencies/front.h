#include <windows.h>

void printTitleSticky();

void printMenu();

void printError();

void clearBuffer();

int checkEE();

int fGetStdin(char* string, int strlen);

void printBookInfo(struct bookNode* pBook);

#include "src/front.c"