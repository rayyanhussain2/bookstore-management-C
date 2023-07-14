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
    unsigned long long height;
    struct nodeAVL* pLeft;
    struct nodeAVL* pRight;
};

struct nodeAVL* insertAVL(struct nodeAVL* pCurrNode, int val)
{
    struct nodeAVL* pHeadNode = pCurrNode;
    struct nodeAVL* pParentNode = NULL;
    bool leftChild = false;
    bool rightChild = false;

    while(pCurrNode != NULL){
        if(pCurrNode -> value > val){
            pParentNode = pCurrNode;
            pCurrNode = pCurrNode -> pLeft;
            leftChild = true;
            rightChild = false;
        }
        else{
            pParentNode = pCurrNode;
            pCurrNode = pCurrNode -> pRight;
            leftChild = false;
            rightChild = true;
        }
    }

    pCurrNode = (struct nodeAVL*) malloc (sizeof(struct nodeAVL));
    pCurrNode -> height = 0;
    pCurrNode -> pLeft = NULL;
    pCurrNode -> pRight = NULL;
    pCurrNode -> value = val;

    if(pParentNode == NULL){
        return pCurrNode;
    }
    else
    {
        if(leftChild){
            pParentNode -> pLeft = pCurrNode;
        }
        else{
            pParentNode -> pRight = pCurrNode;
        }
        return pHeadNode;
    }
}

int main()
{
    int arr[] = {5, 6, 7, 8, 2, 3};
    int arrSize = 6;
    struct nodeAVL* pHead = NULL;

    for(int i = 0; i < arrSize; i++)
    {

    }

    return 0;
}