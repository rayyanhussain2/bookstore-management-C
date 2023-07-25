#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int getMax(int a, int b){
    return (a > b)? a : b;
}

int getHeight(struct bookNode* pCurrBook){ 
    if(pCurrBook == NULL){
        return -1;
    }
    return pCurrBook -> height;
}

int getBalanceFactor(struct bookNode* pCurrBook){
    return getHeight(pCurrBook -> pRight) - getHeight(pCurrBook -> pLeft);
}

struct bookNode* rrRotation(struct bookNode* pCurrBook){
    //rotation
    struct bookNode* newRoot = pCurrBook -> pRight;
    pCurrBook -> pRight = newRoot -> pLeft;
    newRoot -> pLeft = pCurrBook;
 
    //update height
    pCurrBook -> height = 1 + getMax(getHeight(pCurrBook -> pLeft), getHeight(pCurrBook -> pRight));
    newRoot -> height = 1 + getMax(getHeight(newRoot -> pLeft), getHeight(newRoot -> pRight));
    
    //return
    return newRoot;
}

struct bookNode* llRotation(struct bookNode* pCurrBook){
    //rotation
    struct bookNode* newRoot = pCurrBook -> pLeft;
    pCurrBook -> pLeft = newRoot -> pRight;

    newRoot -> pRight = pCurrBook;
 
    //update height
    pCurrBook -> height = 1 + getMax(getHeight(pCurrBook -> pLeft), getHeight(pCurrBook -> pRight));
    newRoot -> height = 1 + getMax(getHeight(newRoot -> pLeft), getHeight(newRoot -> pRight));
    
    //return
    return newRoot;
}

struct bookNode* rlRotation(struct bookNode* pCurrBook){
    //rotation
    pCurrBook -> pRight = llRotation(pCurrBook -> pRight);
    return rrRotation(pCurrBook);
}

struct bookNode* lrRotation(struct bookNode* pCurrBook){
    pCurrBook -> pLeft = rrRotation(pCurrBook -> pLeft);
    return llRotation(pCurrBook);
}

struct bookNode* insertAVL(struct bookNode* pCurrBook, struct bookNode* pNewBook){
    if(pCurrBook == NULL){
        return pNewBook;
    }
    else if (strcmp(pCurrBook -> title, pNewBook -> title) > 0){
        pCurrBook -> pLeft = insertAVL(pCurrBook -> pLeft, pNewBook);
    }else if (strcmp(pCurrBook -> title, pNewBook -> title) < 0){
        pCurrBook -> pRight = insertAVL(pCurrBook -> pRight, pNewBook); //handles the case where the title is the same
    }else{
        return pCurrBook;
    }

    //backtracking
    //recalculate the heights
    pCurrBook -> height =  1 + getMax(getHeight(pCurrBook -> pLeft), getHeight(pCurrBook -> pRight));
    short int balanceFactor = getBalanceFactor(pCurrBook);
    //Checking the imbalance with respect to the inserted node
    if(balanceFactor > 1){
        //RR
        if(strcmp(pNewBook -> title, pCurrBook -> pRight -> title) > 0){
            pCurrBook = rrRotation(pCurrBook);
            }else{
            //RL
            pCurrBook = rlRotation(pCurrBook);
        }
    }else if(balanceFactor < -1){
        //LL
        if(strcmp(pNewBook -> title, pCurrBook -> pLeft -> title) < 0){
            pCurrBook = llRotation(pCurrBook);
        }else{
            //LR
            pCurrBook = lrRotation(pCurrBook);
        }
    }
    return pCurrBook;
}

struct bookNode* minTree(struct bookNode* pCurrBook){
    while(pCurrBook -> pLeft != NULL){
        pCurrBook = pCurrBook -> pLeft;
    }
    return pCurrBook;
}

struct bookNode* returnSuccessorTwoChildren(struct bookNode* pCurrBook){
    return minTree(pCurrBook -> pRight);
}

/*
struct bookNode* deleteAVL(struct bookNode* pCurrBook, int val){
    if(pCurrBook == NULL)
    {
        puts("Node not found");
        return NULL;
    }

    if(pCurrBook -> value > val){
        pCurrBook -> pLeft = deleteAVL(pCurrBook -> pLeft, val);
    }else if(pCurrBook -> value < val){
        pCurrBook -> pRight = deleteAVL(pCurrBook -> pRight, val);
    }else{
        //we've found the node

        //the node has no children
        if(pCurrBook -> pLeft == NULL && pCurrBook -> pRight == NULL){
            free(pCurrBook);
            return NULL;
        }

        //the node has one child
        else if(pCurrBook -> pLeft != NULL && pCurrBook -> pRight == NULL){
            struct bookNode* returnNode = pCurrBook -> pLeft;
            free(pCurrBook);
            return returnNode;
        }else if(pCurrBook -> pLeft == NULL && pCurrBook -> pRight != NULL){
            struct bookNode* returnNode = pCurrBook -> pRight;
            free(pCurrBook);
            return returnNode;
        }

        //the node has two children
        else{
            //Find successor
            struct bookNode* successorNode = returnSuccessorTwoChildren(pCurrBook);

            //Copy Data
            pCurrBook -> value = successorNode -> value;

            //Free the node
            pCurrBook -> pRight = deleteAVL(pCurrBook -> pRight, successorNode -> value);
        }
    }


    //rebalancing
    pCurrBook -> height =  1 + getMax(getHeight(pCurrBook -> pLeft), getHeight(pCurrBook -> pRight));
    short int balanceFactor = getBalanceFactor(pCurrBook);

    //Checking in general
    if(balanceFactor > 1){
        //RR
        if(pCurrBook -> pRight -> pRight != NULL){
            pCurrBook = rrRotation(pCurrBook);
            }else{
            //RL
            pCurrBook = rlRotation(pCurrBook);
        }
    }else if(balanceFactor < -1){
        //LL
        if(pCurrBook -> pLeft -> pLeft != NULL){
            pCurrBook = llRotation(pCurrBook);
        }else{
            //LR
            pCurrBook = lrRotation(pCurrBook);
        }
    }
    return pCurrBook;
}
*/

void preDisplay(struct bookNode* pRoot){
    if (pRoot == NULL)
        return;

    printf("%s\n", pRoot -> title);
    preDisplay(pRoot -> pLeft);
    preDisplay(pRoot -> pRight);
}
