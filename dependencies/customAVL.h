int getMax(int a, int b);

int getHeight(struct bookNode* pCurrBook);

int getBalanceFactor(struct bookNode* pCurrBook);

struct bookNode* rrRotation(struct bookNode* pCurrBook);

struct bookNode* llRotation(struct bookNode* pCurrBook);

struct bookNode* rlRotation(struct bookNode* pCurrBook);

struct bookNode* insertAVL(struct bookNode* pCurrBook, struct bookNode* pNewBook);

struct bookNode* minTree(struct bookNode* pCurrBook);

struct bookNode* returnSuccessorTwoChildren(struct bookNode* pCurrBook);

struct bookNode* deleteAVL(struct bookNode* pCurrBook, char* bookSearchTitle);

struct bookNode* searchNode(struct bookNode* pCurrBook, char* titleSearch, struct bookNode** bookFound);

void preDisplay(struct bookNode* pRoot);

struct bookNode* freeNodes(struct bookNode* pNode);

#include "src/customAVL.c"