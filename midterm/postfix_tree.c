// postfix tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20



typedef struct node* treeptr;
typedef struct node{
	treeptr left;
	treeptr right;
	char data;
}node;

treeptr stack[SIZE];
int top = -1;
void push(treeptr t);
treeptr pop();

treeptr root = NULL;

char c_stack[SIZE];
int c_top = -1;
void c_push(char c);
char c_pop();

void insert_node(char c);

void inorder(treeptr t);
void levelorder(treeptr t);

int main()
{
	char input[20];
	strcpy(input,"ab+cd-*ef/gh+/*");
	printf("%s\n", input);
	
	int i=0;
	
	while(input[i] != '\0')
	{
		insert_node(input[i++]);
	}
	
	root = stack[0];
	
	inorder(root);
	
	while(c_top != -1)
	{
		printf("%c",c_pop());
	}
	
	
	
	return 0;
}

void push(treeptr t)
{
	stack[++top] = t;
}
treeptr pop()
{
	return stack[top--];
}

void insert_node(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/')
	{
		treeptr new_node = (treeptr)malloc(sizeof(node));
		new_node->left = pop();
		new_node->right = pop();
		new_node->data = c;
		push(new_node);
	}
	
	else
	{	treeptr new_node = (treeptr)malloc(sizeof(node));
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->data = c;
		push(new_node);
	}
}

void c_push(char c)
{
	c_stack[++c_top] = c;
}
char c_pop()
{
	return c_stack[c_top--];
}

void inorder(treeptr t)
{
	if(t!=NULL)
	{
		
		inorder(t->left);
		c_push(t->data);
		inorder(t->right);
	}
}
