#include <stdio.h>
#include <string.h>

#define ROW 9
#define COL 16

char maze[ROW][COL];
int cp[ROW*COL][2]; //좌표 row,col
int top = -1;

int IsEnd();

int IsFull();
int IsEmpty();
void push(int pos[2]);
int* pop();


void move(int cp[][2], char visited[][COL]); //입력값에 따라 위치 변경해주는 함수
int IsBlocked(int cp[][2], char visited[][COL]);
/////////////////////////////////////////////////////////////////////////////////
int main()
{
    FILE *f = fopen("maze.txt", "r"); //maze txt file open
    char input[100];
    char v[ROW][COL] = {
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}
    };
    //char screen[ROW][COL];

    int i;

//maze 안에 파일 옮기기
    for(i=0; i<ROW; i++)
    {
        fgets(input, sizeof(input), f);
        strcpy(maze[i], input);
        //strcpy(screen[i], input);
    }

    fclose(f);
    
    int start[2] = {1,1};

    push(start);
    printf("start: %d,%d\n", start[0],start[1]);

    
    //while(!IsEnd())

    for(i=0; i<40; i++)
    {
        move(cp, v);
        printf("m_current pos: %d, %d\n", cp[top][0], cp[top][1]);
        while(IsBlocked(cp, v))
        {
            pop();
            printf("back\nb_current pos: %d, %d\n", cp[top][0], cp[top][1]);
        }
    }
    
    printf("route :\n");
    for(i=0; i<top; i++)
    {
        printf("%d, %d\n",cp[i][0],cp[i][1]);
    }



    return 0;
}
///////////////////////////////////////////////////////////////////////
int IsEnd()
{
    if(cp[top][0] == 7 && cp[top][1] == 13)
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
    if(top < ROW*COL-1)
    {
        return 0;
    }

    else
    {
        return 1;
    }
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

void push(int pos[2])
{
    if(!IsFull())
    {
        top++;
        cp[top][0] = pos[0];
        cp[top][1] = pos[1];
    }
}
int* pop()
{
    if(!IsEmpty())
    {
        return cp[top--];
    }
}


void move(int cp[][2], char visited[][COL])
{
    int curr[2];
    curr[0] = cp[top][0];
    curr[1] = cp[top][1];
    
    int next[2];
    printf("v:%c\n", visited[curr[0]][curr[1]]);
    printf("m:%c\n", maze[curr[0]][curr[1]]);
    visited[curr[0]][curr[1]] = '1';
    if((visited[curr[0]-1][curr[1]] == '0') && (maze[curr[0]-1][curr[1]] == '0')) // 위방향이 둘다 0이면
    {
        next[0]= curr[0]-1;
        next[1]= curr[1];
        //printf("next: %d, %d\n", next[0], next[1]);
        push(next);
        printf("move up\n");
    }

    else if((visited[curr[0]+1][curr[1]] == '0') && (maze[curr[0]+1][curr[1]] == '0')) // 아래방향이 둘다 0이면
    {
        next[0]= curr[0]+1;
        next[1]= curr[1];
        //printf("next: %d, %d\n", next[0], next[1]);
        push(next);
        printf("move down\n");
    }

    else if((visited[curr[0]][curr[1]-1] == '0') && (maze[curr[0]][curr[1]-1] == '0')) // 왼방향이 둘다 0이면
    {
        next[0]= curr[0];
        next[1]= curr[1]-1;
        //printf("next: %d, %d\n", next[0], next[1]);
        push(next);
        printf("move left\n");
    }
    


    else if((visited[curr[0]][curr[1]+1] == '0') && (maze[curr[0]][curr[1]+1] == '0')) // 오른방향이 둘다 0이면
    {
        next[0]= curr[0];
        next[1]= curr[1]+1;
        //printf("next: %d, %d\n", next[0], next[1]);
        push(next);
        printf("move right\n");
    }

    else
    {
        printf("no move\n");
    }

}

int IsBlocked(int cp[][2], char visited[][COL])
{
    if((visited[cp[top][0]-1][cp[top][1]] == '1' || maze[cp[top][0]-1][cp[top][1]] == '1')\
    &&(visited[cp[top][0]+1][cp[top][1]] == '1' || maze[cp[top][0]+1][cp[top][1]] == '1')\
    &&(visited[cp[top][0]][cp[top][1]-1] == '1' || maze[cp[top][0]][cp[top][1]-1] == '1')\
    &&(visited[cp[top][0]][cp[top][1]+1] == '1' || maze[cp[top][0]][cp[top][1]+1] == '1'))
    {
        return 1;
    }

    else
    {
        return 0;
    }
}