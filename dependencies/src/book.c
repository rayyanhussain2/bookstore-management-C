#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct bookNode{
    char title [202]; //Requires a dynamic \0
    char ISBN[14]; 
    char author [71]; //Requires a dynamic \0
    char publisher[71]; //Requires a dynamic \0
    char year[5];
    short availability;
    short genre;
    unsigned int height;    
    struct bookNode* pLeft;
    struct bookNode* pRight;
};

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
                        pNewBook -> availability = atoi(availabilityBuffer);

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

    fputs("Please enter title of the book (200 char max)", stdout);
    fgets(&(pNewBook -> title[0]), 200, stdin);
    fputs(&(pNewBook -> title[0]), stdout);


}