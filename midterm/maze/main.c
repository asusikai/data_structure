// maze

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 9
#define COL 15

typedef struct position* ptr;
typedef struct position{

    int row;
    int col;
}position;

ptr stack[ROW*COL];
int top = -1;

void push(ptr p);
ptr pop();

char visited[ROW][COL] = {{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
{'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}};

ptr cp = NULL;
void move(ptr cp, char maze[][COL]);

void print_maze(char maze[][COL]);

int main()
{
	char maze[ROW][COL];
	FILE *f;
	f = fopen("maze.txt", "r");
	int i;

	for(i=0; i<ROW; i++)
	{
		fscanf(f, "%s", maze[i]);
	}

	cp = (ptr)malloc(sizeof(position));
	cp->col = 1;
	cp->row = 1;

	push(cp);
	print_maze(maze);
    printf("\n");

	while(cp->row != ROW-2 || cp->col != COL-2)
    {
        move(cp, maze);
        printf("%d %d\n", cp->row, cp->col);
        print_maze(maze);
        printf("\n");
    }
}

void push(ptr p)
{
    if(top <ROW*COL-1)
    {
        stack[++top] = p;
    }

    else
    {
        printf("stack is full.\n");
    }
}

ptr pop()
{
    if(top >=-1)
    {
        return stack[top--];
    }

    else
    {
        printf("stack is empty.\n");
    }
}


void move(ptr cp,char maze[][COL])
{
    //down
    if(maze[cp->row+1][cp->col] == '0' && visited[cp->row+1][cp->col]=='0')
    {
        cp->row=cp->row+1;
        visited[cp->row][cp->col] = '1';
        push(cp);
    }
    //right
    else if(maze[cp->row][cp->col+1] == '0' && visited[cp->row][cp->col+1]=='0')
    {
        cp->col++;
        visited[cp->row][cp->col] = '1';
        push(cp);
    }
    //up
    else if(maze[cp->row-1][cp->col] == '0' && visited[cp->row-1][cp->col]=='0')
    {
        cp->row--;
        visited[cp->row][cp->col] = '1';
        push(cp);
    }

    //left
    else if(maze[cp->row][cp->col-1] == '0' && visited[cp->row][cp->col-1]=='0')
    {
        cp->col--;
        visited[cp->row][cp->col] = '1';
        push(cp);
    }
    //blocked
    else
    {
        while((maze[cp->row+1][cp->col] == '1' || visited[cp->row+1][cp->col]=='1')\
              &&(maze[cp->row][cp->col+1] == '1' || visited[cp->row][cp->col+1]=='1')\
              &&(maze[cp->row-1][cp->col] == '1' || visited[cp->row-1][cp->col]=='1')\
              &&(maze[cp->row][cp->col-1] == '1' || visited[cp->row][cp->col-1]=='1'))
        {
            cp = pop();
        }
    }
}

void print_maze(char maze[][COL])
{
    int i, j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            if(stack[top]->row == i && stack[top]->col == j)
            {
                printf("X");
            }
            else
            {
                printf("%c", maze[i][j]);
            }
        }
        printf("\n");
    }
}
