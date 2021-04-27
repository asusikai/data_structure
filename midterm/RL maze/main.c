#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 9
#define COL 15

typedef struct position{
    int row;
    int col;
}position;

position cp;

typedef struct value{
    float val;
    float up;
    float down;
    float left;
    float right;
}value;

value v[ROW][COL];

void value_set();

void read_maze();
void print_maze();
char maze[ROW][COL];

int cmp_value();
void move();

int main()
{
    cp.col =1;
    cp.row =1;

    read_maze();
    print_maze();
    value_set();

    //int i;
    //for(i = 0; i<200; i++)
    while(1)
    {
        printf("vec: %d, %d\n", cp.row, cp.col);
        move();
        if(cp.row == ROW-2 && cp.col == COL-2)
        {
            break;
        }
    }
}

void value_set()
{
    int i,j;

    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            if(maze[i][j] == '1')
            {
                v[i][j].val = -20;
                v[i][j].up = 0;
                v[i][j].down = 0;
                v[i][j].left = 0;
                v[i][j].right = 0;
            }

            else if(maze[i][j] == '0')
            {
                v[i][j].val = 20;
                v[i][j].up = 0;
                v[i][j].down = 0;
                v[i][j].left = 0;
                v[i][j].right = 0;
            }
        }
    }

    v[ROW-2][COL-2].val = 200;
}

void read_maze()
{
    FILE *f;
    f = fopen("maze.txt", "r");
    int i;
    for(i=0; i<ROW; i++)
    {
        fscanf(f, "%s", maze[i]);
    }
    fclose(f);
}

void print_maze()
{
    int i,j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int cmp_value()
{
    float temp = v[cp.row][cp.col].up;

    if(temp < v[cp.row][cp.col].down)
    {
        temp = v[cp.row][cp.col].down;
    }
    if(temp < v[cp.row][cp.col].left)
    {
        temp = v[cp.row][cp.col].left;
    }
    if(temp < v[cp.row][cp.col].right)
    {
        temp = v[cp.row][cp.col].right;
    }

    if(temp == v[cp.row][cp.col].up)
    {
        return 1;
    }

    else if(temp == v[cp.row][cp.col].down)
    {
        return 2;
    }

    else if(temp == v[cp.row][cp.col].left)
    {
        return 3;
    }

    else //right
    {
        return 4;
    }

}

void move()
{
    //up
    if(cmp_value() == 1)
    {
        //goal
        if(cp.row-1 == ROW-2 && cp.col == COL-2)
        {
            v[cp.row][cp.col].up += v[cp.row-1][cp.col].val;
            cp.row--;
            printf("goal in.\n");

        }
        //out
        else if(cp.row == 0)
        {
            v[cp.row][cp.col].up -=100;
            cp.row = 1;
            cp.col = 1;
            printf("out of maze.\n");
        }

        //1
        else if(maze[cp.row-1][cp.col] == '1')
        {
            v[cp.row][cp.col].up += 0.8*v[cp.row-1][cp.col].val-1;
            cp.row--;
            v[cp.row][cp.col].down--;
            v[cp.row][cp.col].val -=10;

        }

        //0
        else if(maze[cp.row-1][cp.col] == '0')
        {
            v[cp.row][cp.col].up += 0.8*v[cp.row-1][cp.col].val-1;
            cp.row--;
            v[cp.row][cp.col].down--;
            v[cp.row][cp.col].val +=10;

        }
    }

    //down
    else if(cmp_value() == 2)
    {
        //goal
        if(cp.row+1 == ROW-2 && cp.col == COL-2)
        {
            v[cp.row][cp.col].down += v[cp.row+1][cp.col].val;
            cp.row++;
            printf("goal in.\n");

        }
        //out
        else if(cp.row == ROW-1)
        {
            v[cp.row][cp.col].down -=100;
            cp.row = 1;
            cp.col = 1;
            printf("out of maze.\n");
        }

        //1
        else if(maze[cp.row+1][cp.col] == '1')
        {
            v[cp.row][cp.col].down += 0.8*v[cp.row+1][cp.col].val+1;
            cp.row++;
            v[cp.row][cp.col].up--;
            v[cp.row][cp.col].val -=10;
        }

        //0
        else if(maze[cp.row+1][cp.col] == '0')
        {
            v[cp.row][cp.col].down += 0.8*v[cp.row+1][cp.col].val+1;
            cp.row++;
            v[cp.row][cp.col].up--;
            v[cp.row][cp.col].val +=10;

        }
    }

    //left
    else if(cmp_value() == 3)
    {
        //goal
        if(cp.row == ROW-2 && cp.col-1 == COL-2)
        {
            v[cp.row][cp.col].left += v[cp.row][cp.col-1].val;
            cp.col--;
            printf("goal in.\n");

        }
        //out
        else if(cp.col == 0)
        {
            v[cp.row][cp.col].left -=100;
            cp.row = 1;
            cp.col = 1;
            printf("out of maze.\n");
        }

        //1
        else if(maze[cp.row][cp.col-1] == '1')
        {
            v[cp.row][cp.col].left += 0.8*v[cp.row][cp.col-1].val-1;
            cp.col--;
            v[cp.row][cp.col].right--;
            v[cp.row][cp.col].val -=10;
        }

        //0
        else if(maze[cp.row][cp.col-1] == '0')
        {
            v[cp.row][cp.col].left += 0.8*v[cp.row][cp.col-1].val-1;
            cp.col--;
            v[cp.row][cp.col].right--;
            v[cp.row][cp.col].val +=10;
        }
    }

    //right
    else if(cmp_value() == 4)
    {
        //goal
        if(cp.row == ROW-2 && cp.col+1 == COL-2)
        {
            v[cp.row][cp.col].up += v[cp.row][cp.col+1].val;
            cp.col++;
            printf("goal in.\n");

        }
        //out
        else if(cp.col == COL-1)
        {
            v[cp.row][cp.col].right -=100;
            cp.row = 1;
            cp.col = 1;
            printf("out of maze.\n");
        }

        //1
        else if(maze[cp.row][cp.col+1] == '1')
        {
            v[cp.row][cp.col].right += 0.8*v[cp.row][cp.col+1].val+1;
            cp.col++;
            v[cp.row][cp.col].left--;
            v[cp.row][cp.col].val -=10;
        }

        //0
        else if(maze[cp.row][cp.col+1] == '0')
        {
            v[cp.row][cp.col].right += 0.8*v[cp.row][cp.col+1].val+1;
            cp.col++;
            v[cp.row][cp.col].left--;
            v[cp.row][cp.col].val +=10;
        }
    }

}
