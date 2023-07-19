#include <stdio.h>
#include <stdbool.h>

void setupBook(struct book* pCurrBook, FILE* pFile)
{
    short phase = 1, index = 0;
    pCurrBook -> ISBN[13] = '\0';
    pCurrBook -> year[4] = '\0';
    while(true)
    {
        char currChar = fgetc(pFile); //it returns the character and moves the poitner forward, probably something in the struct where one holds the pointer another holds the actual address
        if(currChar == '\n')
        {
            break;
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