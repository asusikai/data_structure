#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 40

typedef struct tree_node *tree_ptr;
typedef struct tree_node{
    tree_ptr left;
    int data;
    tree_ptr right;
}tree;

tree_ptr root = NULL;
tree_ptr Queue[MAX_QUEUE_SIZE];

void searchBST(tree_ptr t, int key);
void insertBST(tree_ptr t, int key);
void deleteBST();
int find_smallest(tree_ptr t);

int front = 0;
int rear = 0; // 전역변수 선언


void Enqueue(tree_ptr ptr);
tree_ptr Dequeue();
void levelOrder(tree_ptr ptr);

int main()
{
    insertBST(root,5);
    insertBST(root,6);
    insertBST(root,9);
    insertBST(root,8);
    insertBST(root,4);
    insertBST(root,7);
    insertBST(root,8);
    insertBST(root,3);
    insertBST(root,1);
    insertBST(root,2);
    insertBST(root,10);

    searchBST(root,7);
    searchBST(root,12);

    printf("print in levelorder.\n");
    levelOrder(root);
    deleteBST(root, 7);
    deleteBST(root ,20);
    levelOrder(root);
}

void searchBST(tree_ptr t, int key)
{
    tree_ptr search;

    if(t == NULL)
    {
        printf("data %d not found.\n", key);
    }

    else
    {
        search = t;
        if(search->data == key)
        {
            printf("data %d found.\n", key);
        }
        else if(search->data > key)
        {
            searchBST(search->left, key);
        }

        else // search->data < key
        {
            searchBST(search->right, key);
        }

    }
}

void deleteBST(tree_ptr t, int key)
{
    if(t == NULL)
    {
        printf("can't delete. not found.\n");
    }

    else
    {
        if(t->data > key)
        {
            deleteBST(t->left, key);
        }

        else if(t->data < key)
        {
            deleteBST(t->right, key);
        }

        else // t->data == key
        {
            int temp = t->data;
            t->data = find_smallest(t->right);
            printf("%d delete -> %d\n", temp, t->data);
            
        }
    }
}
int find_smallest(tree_ptr t)
{
    if(t->left == NULL)
    {
        return t->data;
    }
    else
    {
        find_smallest(t->left);
    }
}

void insertBST(tree_ptr t, int key)
{
    if(root != NULL)
    {
        if(t->data > key)
        {
            if(t->left != NULL)
            {
                insertBST(t->left, key);
            }

            else // t->left == NULL
            {
                tree_ptr new;
                new = (tree_ptr)malloc(sizeof(tree));
                new->data = key;
                new->left = NULL;
                new->right = NULL;

                t->left = new;
                printf("%d inserted.\n",key);
            }
        }

        else if(t->data < key)
        {
            if(t->right != NULL)
            {
                insertBST(t->right, key);
            }

            else // t->right == NULL
            {
                tree_ptr new;
                new = (tree_ptr)malloc(sizeof(tree));
                new->data = key;
                new->left = NULL;
                new->right = NULL;

                t->right = new;
                printf("%d inserted.\n",key);
            }

        }

        else // t->data == key
        {
            printf("%d is already inside.\n", key);
        }               
    }

    else // root == NULL
    {
        root = (tree_ptr)malloc(sizeof(tree));
        root->data = key;
        root->left = NULL;
        root->right = NULL;
        printf("%d inserted.\n",key);
    }
    
}


void Enqueue(tree_ptr ptr)
{
	Queue[++rear] = ptr;
}

tree_ptr Dequeue()
{
	return Queue[++front];
}

void levelOrder(tree_ptr ptr)
{
	if (!ptr)
		return;
	
	Enqueue(ptr);  

	while (1) {
		ptr = Dequeue();
		if (ptr)
		{
			printf("%d ", ptr->data);

			if (ptr->left)
				Enqueue(ptr->left);
                
			if (ptr->right)
				Enqueue(ptr->right);
                
		}
		else
			break; 
	}
}
