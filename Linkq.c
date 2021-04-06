#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertq_a(char c);
void printq_a();
char deleteq_a();

void insertq_b(char c);
void printq_b();
char deleteq_b();

typedef struct node* nodeptr;
typedef struct node{
    char item;
    nodeptr next;
}node;

nodeptr front_a = NULL;
nodeptr rear_a = NULL;
nodeptr front_b = NULL;
nodeptr rear_b = NULL;

int main()
{
    char a[21], b[21];
    int i,j = 0;

    while(1)
    {
        printf("길이가 같은 2개 숫자 XOR 연산하기 (최대 20자리) exit 입력시 종료.\n");
        printf("1st num:");
        scanf("%s", &a);

        if(strcmp(a,"exit") == 0)
        {
            break;
        }

        while(a[i] != '\0')
        {
            insertq_a(a[i]);
            i++;
        }

        printf("2nd num:");
        scanf("%s", b);

        while(b[j] != '\0')
        {
            insertq_b(b[j]);
            j++;
        }

        if(strcmp(b,"exit") == 0)
        {
            break;
        }

        if( i != j)
        {
            printf("길이가 다릅니다. 같은 길이의 숫자를 넣어주세요.\n");
        }

        else
        {
            char x,y;
            for(i = 0; i<j; i++)
            {
                x = deleteq_a();
                y = deleteq_b();

                if(x == y)
                {
                    printf("0");
                }

                else
                {
                    printf("1");
                }
            }
            printf("\n");
        }
    }
    
}

void insertq_a(char c)
{
    nodeptr np = (nodeptr)malloc(sizeof(node));
    np->item = c;
    np->next = NULL;

    if(front_a == NULL)
    {
        front_a = np;
        rear_a = np;
    }

    else
    {
        rear_a->next = np;
        rear_a =np;
    }
}
void printq_a()
{
    nodeptr temp = front_a;
    printf("1st que: ");
    while(temp != NULL)
    {
        printf("%c", temp->item);
        temp = temp->next;
    }
    printf("\n");
}
char deleteq_a()
{
    nodeptr temp;
    char data;
    if(front_a == NULL)
    {
        printf("Queue_a is empty.\n");
    }
    else
    {
        temp = front_a;
        data = temp->item;
        front_a = front_a->next;
        free(temp);

        return data;
    }
}

void insertq_b(char c)
{
    nodeptr np = (nodeptr)malloc(sizeof(node));
    np->item = c;
    np->next = NULL;

    if(front_b == NULL)
    {
        front_b = np;
        rear_b = np;
    }
    else
    {
        rear_b->next = np;
        rear_b =np;
    }
}
void printq_b()
{
    nodeptr temp = front_b;
    printf("2nd que: ");
    while(temp != NULL)
    {
        printf("%c", temp->item);
        temp = temp->next;
    }
    printf("\n");
}
char deleteq_b()
{
    nodeptr temp;
    char data;
    if(front_b == NULL)
    {
        printf("Queue_b is empty.\n");
    }
    else
    {
        temp = front_b;
        data = temp->item;
        front_b = front_b->next;
        free(temp);

        return data;
    }
}