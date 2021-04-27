#include <stdio.h>
#include <stdlib.h>

typedef struct node* ptr;
typedef struct node{

    int key;
    ptr left;
    ptr right;
}node;

ptr root = NULL;

void insert_node(ptr t, int key);
void search_node(ptr t, int key);
ptr find_smallest(ptr t);
ptr find_biggest(ptr t);
void delete_node(ptr parent, ptr t, int data);

void print_inorder(ptr t);

ptr _q[25];
int front = 0, rear = 0;
void enq(ptr q);
ptr deq();

void print_levelorder(ptr t);

int main()
{
    insert_node(root, 5);
    delete_node(NULL, root, 5);
    //printf("%d\n", root->key);
    print_inorder(root);
    printf("Done.\n");
    insert_node(root, 5);
    insert_node(root, 2);
    insert_node(root, 8);
    insert_node(root, 1);
    insert_node(root, 4);
    insert_node(root, 7);
    insert_node(root, 9);
    insert_node(root, 3);
    insert_node(root, 10);
    insert_node(root, 6);
    insert_node(root, 5);

    print_inorder(root);

    delete_node(NULL, root, 20);

    delete_node(NULL, root, 8);

    print_inorder(root);
    printf("Done.\n");

    delete_node(NULL, root, 10);

    print_inorder(root);
    printf("Done.\n");
    insert_node(root, 10);

    print_inorder(root);
    printf("Done.\n");
    print_levelorder(root);
    print_inorder(root);
    insert_node(root, 5);
    //printf("\n\n%d\n",root->key);
    print_levelorder(root);
    print_levelorder(root);
    //print_levelorder(root);

    search_node(root, 15);
    search_node(root, 7);
    return 0;
}

void insert_node(ptr t, int key)
{
    if(root == NULL)
    {
        ptr new_node = (ptr)malloc(sizeof(node));
        new_node->key = key;
        new_node->left = NULL;
        new_node->right = NULL;

        root = new_node;
    }

    else
    {
        if(key < t->key)
        {
            if(t->left != NULL)
            {
                insert_node(t->left, key);
            }

            else
            {
                ptr new_node = (ptr)malloc(sizeof(node));
                new_node->key = key;
                new_node->left = NULL;
                new_node->right = NULL;

                t->left = new_node;
            }

        }

        else if(key > t->key)
        {
            if(t->right != NULL)
            {
                insert_node(t->right, key);
            }

            else
            {
                ptr new_node = (ptr)malloc(sizeof(node));
                new_node->key = key;
                new_node->left = NULL;
                new_node->right = NULL;

                t->right = new_node;
            }
        }

        else
        {
            printf("%d is already in the tree.\n", key);
        }
    }
}

void search_node(ptr t, int key)
{
    if(key < t->key)
    {
        if(t->left != NULL)
        {
            search_node(t->left,key);
        }

        else
        {
            printf("there is no %d.\n", key);
        }
    }

    else if(key > t->key)
    {
        if(t->right != NULL)
        {
            search_node(t->right, key);
        }

        else
        {
            printf("there is no %d.\n", key);
        }
    }

    else
    {
        printf("found %d.\n", key);
    }
}

ptr find_smallest(ptr t)
{
    if(t->left != NULL)
    {
        find_smallest(t->left);
    }

    else
    {
        return t;
    }
}

ptr find_biggest(ptr t)
{
    if(t->right != NULL)
    {
        find_biggest(t->right);
    }

    else
    {
        return t;
    }
}
/*
void delete_node(ptr parent, ptr child, int key)
{
    if(key >child->key)
    {
        if(child->right == NULL)
        {
            printf("can't find %d.\n", key);
        }
        else
        {
            delete_node(child, child->right, key);
        }
    }

    else if(key < child->key)
    {
        if(child->left == NULL)
        {
            printf("can't find %d.\n", key);
        }
        else
        {
            delete_node(child, child->left, key);
        }
    }

    else // key == child->key
    {
        if(child->left == NULL && child->right == NULL)
        {
            if(parent == NULL)
            {
                root = NULL;
            }

            else
            {
                if(parent->left == child)
                {
                    parent->left = NULL;
                }

                else
                {
                    parent->right = NULL;
                }
                free(child);
            }
        }

        else if(child->left == NULL && child->right != NULL)
        {
            if(parent == NULL)
            {
                root = child->right;
            }

            else if(parent->left == child)
            {
                parent->left = child->right;
                free(child);
            }

            else if(parent->right == child)
            {
                parent->right = child->right;
                free(child);
            }
        }

        else if(child->left != NULL && child->right == NULL)
        {
            if(parent == NULL)
            {
                root = child->left;
            }

            else if(parent->left == child)
            {
                parent->left = child->left;
                free(child);
            }

            else if(parent->right == child)
            {
                parent->right = child->left;
                free(child);
            }
        }

        else // left not null & right not null
        {
            ptr temp = find_biggest(child->left);
            child->key = temp->key;
            delete_node(child, child->left, temp->key);
        }
    }
}*/

void delete_node(ptr parent, ptr t, int data)
{
    if(data < t->key)
    {
        if(t->left != NULL)
        {
            delete_node(t, t->left, data);
        }

        else
        {
            printf("can't find %d.\n", data);
        }
    }

    else if(data > t->key)
    {
        if(t->right != NULL)
        {
            delete_node(t, t->right, data);
        }

        else
        {
            printf("can't find %d.\n", data);
        }

    }

    else
    {
        //t == root
        if(parent == NULL)
        {
            if(t->left == NULL && t->right == NULL)
            {
                root = NULL;
            }

            else if(t->left != NULL && t->right == NULL)
            {
                ptr temp = root;
                root = t->left;
                free(temp);
            }

            else if(t->left == NULL && t->right != NULL)
            {
                ptr temp = root;
                root = t->left;
                free(temp);
            }

            else // both not null
            {
                ptr temp = find_smallest(t->right);
                t->key = temp->key;
                delete_node(t,t->right,temp->key);
            }
        }

        else //parent != NULL
        {
            if(parent->left == t)
            {
                if(t->left == NULL && t->right == NULL)
                {
                    parent->left = NULL;
                    free(t);
                }

                else if(t->left != NULL && t->right == NULL)
                {
                    parent->left = t->left;
                    free(t);
                }

                else if(t->left == NULL && t->right != NULL)
                {
                    parent->left = t->right;
                    free(t);
                }

                else // both not null
                {
                    ptr temp = find_smallest(t->right);
                    t->key = temp->key;
                    delete_node(t,t->right,temp->key);
                }
            }

            else
            {
                if(t->left == NULL && t->right == NULL)
                {
                    parent->right = NULL;
                    free(t);
                }

                else if(t->left != NULL && t->right == NULL)
                {
                    parent->right = t->left;
                    free(t);
                }

                else if(t->left == NULL && t->right != NULL)
                {
                    parent->right = t->right;
                    free(t);
                }

                else // both not null
                {
                    ptr temp = find_smallest(t->right);
                    t->key = temp->key;
                    delete_node(t,t->right,temp->key);
                }
            }
        }
    }
}

void print_inorder(ptr t)
{
    if(t != NULL)
    {
        print_inorder(t->left);
        printf("%d\n", t->key);
        print_inorder(t->right);
    }
}

void enq(ptr q)
{
    if(rear < 24)
    {
        _q[++rear] = q;
    }
}
ptr deq()
{
    if(rear >= front)
    {
        return _q[++front];
    }
}

void print_levelorder(ptr t)
{
    if(t == NULL)
    {
        printf("empty.\n");
        return;
    }
    enq(t);

    ptr temp;

    while(1)
    {
        temp = deq();

        if(temp != NULL)
        {
            printf("%d\n", temp->key);
            if(temp->left!=NULL)
            {
                enq(temp->left);
            }

            if(temp->right != NULL)
            {
                enq(temp->right);
            }
        }
        else
        {
            break;
        }
    }
    front = rear = 0;
}
