#include <stdio.h>
#include <stdlib.h>

typedef struct node* ptr;
typedef struct node{
    int data;
    ptr pre;
    ptr next;
}node;

ptr head = NULL;

void add_node(ptr p, int n);
void del_node(ptr p, int n);
void print_node(ptr p);
int main()
{
    add_node(head, 15);
    add_node(head, 7);
    add_node(head, 19);
    add_node(head, 21);
    add_node(head, 17);
    add_node(head, 9);
    add_node(head, 11);
    add_node(head, 13);

    print_node(head);

    del_node(head, 10);
    del_node(head, 15);

    print_node(head);
    return 0;
}

void add_node(ptr p, int n)
{
    ptr new_node = (ptr)malloc(sizeof(node));
    new_node->data = n;

    if(head == NULL)
    {
        head = (ptr)malloc(sizeof(node));
        new_node->pre = NULL;
        new_node->next = NULL;
        head = new_node;
    }

    else
    {
        if(n > p->data)
        {
            if(p->next != NULL)
            {
                if(n > p->next->data)
                {
                    add_node(p->next, n);
                }

                else
                {
                    new_node->next = p->next;
                    new_node->pre = p;
                    p->next->pre = new_node;
                    p->next = new_node;
                }

            }

            else
            {
                p->next = new_node;
                new_node->pre = p;
                new_node->next = NULL;
            }
        }

        else if(n < p->data)
        {
            if(p->pre != NULL)
            {
                if(n < p->pre->data)
                {
                    add_node(p->pre, n);
                }

                else
                {
                    new_node->next = p;
                    new_node->pre = p->pre;
                    p->pre->next = new_node;
                    p->pre = new_node;
                }
            }

            else
            {
                p->pre = new_node;
                new_node->next = p;
                new_node->pre = NULL;
                head = new_node;
            }
        }

        else
        {
            printf("%d is already in.", n);
        }
    }
}

void del_node(ptr p, int n)
{
    if(n < p->data)
    {
        if(p->pre != NULL)
        {
            if(n > p->pre->data)
            {
                printf("there is no %d.\n", n);
            }

            else
            {
                del_node(p->pre,n);
            }
        }

        else
        {
            printf("there is no %d.\n", n);
        }
    }

    else if(n > p->data)
    {
        if(p->next != NULL)
        {
            if(n < p->next->data)
            {
                printf("there is no %d.\n", n);
            }

            else
            {
                del_node(p->next, n);
            }

        }

        else
        {
            printf("there is no %d.\n", n);
        }
    }

    else
    {
        if(p->pre == NULL && p->next != NULL)
        {
            ptr temp = p;
            p = p->next;
            free(temp);
        }

        else if(p->pre != NULL && p->next == NULL)
        {
            ptr temp = p->pre;
            temp->next = NULL;
            free(p);
        }

        else if(p->pre == NULL && p->next == NULL)
        {
            ptr temp = p;
            p = NULL;
            free(temp);
        }

        else
        {
            p->pre->next = p->next;
            p->next->pre = p->pre;

            free(p);
        }
    }
}

void print_node(ptr t)
{
    printf("%d\n", t->data);
    if(t->next != NULL)
    {
        print_node(t->next);
    }
}
