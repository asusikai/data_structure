// level order//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 30

typedef struct node *treeptr;
typedef struct node{
	treeptr left;
	treeptr right;
	int data;
}node;

treeptr root = NULL;

void insert_node(treeptr t, int n);
void delete_node(treeptr t, int n);

treeptr find_smallest(treeptr t);

treeptr que[SIZE];
int front = 0, rear = 0;
void en_q(treeptr t);
treeptr de_q();

void levelorder(treeptr t);

void inorder(treeptr t);
void preorder(treeptr t);
void postorder(treeptr t);

int main()
{
	insert_node(root,5);
	insert_node(root,2);
	insert_node(root,3);
	insert_node(root,4);
	insert_node(root,7);
	insert_node(root,9);
	insert_node(root,8);
	insert_node(root,1);
	insert_node(root,10);
	
	levelorder(root);
	levelorder(root);
	levelorder(root);
	
	printf("inorder\n");
	inorder(root);
	printf("preorder\n");
	preorder(root);
	printf("postorder\n");
	postorder(root);
	
}

void insert_node(treeptr t, int n)
{
	treeptr new_node = (treeptr)malloc(sizeof(node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = n;
	if(root == NULL)
	{
		 root = new_node;
	}
	
	else
	{
		if(n < t->data)
		{
			if(t->left == NULL)
			{
				t->left = new_node;
			}
			
			else
			{
				insert_node(t->left, n);
			}
		}
		
		else if(n > t->data)
		{
			if(t->right == NULL)
			{
				t->right = new_node;
			}
			
			else
			{
				insert_node(t->right, n);
			}
		}
		
		else
		{
			printf("%d already in the tree.\n", n);
		}
	}
}
void delete_node(treeptr t, int n)
{
	if(t == NULL)
	{
		printf("can't find %d. \n", n);
	}
	
	else
	{
		if(n < t->data)
		{
			delete_node(t->left, n);
		}
		
		else if(n > t->data)
		{
			delete_node(t->right, n);
		}
		
		else
		{
			treeptr temp = find_smallest(t->right);
			
			t->data = temp->data;
			
			free(temp);
		}
	}
}

treeptr find_smallest(treeptr t)
{
	if(t->left == NULL)
	{
		return t;
	}
	
	else
	{
		find_smallest(t->left);
	}
}

void en_q(treeptr t)
{
	que[++rear] = t;
}
treeptr de_q()
{
	return que[++front];
}

void levelorder(treeptr t)
{
	printf("level order\n");
	if(t == NULL)
	{
		return ;
	}
	
	else
	{
		en_q(t);
		treeptr temp;
		while(1)
		{
			temp = de_q();
			
			if(temp != NULL)
			{
				printf("%d\n", temp->data);
			
				if(temp->left != NULL)
				{
					en_q(temp->left);
				}
			
				if(temp->right != NULL)
				{
					en_q(temp->right);
				}	
			}
			
			else
			{
				break;
			}
		}
		
		rear = front = 0;
		
		
	}
}
void inorder(treeptr t)
{
	if(t != NULL)
	{
		inorder(t->left);
		printf("%d\n",t->data);
		inorder(t->right);	
	}
	
}
void preorder(treeptr t)
{
	if(t != NULL)
	{
		printf("%d\n", t->data);
		preorder(t->left);
		preorder(t->right);
	}

}

void postorder(treeptr t)
{
	if(t != NULL)
	{
		postorder(t->left);
		postorder(t->right);
		printf("%d\n", t->data);
	}

}
