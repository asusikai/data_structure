#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 21 //0번 index는 비워둔다.

int tree[SIZE];

void preorder(int i);

int main()
{
    int i;
    srand(time(NULL));

    for(i=1; i<SIZE; i++)
    {
        tree[i] = rand()%100+1;
    }

    printf("print tree array\n");
    for(i=1; i<SIZE; i++)
    {
        printf("%3d:%3d\n", i, tree[i]);
    }
    int num = 1;


    printf("print by preorder\n");
    preorder(1);


    return 0;
}

void preorder(int i)
{
    printf("%3d:%3d\n",i, tree[i]);
    if(i*2<SIZE)
    {
        preorder(i*2);
        preorder(i*2+1);
    }
}