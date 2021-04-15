#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE 30

typedef struct node* treeptr;
typedef struct node{
    char data;

    treeptr left;
    treeptr right;
}node;

treeptr stack[SIZE];
int top = -1;

int IsEmpty();
int IsFull();
void push(char n);
void push_ptr(treeptr t);
treeptr pop();

void tree(char c);
void pre_order(treeptr t);
void post_order(treeptr t);
void in_order(treeptr t);

treeptr root;

int main()
{
    root = (treeptr)malloc(sizeof(node));

    char input[20] = "ab+cd-*ef/gh+/*";
    int len = strlen(input);
    int i;
    for(i=0; i<len; i++)
    {
        tree(input[i]);
    }
    
    root = stack[0];

    printf("preorder\n");
    pre_order(root);
    printf("\n");

    root = stack[0];
    printf("postorder\n");
    post_order(root);
    printf("\n");

    printf("inorder\n");
    in_order(root);
    printf("\n");


}

int IsEmpty()
{
    if(top == -1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int IsFull()
{
    if(top == SIZE)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

void push(char n)
{
    if(!IsFull())
    {
        treeptr temp;
        temp = (treeptr)malloc(sizeof(node));
        temp->data = n;
        temp->left = NULL;
        temp->right = NULL;

        stack[++top] = temp;
    }

    else
    {
        printf("stack is full.");
    }
}

treeptr pop()
{
    if(!IsEmpty())
    {
        return stack[top--];
    }

    else
    {
        //printf("stack is empty.");
    }
}

void push_ptr(treeptr t)
{
    if(!IsFull())
    {
        stack[++top] = t;
    }

    else
    {
        printf("stack is full.");
    }
}

void tree(char c)
{
    if(isdigit(c) != 0)
    {
        push(c);
    }

    else
    {
        push(c);
        treeptr temp;
        temp = (treeptr)malloc(sizeof(node));
        temp = pop();

        temp->left = pop();
        temp->right = pop();
        push_ptr(temp);
    }
}

void pre_order(treeptr t)
{
    if(t != NULL)
    {
        printf("%c",t->data);
        pre_order(t->left);
        pre_order(t->right);
    }
}

void post_order(treeptr t)
{
    if(t != NULL)
    {
        post_order(t->left);
        post_order(t->right);
        printf("%c",t->data);
    }

}

void in_order(treeptr t)
{
    if(t != NULL)
    {
        in_order(t->left);
        printf("%c",t->data);
        in_order(t->right);
    }
}
