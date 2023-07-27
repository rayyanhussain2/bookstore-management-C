#include <stdio.h>
#include <windows.h>

void printTitleSticky(){
  fputs("=========================================\n", stdout);
  fputs("        Library Management System\n", stdout);
  fputs("=========================================\n\n", stdout);
}

void printMenu(){
  fputs("Please select an option:\n", stdout);
  fputs("1. Add a book\n", stdout);
  fputs("2. Search a book\n", stdout);
  fputs("3. List books\n", stdout);
  fputs("4. Exit\n\n", stdout);
  fputs("Enter the number of your choice: ", stdout);
}

void printError(){
  fputs("\nInvalid input, please try again\n", stdout);
  Sleep(300);
  system("clear");
}

void clearBuffer(){
  while(fgetc(stdin) != '\n'){
    continue;
  }
}


int checkEE(){
  char check = fgetc(stdin);
  if(check == '\n'){//Buffer's already cleared
    return 0;
  }else if(check == 27){
    clearBuffer();
    return -1;
  }else{
    ungetc(check, stdin);
    return 1;
  }

}

int checkEE0(){
  char check = fgetc(stdin);
  if(check == '\n'){//Buffer's already cleared
    return 0;
  }else if(check == 27){
    clearBuffer();
    return -1;
  }else if(check == '0'){
    return 2;
  }else{
    ungetc(check, stdin);
    return 1;
  }

}

int fGetStdin(char* string, int strlen){
  //assumption is that the first character is not escape (clear buffer handled by checkEE)
  //another assumption is that the first character is not \n
  char charPointer;
  int i = 0;
  while(i < strlen - 1){
    charPointer = fgetc(stdin);
    if(charPointer == '\n')
      break;
    *(string + i) = charPointer;
    i += 1;
  }

  if(strlen > 1)
    *(string+i) = '\0';

  return charPointer;
}

void printBookInfo(struct bookNode* pBook){
  fputs("Title: ", stdout);
  fputs(&(pBook -> title[0]), stdout);
  fputs("\n", stdout);
  
  fputs("ISBN: ", stdout);
  fputs(&(pBook -> ISBN[0]), stdout);
  fputs("\n", stdout);
  
  fputs("Author: ", stdout);
  fputs(&(pBook -> author[0]), stdout);
  fputs("\n", stdout);


  fputs("Publisher: ", stdout);
  fputs(&(pBook -> publisher[0]), stdout);
  fputs("\n", stdout);

  fputs("Year: ", stdout);
  fputs(&(pBook -> year[0]), stdout);
  fputs("\n", stdout);

  fputs("Available copies: ", stdout);
  printf("%d\n", pBook -> copies);

  fputs("Genre: ", stdout);
  printf("%d\n\n", pBook -> genre);
}