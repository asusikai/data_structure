#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *ptr;
typedef struct node
{
    char type;
    char name[10];
    ptr child;
    ptr sib;

}node;

ptr root, current;

void insert_node(char name[], char type);

void del_file(char name[]);
void free_dir(ptr dir);
void del_dir(char name[]);

void change_dir(ptr p, char name[]);

void print_preorder(ptr p);

int main()
{
    root = (ptr)malloc(sizeof(node));
    root->type = 'd';
    strcpy(root->name, "root");
    root->child = NULL;
    root->sib = NULL;

    current = root;
    
    insert_node("bskim", 'd');
    change_dir(root, "bskim");
    insert_node("homework1", 'f');

    printf("\nprint LCRS before delete\n");
    print_preorder(root);

    change_dir(root, "bskim");
    del_file("homework1");

    printf("\nprint LCRS after delete file\n");
    print_preorder(root);

    change_dir(root, "root");
    del_dir("bskim");

    printf("\nprint LCRS after delete directory\n");
    print_preorder(root);




    return 0;
}

void insert_node(char name[], char type)
{
    
    if(current->type == 'd')
    {
        ptr new_node = (ptr)malloc(sizeof(node));
        new_node->type = type;
        strcpy(new_node->name , name);
        new_node->child = NULL;
        new_node->sib = NULL;

        if(current->child != NULL)
        {
            ptr temp = current->child;

            while(temp->sib != NULL)
            {
                if(strcmp(temp->name, name) == 0 && temp->type == type)
                {
                    printf("it's already in the directory.\n");
                    return;
                }
                temp = temp->sib;
            }
            temp->sib = new_node;
            printf("%s is added in current directory(%s).\n", new_node->name, current->name);
        }

        else
        {
            current->child = new_node;
            printf("%s is added in current directory(%s).\n", new_node->name, current->name);
        }
    }

    else // type == 'f'
    {
        printf("Can't make file or directory in the file.\n");
    }
}

void change_dir(ptr p, char name[])
{
    if(strcmp(p->name, name) != 0)
    {
        if(p->sib != NULL)
        {
            change_dir(p->sib, name);
        }

        if(p->child != NULL)
        {
            change_dir(p->child, name);
        }
    }

    else if(strcmp(p->name, name) == 0 && p->type == 'd')
    {
        current = p;
        printf("changed dir to %s\n", p->name);
    }
    else if(strcmp(p->name, name) == 0 && p->type == 'f')
    {
        printf("%s type is %c\n", p->name, p->type);
    }

}

void del_file(char name[])
{
    ptr temp = current;
    ptr t = current->child;

    while(t != NULL && (strcmp(t->name, name) != 0 || t->type != 'f'))
    {
        temp = t;
        t = t->sib;
    }

    if(t == NULL)
    {
        printf("there is no file called %s in this directory.\n", name);
    }

    else
    {
        if(temp == current)
        {
            temp->child = t->sib;
            free(t);
        }

        else
        {
            temp->sib = t->sib;
            free(t);
        }
    }

}

void free_dir(ptr dir)
{
    if(dir != NULL)
    {
        free_dir(dir->sib);
        free_dir(dir->child);
        free(dir);
    }
}

void del_dir(char name[])
{
    ptr temp = current;
    ptr t = current->child;

    while(t != NULL && (strcmp(t->name, name) != 0 || t->type != 'd'))
    {
        temp = t;
        t = t->sib;
    }

    if(t == NULL)
    {
        printf("There is no directory called %s in this directory.\n", name);
    }

    else
    {
        if(temp == current)
        {
            temp->child = t->sib;
            free_dir(t);
        }

        else
        {
            temp->sib = t->sib;
            free_dir(t);
        }
    }
}

void print_preorder(ptr p)
{
    if(p != NULL)
    {
        printf("name: %s, type: %c  ", p->name, p->type);
        print_preorder(p->sib);
        printf("\n");
        print_preorder(p->child);
    }
}