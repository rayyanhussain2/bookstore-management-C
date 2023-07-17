/*
Balance Factor of a given node in a AVL Tree -1, 0, 1 (left heavy, balanced, right heavy)
Insertion, delete, search operation is O(logn) time.
Single Rotation
Double Rotation
height of a node in AVL trees is max height of its children + 1;

In insertion we only go up to the parent node until which there is a balance factor not from the range
{-1, 0, 1}. No further reordering required for ancestors. 
In deletion we have to go up to the root node because there might be nodes which are not balanced.

In insertion there are four cases after inserting a node. Refer to the picture. In single rotation,
we take h+2 as the pivot. In double we take h+1 as the pivot.

In deletion there might be cases when h+2 has two h+1 children. In such a case we do single rotation on h+2.
And deletion in AVL trees when a node has two children, we replace by its predecessor rather than its successor.
H or worst case time complexity is approx h < 1:4404 log2N;
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct nodeAVL{
    int value;
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

struct nodeAVL* insertAVL(struct nodeAVL* pCurrNode, int val){
    if(pCurrNode == NULL){
        struct nodeAVL* pTempNode = (struct nodeAVL*) malloc (sizeof(struct nodeAVL));
        pTempNode -> value = val;
        pTempNode -> pRight = NULL;
        pTempNode -> pLeft = NULL;
        pTempNode -> height = 0;
        return pTempNode;
    }
    else if (pCurrNode -> value > val){
        pCurrNode -> pLeft = insertAVL(pCurrNode -> pLeft, val);
    }else if (pCurrNode -> value < val){
        pCurrNode -> pRight = insertAVL(pCurrNode -> pRight, val); //handles the case where the title is the same
    }else{
        return pCurrNode;
    }

    //backtracking
    //recalculate the heights
    pCurrNode -> height =  1 + getMax(getHeight(pCurrNode -> pLeft), getHeight(pCurrNode -> pRight));
    short int balanceFactor = getBalanceFactor(pCurrNode);
    if(balanceFactor > 1){
        //RR
        if(val > pCurrNode -> pRight -> value){
            pCurrNode = rrRotation(pCurrNode);
            }else{
            //RL
            pCurrNode = rlRotation(pCurrNode);
        }
    }else if(balanceFactor < -1){
        //LL
        if(val < pCurrNode -> pLeft -> value){
            pCurrNode = llRotation(pCurrNode);
        }else{
            //LR
            pCurrNode = lrRotation(pCurrNode);
        }
    }
    return pCurrNode;
}



void preDisplay(struct nodeAVL* pRoot){
    if (pRoot == NULL)
        return;

    printf("%d ", pRoot -> value);
    preDisplay(pRoot -> pLeft);
    preDisplay(pRoot -> pRight);
}

int main(){
    int arr[] = {10, 20, 30, 40, 50, 25};
    int arrSize = 6;
    struct nodeAVL* pHead = NULL;
    for(int i = 0; i < arrSize; i++){
        pHead = insertAVL(pHead, arr[i]);
    }

    preDisplay(pHead);

    return 0;
}