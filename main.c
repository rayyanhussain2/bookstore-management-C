#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "dependencies/book.h"
#define genreCount 30

//in 64 bit systems, ech memory address is 64 bits or 8 bytes
//is this done on hardware or software part
//can be abstract or hardware
// the bus is 8 bytes for addressing

/*
1. Art
2. Biography
3. Business
4. Children's
5. Christian
6. Classics
7. Comics
8. Cookbooks
9. Ebooks
10. Fantasy
11. Fiction
12. Graphic Novels
13. Historical Fiction
14. History
15. Horror
16. Memoir
17. Music
18. Mystery
19. Nonfiction
20. Poetry
21. Psychology
22. Romance
23. Science
24. Science Fiction
25. Self Help
26. Sports
27. Thriller
28. Travel
29. Young Adult
*/


int main()
{
    //setting up initial variables, reading from saved file
    struct bookNode* genreHeads[genreCount];
    for(int i = 0; i < genreCount; i++){
        genreHeads[i] = NULL;
    }

    FILE* pFile = fopen("data.txt", "r");

    //Decrypt

    //Input
    setupBookFile(&genreHeads[0], pFile); 
    fclose(pFile);

    //Main menu
    while(true){
        system("clear");
        printTitleSticky();
        printMenu();
        
        int checkRes = checkEE();
        if (checkRes != 1)
            goto invalid;

        char selection = fgetc(stdin);
        clearBuffer();

        if(selection == '1'){
            //Insert 
            setupBookInput(&genreHeads[0]);
        }
        else if(selection == '2'){
            //Search 
            searchBooks(&genreHeads[0]);
        }
        else if(selection == '3'){
            //List 
            listBooks(&genreHeads[0]); 
        }
        else if(selection == '4'){
            //Encrypt
  
            pFile = fopen("data.txt", "w");
            //Write To file
            writeBooksFile(&genreHeads[0], pFile);
            //close file 
            fclose(pFile);
            pFile = NULL;

            //free nodes 
            for(int i = 0; i < genreCount; i++){
                genreHeads[i] = freeNodes(genreHeads[i]);
            }

            return 0;
        }else{
        invalid:
            printError();
        }
    }
}