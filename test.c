#include <stdio.h>

void test(int start){
    printf("%d\n", ++start);
    test(start);
}
int main()
{
    test(0);
}