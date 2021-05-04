#include <stdio.h>
#include <stdlib.h>

int heap[25];
int top = 0;

void swap(int *a, int *b);
void insert_heap(int e);
int remove_heap();
void print_heap();

int main()
{
    int r;
    int i;
    
    for(i = 0; i<20; i++)
    {
        r = rand()%99+1;
        insert_heap(r);
    }
    
    print_heap();
}

void swap(int *a, int *b)
{
    int tem = *a;
    *a = *b;
    *b = tem;
}

void insert_heap(int e)
{
    int temp;

    heap[++top] = e;
    int i = top;

    while(i/2 >= 1)
    {
        if(heap[i]>heap[i/2])
        {
            swap(&heap[i], &heap[i/2]);
            i = i/2;
        }

        else
        {
            break;
        }
    }
}

int remove_heap()
{
    int max = heap[1];

    heap[1] = heap[top--];

    int i = 1;
    while(i <= top/2)
    {
        if(heap[i]<heap[i*2] || heap[i]<heap[i*2+1])
        {
            if(heap[i*2]>heap[i*2+1])
            {
                swap(&heap[i], &heap[i*2]);
                i = i*2;
            }

            else
            {
                swap(&heap[i], &heap[i*2+1]);
                i = i*2+1;
            }
        }

        else
        {
            break;
        }
    }

    return max;
}

void print_heap()
{
    printf("Printing Max Heap in index order.\n");
    int i;
    for(i = 1; i<=top; i++)
    {
        printf("%d : %d\n", i, heap[i]);
    }

    printf("After sorted.\n");
    while(top != 0)
    {
        printf("%d\n", remove_heap());
    }
}