#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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

#include "gtk.c"


#include "customAVL.c"

void setupBookFile(struct bookNode** genreHeads, FILE* pFile)
{
    char currChar = fgetc(pFile);
    //Loop that goes across lines
    while(currChar != EOF){
        ungetc(currChar, pFile);
 
        //Setting up new book for the current line in the file
        struct bookNode* pNewBook = (struct bookNode*) malloc (sizeof(struct bookNode));
        short phase = 1, index = 0;
        char availabilityBuffer[6]; //Requires a dynamic \0
        char genreBuffer[3];
        pNewBook -> ISBN[13] = '\0';
        pNewBook -> year[4] = '\0';
        genreBuffer[2] = '\0';

        //Loop that goes within lines
        while(true)
        {
            char currChar = fgetc(pFile); //it returns the character and moves the poitner forward, probably something in the struct where one holds the pointer another holds the actual address
            if(currChar == '\n'){
                break;
            }
            else if (currChar == ';')
            {
                switch(phase){
                    case 1:
                        pNewBook -> title[index] = '\0';
                        break;

                    case 3:
                        pNewBook -> author[index] = '\0';
                        break;

                    case 4:
                        pNewBook -> publisher[index] = '\0';
                        break;
                    
                    case 6:
                        pNewBook -> genre = atoi(genreBuffer);
                        break;
                    
                    case 7:
                        availabilityBuffer[index] = '\0';
                        pNewBook -> copies = atoi(availabilityBuffer);

                }
                phase +=  1;
                index = 0;
                continue;
            }
            
            //copying the data
            switch(phase){
                case 1 :
                    pNewBook -> title[index] = currChar;
                    index += 1;
                    break;

                case 2:
                    pNewBook -> ISBN[index] = currChar;
                    index += 1; 
                    break;

                case 3:
                    pNewBook -> author[index] = currChar;
                    index += 1;
                    break;

                case 4:
                    pNewBook -> publisher[index] = currChar;
                    index += 1;
                    break;

                case 5:
                    pNewBook -> year[index] = currChar;
                    index += 1;
                    break;

                case 6:
                    genreBuffer[index] = currChar;
                    index += 1;
                    break;

                case 7:
                    availabilityBuffer[index] = currChar;
                    index += 1;
            }
        }

        //pass it to the appropriate AVL Tree
        *(genreHeads + (pNewBook -> genre)) = insertAVL(*(genreHeads + (pNewBook -> genre)), pNewBook);
        currChar = fgetc(pFile);
    }
}

void setupBookInput(struct bookNode** genreHeads){
    struct bookNode* pNewBook = (struct bookNode *) malloc (sizeof(struct bookNode));    
    _Bool confirmation = 0;
init:
    system("clear");
    printTitleSticky();
    fputs("Add a book\n\n", stdout);

    if(confirmation){
        printBookInfo(pNewBook);
        fputs("\nDo you want to add this book to the library? [Y/n] ", stdout);
        
        char y = fgetc(stdin);
        if(y == 'y' || y == 'Y' || y == '\n'){
            *(genreHeads + (pNewBook -> genre)) = insertAVL(*(genreHeads + (pNewBook -> genre)), pNewBook);
        }
        else{
            free(pNewBook);
            pNewBook = NULL;
            confirmation = 0;
            clearBuffer();
            goto init;
        }
    }else{
        char charCurrPointer;

        fputs("Title: ", stdout); //clears buffer
    title:
        int checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto title;
        }
        else{
            charCurrPointer = fGetStdin(&(pNewBook -> title[0]), 201);//last character is always \0, \n will be put if extra space is there
            if(charCurrPointer != '\n'){
                clearBuffer();
            }
        }

    isbn1:
        fputs("ISBN: ", stdout);
    isbn:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto isbn;
        }
        else{
            char tempBuffer[14];
            charCurrPointer = fGetStdin(&tempBuffer[0], 14);//last character is always \0, \n will be put if extra space is there
            if(atol(&tempBuffer[0]) != 0 && strlen(&tempBuffer[0]) == 13){
                strcpy(&(pNewBook -> ISBN[0]), &tempBuffer[0]);
                if(charCurrPointer != '\n')
                    clearBuffer();
            }else{
                fputs("Invalid input, try again\n\n", stdout);
                if(charCurrPointer != '\n')
                    clearBuffer();
                goto isbn1;
            }
        }

        fputs("Author: ", stdout);
    author:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto author;
        }
        else{
            charCurrPointer = fGetStdin(&(pNewBook -> author[0]), 71);//last character is always \0, \n will be put if extra space is there
            if(charCurrPointer != '\n'){
                clearBuffer();
            }
        }

        fputs("Publisher: ", stdout);
    publisher:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto publisher;
        }
        else{
            charCurrPointer = fGetStdin(&(pNewBook -> publisher[0]), 71);//last character is always \0, \n will be put if extra space is there
            if(charCurrPointer != '\n'){
                clearBuffer();
            }
        }

    year:
        fputs("Year: ", stdout);
    year1:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto year1;
        }
        else{
            char tempBuffer[5];
            charCurrPointer = fGetStdin(&tempBuffer[0], 5);//last character is always \0, \n will be put if extra space is there
            if(atoi(tempBuffer) != 0){
                strcpy(&(pNewBook -> year[0]), &tempBuffer[0]);
                if(charCurrPointer != '\n')
                    clearBuffer();
            }else{
                fputs("Invalid input, try again\n\n", stdout);
                if(charCurrPointer != '\n')
                    clearBuffer();
                goto year;
            }
        }

    copies1:
        fputs("Copies: ", stdout);
    copies:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto copies;
        }
        else{
            char tempBuffer[5];
            charCurrPointer = fGetStdin(&tempBuffer[0], 5);//last character is always \0, \n will be put if extra space is there
            int copiesInt = atoi(&tempBuffer[0]); 
            if(copiesInt != 0){
                pNewBook -> copies = copiesInt;
                if(charCurrPointer != '\n')
                    clearBuffer();
            }else{
                fputs("Invalid input, try again\n\n", stdout);
                if(charCurrPointer != '\n')
                    clearBuffer();
                goto copies1;
            }
        }

    genre1:
        fputs("Genre: ", stdout);
    genre:
        checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto genre;
        }
        else{
            char tempBuffer[3];
            charCurrPointer = fGetStdin(&tempBuffer[0], 3);//last character is always \0, \n will be put if extra space is there
            int genreInt = atoi(&tempBuffer[0]); 
            if(genreInt != 0 && genreInt < 30){
                if(charCurrPointer != '\n')
                    clearBuffer();
                pNewBook -> genre = genreInt;
            }else{
                fputs("Invalid input, try again\n\n", stdout);
                if(charCurrPointer != '\n')
                    clearBuffer();
                goto genre1;
            }
        }

    confirmation = 1;
    goto init;
    }
}

void searchBooks(struct bookNode** genreHeads){
struct bookNode* bookFound = NULL;
char charCurrPointer;
char copiesChar[5];
short copiesNew;
int genreInt;
char titleSearch[201];

init:
    system("clear");
    printTitleSticky();
    fputs("Search a book\n\n", stdout);

    if(bookFound != NULL){
        fputs("Book found!\n\n", stdout);
        printBookInfo(bookFound);

select:     
        fputs("Enter the new number of copies for the book: ", stdout);
        int checkRes = checkEE();
        if (checkRes == -1){
            return;
        }else if(checkRes == 0){
            goto select;
        }
        else{
            charCurrPointer = fGetStdin(&copiesChar[0], 5);//last character is always \0, \n will be put if extra space is there
            if (charCurrPointer != '\n'){
                clearBuffer();
            }
            
            if(atoi(&copiesChar[0]) == 0){
               copiesNew = 0;
            }
            else{
                copiesNew = atoi(&copiesChar[0]);
            }
        }

        if(copiesNew == 0){
            *(genreHeads + genreInt) = deleteAVL(*(genreHeads + genreInt), &titleSearch[0]);
        }else{
            bookFound -> copies = copiesNew;
        }
        return;
    }
    else{
            fputs("Enter title of the book: ", stdout); //clears buffer
        title:
            int checkRes = checkEE();
            if (checkRes == -1){
                return;
            }else if(checkRes == 0){
                goto title;
            }
            else{
                charCurrPointer = fGetStdin(&titleSearch[0], 201);//last character is always \0, \n will be put if extra space is there
                if(charCurrPointer != '\n'){
                    clearBuffer();
                }
                //printf("%d %d %d\n", titleSearch[11], titleSearch[12], titleSearch[10]);
            }

        genre1:
            fputs("Enter genre number: ", stdout);
        genre:
            checkRes = checkEE();
            if (checkRes == -1){
                return;
            }else if(checkRes == 0){
                goto genre;
            }
            else{
                char tempBuffer[3];
                charCurrPointer = fGetStdin(&tempBuffer[0], 3);//last character is always \0, \n will be put if extra space is there
                genreInt = atoi(&tempBuffer[0]); 
                if(genreInt != 0 && genreInt <= 30 && genreInt >= 0){
                    if(charCurrPointer != '\n')
                        clearBuffer();
                }else{
                    fputs("Invalid input, try again\n\n", stdout);
                    if(charCurrPointer != '\n')
                        clearBuffer();
                    goto genre1;
                }
            }

        if(genreInt == 30){
            for(int i = 0; i < 30; i++)
            {
                continue;
            }
        }else{
            *(genreHeads + genreInt) = searchNode(*(genreHeads + genreInt), &titleSearch[0], &bookFound);
                                            //Give me the address to the specific genre head
            if(bookFound == NULL){
                fputs("Book nhi mila\n", stdout);
            }
            goto init;
        }
    }
}