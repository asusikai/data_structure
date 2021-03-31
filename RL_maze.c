#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW 9
#define COL 16

char maze[ROW][COL];
int cp[ROW*COL][2]; //좌표 row,col 순서쌍 stack
int top = -1;

int IsEnd();

int IsFull();
int IsEmpty();
void push(int pos[2]);
int* pop();

void move(int cp[][2], char visited[][COL]); //입력값에 따라 위치 변경해주는 함수
int IsBlocked(int cp[][2], char visited[][COL]); //막혔는지 체크하는 함수 -결과적으로 사용안함 ㅠㅠ
/////////////////////////////////////////////////////////////////////////////////
typedef struct State{
    float up;
    float down;
    float left;
    float right;
    float value;

}State;

State S[ROW][COL];
void clear_S();

void RL();
void print_S();
void print_U();

int random_num(int n); // 0 ~ n-1 사이의 난수 return

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
    }

    fclose(f);

    int start[2] = {1,1};

    push(start); // 1,1 에서 시작
    printf("start: %d,%d\n", start[0],start[1]);
//
    clear_S();
    print_S();
    int count_RL;
    //for(count_RL=0; count_RL<9; count_RL++)
    {
        RL();
        print_S();
        print_U();
    }
    


    return 0;
}
///////////////////////////////////////////////////////////////////////
int IsEnd()
{
    if(cp[top][0] == (ROW-2) && cp[top][1] == (COL-2))
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


void RL() // 강화학습 1회
{
    int curr[2], next[2], dir; // curr - 현재 좌표 저장, next - 다음 좌표 저장, dir - 방향 지정
    float temp;
//value 가 높은 액션 찾기

    while(1)
    {    
        //// 현재 state의 up, down, left, right의 값
        curr[0] = cp[top][0];
        curr[1] = cp[top][1];

        //state S[ROW][COL] 안의 값 비교
        temp = S[curr[0]][curr[1]].up;
        dir = 0;

        if(temp < S[curr[0]][curr[1]].down)
        {
            dir = 1;
            temp = S[curr[0]][curr[1]].down;
        }

        if(temp < S[curr[0]][curr[1]].left)
        {
            dir = 2;
            temp = S[curr[0]][curr[1]].left;
        }

        if(temp < S[curr[0]][curr[1]].right)
        {
            dir = 3;
            temp = S[curr[0]][curr[1]].right;
        }

        if(dir == 0) //up
        {
            // 미로 밖으로 떨어질 경우
            if(curr[0] == 0)
            {
                S[curr[0]][curr[1]].up -= 100;

            }
            //목표 값에 도달했을 경우
            else if(curr[0]-1 == (ROW-2) && curr[1] == (COL-2))
            {
                S[curr[0]][curr[1]].up =  S[curr[0]-1][curr[1]].value * 0.9;

            }
            
            else
            {
                // 다음 좌표의 maze 값 따라 value 변화
                if(maze[curr[0]-1][curr[1]] == '1')
                {
                    S[curr[0]-1][curr[1]].value -=10;
                }

                //현재 좌표 S.up 에 다음 좌표 S.value*0.9 더하기 -> 함수화 해보기
                S[curr[0]][curr[1]].up =  S[curr[0]-1][curr[1]].value * 0.9;
                next[0]= curr[0]-1;
                next[1]= curr[1];
                push(next);
            }
        }

        else if(dir == 1) //down
        {
            // 미로 밖으로 떨어질 경우
            if(curr[0] == COL-1)
            {
                S[curr[0]][curr[1]].down -= 100;

            }
            //목표 값에 도달했을 경우
            else if(curr[0]+1 == (ROW-2) && curr[1] == (COL-2))
            {
                S[curr[0]][curr[1]].down =  S[curr[0]+1][curr[1]].value * 0.9;

            }

            else
            {
                // 다음 좌표의 maze 값 따라 value 변화
                if(maze[curr[0]+1][curr[1]] == '1')
                {
                    S[curr[0]+1][curr[1]].value -=10;
                }

                //현재 좌표 S.down 에 다음 좌표 S.value*0.9 더하기
                S[curr[0]][curr[1]].down =  S[curr[0]+1][curr[1]].value * 0.9;
                next[0]= curr[0]+1;
                next[1]= curr[1];
                push(next);
            }
        }

        else if(dir == 2) //left
        {
            // 미로 밖으로 떨어질 경우
            if(curr[1] == 0)
            {
                S[curr[0]][curr[1]].left -= 100;
            }
            //목표 값에 도달했을 경우
            else if(curr[0] == (ROW-2) && curr[1]-1 == (COL-2))
            {
                S[curr[0]][curr[1]].left =  S[curr[0]][curr[1]-1].value * 0.9;
            }

            else
            {
                // 다음 좌표의 maze 값 따라 value 변화
                if(maze[curr[0]][curr[1]-1] == '1')
                {
                    S[curr[0]][curr[1]-1].value -=10;
                }

                //현재 좌표 S.left 에 다음 좌표 S.value*0.9 더하기
                S[curr[0]][curr[1]].left =  S[curr[0]][curr[1]-1].value * 0.9;
                next[0]= curr[0];
                next[1]= curr[1]-1;
                push(next);
            }
        }

        else if(dir == 3) //right
        {
            // 미로 밖으로 떨어질 경우
            if(curr[1] == COL-1)
            {
                S[curr[0]][curr[1]].right -= 100;
            }
            //목표 값에 도달했을 경우
            else if(curr[0] == (ROW-2) && curr[1]+1 == (COL-2))
            {
                S[curr[0]][curr[1]].right =  S[curr[0]][curr[1]+1].value * 0.9;
            }

            else
            {
                // 다음 좌표의 maze 값 따라 value 변화
                if(maze[curr[0]][curr[1]+1] == '1')
                {
                    S[curr[0]][curr[1]+1].value -=10;
                }
                //현재 좌표 S.right 에 다음 좌표 S.value*0.9 더하기
                S[curr[0]][curr[1]].right =  S[curr[0]][curr[1]+1].value * 0.9;
                next[0]= curr[0];
                next[1]= curr[1]+1;
                push(next);
            }
        }
    }
    //액션 하면서 value 값 수정 
}

int random_num(int n)
{
    srand(time(NULL));

    return rand() % n;
}

void print_S()
{
    printf("\nRL-value\n");
    printf("=================================\n");
    int i,j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            printf("%8.1f  ", S[i][j].value);
        }
        printf("\n");
    }
    printf("=================================");
}

void clear_S()
{
    int x,y;
    for(x=0; x<ROW; x++)
    {
        for(y=0; y<COL; y++)
        {
            memset(&S[x][y],0, sizeof(struct State));
        }
    }
    
    //a,b의 State는 value를 설정한다

    S[ROW-2][COL-2].value = 100;
}

void print_U()
{
    printf("\nRL-up\n");
    printf("=================================\n");
    int i,j;
    for(i=0; i<ROW; i++)
    {
        for(j=0; j<COL; j++)
        {
            printf("%8.1f  ", S[i][j].up);
        }
        printf("\n");
    }
    printf("=================================");
}