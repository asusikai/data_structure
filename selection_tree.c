#include <stdio.h>
#include <stdlib.h>
#define q_size 7

typedef struct ex_node{
    int que[q_size];
    int front;
    int rear;
}ex_node;

void enque(ex_node n, int x);
int deque(ex_node n);
void set_q(ex_node n);
int in_node[16];
int result_array[100];
ex_node en[16];

void swap(int *a, int *b);
void sort_insert(int arr[]);
int ex_compare(ex_node a, ex_node b);
void set();
int compete();

void new_set(int j);

int main()
{
    int i,j;
    for(i=0; i<15; i++)
    {
        set_q(en[i]);

        for(j=0; j<q_size; j++)
        {
            printf("%d", en[i].que[j]);
        }
        printf("\n");
    }
    

    set();
    result_array[0] = compete();
    printf("result: %d\n", result_array[0]);

    for(i = 0; i<7*16-1; i++)
    {
        new_set(i);
        result_array[i+1] = compete();
    }

    for(i = 0; i<7*16; i++)
    {
        printf("%d\n", result_array[i]);
    }
    
    

    return 0;
}

void enque(ex_node n, int x)
{
    n.que[++n.rear] = x;
}

int deque(ex_node n)
{
    return n.que[++n.front];
}

void set_q(ex_node n)
{
    n.front = 0;
    n.rear = 0;

    int i;
    int random;
    for(i = 0; i<q_size; i++)
    {
        random = rand()%1000;
        enque(n, random);
    }

    sort_insert(n.que);
}


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort_insert(int arr[])
{
    int i,j;
    for(i = 0; i<q_size; i++)
    {
        for(j = 0; j<q_size-1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int ex_compare(ex_node a, ex_node b)
{
    if( a.front == a.rear && b.front ==b.rear)
    {
        return 0;
    }

    else if(a.front <a.rear && b.front == b.rear)
    {
        return deque(a);
    }

    else if(a.front == a.rear && b.front < b.rear)
    {
        return deque(b);
    }

    else if(a.front < a.rear && b.front < b.rear)
    {
        if(a.que[a.front] < b.que[b.front])
        {
            return deque(a);
        }

        else
        {
            return deque(b);
        }
    }
}
void set()
{
    int i;
    for(i=8; i<16; i++)
    {
        in_node[i] = ex_compare(en[2*i-16], en[2*i-15]);
    }
}
int compete()
{
    int i = 15;

    while(i>1)
    {
        if(in_node[i] > in_node[i-1])
        {
            in_node[i/2] = in_node[i];      
        }

        else
        {
            in_node[i/2] = in_node[i-1];
        }
        i=i-2;
    }

    return in_node[i];
}

void new_set(int j)
{
    int i;
    for(i = 0; i< 16; i++)
    {
        if(en[i].que[en[i].front] == result_array[j])
        {
            if(i%2 == 0)
            {
                ex_compare(en[i], en[i+1]);
            }

            else
            {
                ex_compare(en[i-1], en[i]);
            }

            break;
        }

        
    }

}