#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header/book.h"

struct nodeAVL{
    struct book* pBook;
    unsigned int height;    
    struct nodeAVL* pLeft;
    struct nodeAVL* pRight;
};

int getMax(int a, int b){
    return (a > b)? a : b;
}

int getHeight(struct nodeAVL* pCurrNode){ 
    if(pCurrNode == NULL){
        return -1;
    }
    return pCurrNode -> height;
}

int getBalanceFactor(struct nodeAVL* pCurrNode){
    return getHeight(pCurrNode -> pRight) - getHeight(pCurrNode -> pLeft);
}

struct nodeAVL* rrRotation(struct nodeAVL* pCurrNode){
    //rotation
    struct nodeAVL* newRoot = pCurrNode -> pRight;
    pCurrNode -> pRight = newRoot -> pLeft;
    newRoot -> pLeft = pCurrNode;
 
    //update height
    pCurrNode -> height = 1 + getMax(getHeight(pCurrNode -> pLeft), getHeight(pCurrNode -> pRight));
    newRoot -> height = 1 + getMax(getHeight(newRoot -> pLeft), getHeight(newRoot -> pRight));
    
    //return
    return newRoot;
}

struct nodeAVL* llRotation(struct nodeAVL* pCurrNode){
    //rotation
    struct nodeAVL* newRoot = pCurrNode -> pLeft;
    pCurrNode -> pLeft = newRoot -> pRight;

    newRoot -> pRight = pCurrNode;
 
    //update height
    pCurrNode -> height = 1 + getMax(getHeight(pCurrNode -> pLeft), getHeight(pCurrNode -> pRight));
    newRoot -> height = 1 + getMax(getHeight(newRoot -> pLeft), getHeight(newRoot -> pRight));
    
    //return
    return newRoot;
}

struct nodeAVL* rlRotation(struct nodeAVL* pCurrNode){
    //rotation
    pCurrNode -> pRight = llRotation(pCurrNode -> pRight);
    return rrRotation(pCurrNode);
}

struct nodeAVL* lrRotation(struct nodeAVL* pCurrNode){
    pCurrNode -> pLeft = rrRotation(pCurrNode -> pLeft);
    return llRotation(pCurrNode);
}

struct nodeAVL* insertAVL(struct nodeAVL* pCurrNode, struct book* newBook){
    if(pCurrNode == NULL){
        struct nodeAVL* pTempNode = (struct nodeAVL*) malloc (sizeof(struct nodeAVL));
        pTempNode -> pBook = newBook;
        pTempNode -> pRight = NULL;
        pTempNode -> pLeft = NULL;
        pTempNode -> height = 0;
        return pTempNode;
    }
    
    else if (strcmp(pCurrNode -> pBook -> title, newBook -> title) > 0){
        pCurrNode -> pLeft = insertAVL(pCurrNode -> pLeft, newBook);
    }else if (strcmp(pCurrNode -> pBook -> title, newBook -> title) < 0){
        pCurrNode -> pRight = insertAVL(pCurrNode -> pRight, newBook); //handles the case where the title is the same
    }else{
        return pCurrNode;
    }

    //backtracking
    //recalculate the heights
    pCurrNode -> height =  1 + getMax(getHeight(pCurrNode -> pLeft), getHeight(pCurrNode -> pRight));
    short int balanceFactor = getBalanceFactor(pCurrNode);
    //Checking the imbalance with respect to the inserted node
    if(balanceFactor > 1){
        //RR
        if(strcmp(newBook -> title, pCurrNode -> pRight -> pBook -> title) > 0){
            pCurrNode = rrRotation(pCurrNode);
            }else{
            //RL
            pCurrNode = rlRotation(pCurrNode);
        }
    }else if(balanceFactor < -1){
        //LL
        if(strcmp(newBook -> title, pCurrNode -> pLeft -> pBook -> title) < 0){
            pCurrNode = llRotation(pCurrNode);
        }else{
            //LR
            pCurrNode = lrRotation(pCurrNode);
        }
    }
    return pCurrNode;
}

struct nodeAVL* minTree(struct nodeAVL* pCurrNode){
    while(pCurrNode -> pLeft != NULL){
        pCurrNode = pCurrNode -> pLeft;
    }
    return pCurrNode;
}

struct nodeAVL* returnSuccessorTwoChildren(struct nodeAVL* pCurrNode){
    return minTree(pCurrNode -> pRight);
}

/*
struct nodeAVL* deleteAVL(struct nodeAVL* pCurrNode, int val){
    if(pCurrNode == NULL)
    {
        puts("Node not found");
        return NULL;
    }

    if(pCurrNode -> value > val){
        pCurrNode -> pLeft = deleteAVL(pCurrNode -> pLeft, val);
    }else if(pCurrNode -> value < val){
        pCurrNode -> pRight = deleteAVL(pCurrNode -> pRight, val);
    }else{
        //we've found the node

        //the node has no children
        if(pCurrNode -> pLeft == NULL && pCurrNode -> pRight == NULL){
            free(pCurrNode);
            return NULL;
        }

        //the node has one child
        else if(pCurrNode -> pLeft != NULL && pCurrNode -> pRight == NULL){
            struct nodeAVL* returnNode = pCurrNode -> pLeft;
            free(pCurrNode);
            return returnNode;
        }else if(pCurrNode -> pLeft == NULL && pCurrNode -> pRight != NULL){
            struct nodeAVL* returnNode = pCurrNode -> pRight;
            free(pCurrNode);
            return returnNode;
        }

        //the node has two children
        else{
            //Find successor
            struct nodeAVL* successorNode = returnSuccessorTwoChildren(pCurrNode);

            //Copy Data
            pCurrNode -> value = successorNode -> value;

            //Free the node
            pCurrNode -> pRight = deleteAVL(pCurrNode -> pRight, successorNode -> value);
        }
    }


    //rebalancing
    pCurrNode -> height =  1 + getMax(getHeight(pCurrNode -> pLeft), getHeight(pCurrNode -> pRight));
    short int balanceFactor = getBalanceFactor(pCurrNode);

    //Checking in general
    if(balanceFactor > 1){
        //RR
        if(pCurrNode -> pRight -> pRight != NULL){
            pCurrNode = rrRotation(pCurrNode);
            }else{
            //RL
            pCurrNode = rlRotation(pCurrNode);
        }
    }else if(balanceFactor < -1){
        //LL
        if(pCurrNode -> pLeft -> pLeft != NULL){
            pCurrNode = llRotation(pCurrNode);
        }else{
            //LR
            pCurrNode = lrRotation(pCurrNode);
        }
    }
    return pCurrNode;
}
*/
void preDisplay(struct nodeAVL* pRoot){
    if (pRoot == NULL)
        return;

    printf("%s ", pRoot -> pBook -> title);
    preDisplay(pRoot -> pLeft);
    preDisplay(pRoot -> pRight);
}
