#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

struct book{
    char title [201]; //Requires a dynamic \0
    char ISBN[14]; 
    char author [71]; //Requires a dynamic \0
    char publisher[71]; //Requires a dynamic \0
    char year[5];
    char charsAvailability[6]; //Requires a dynamic \0
    short availability;

};

void setupBook(struct book* pCurrBook, FILE* pFile)
{
    short phase = 1, index = 0;
    pCurrBook -> ISBN[13] = '\0';
    pCurrBook -> year[4] = '\0';
    while(true)
    {
        char currChar = fgetc(pFile); //it returns the character and moves the poitner forward, probably something in the struct where one holds the pointer another holds the actual address
        if(currChar == EOF)
        {
            break;
        }
        else if(currChar == '\n')
        {
            continue;
        }
        else if (currChar == ';')
        {
            if(phase == 1)
                pCurrBook -> title[index] = '\0';
            else if (phase == 3)
                pCurrBook -> author[index] = '\0';
            else if (phase == 4)
                pCurrBook -> publisher[index] = '\0';
            else if (phase == 6)
            {
                pCurrBook -> charsAvailability[index] = '\0';
                pCurrBook -> availability = atoi(pCurrBook -> charsAvailability);

            }
            phase += 1;
            index = 0;
            continue;
        }
        
        //copying the data
        if (phase == 1)
        {
            pCurrBook -> title[index] = currChar;
            index += 1;
        }
        else if (phase == 2)
        {
            pCurrBook -> ISBN[index] = currChar;
            index += 1; 
        }
        else if(phase == 3)
        {
            pCurrBook -> author[index] = currChar;
            index += 1;
        }
        else if(phase == 4)
        {
            pCurrBook -> publisher[index] = currChar;
            index += 1;            
        }
        else if(phase == 5)
        {
            pCurrBook -> year[index] = currChar;
            index += 1;
        }
        else if(phase == 6)
        {
            pCurrBook -> charsAvailability[index] = currChar;
            index += 1;
        }
    }
}

int main()
{
    FILE* pFile = fopen("data.txt", "r");
    struct book* pCurrBook = (struct book*) malloc (sizeof(struct book));
    setupBook(pCurrBook, pFile);
    fclose(pFile);
    pFile = NULL;

    puts(pCurrBook -> title);
    puts(pCurrBook -> ISBN);
    puts(pCurrBook -> author);
    puts(pCurrBook -> publisher);
    puts(pCurrBook -> year);
    printf("%i\n", pCurrBook -> availability);
}