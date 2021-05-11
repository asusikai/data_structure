#include <stdio.h>
#include <stdlib.h>
#define qsize 10

int graph[12][12] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,0,0,0,0,0,0,0},
    {0,1,0,1,0,1,1,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,0,0,0,0},
    {0,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,1,1,0,0,0,1,0,1,0,0},
    {0,0,1,0,1,0,0,1,0,1,0,0},
    {0,0,0,0,0,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0},
    {0,0,0,0,0,1,0,0,1,0,1,1},
    {0,0,0,0,0,0,0,0,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,1,1,0},
};

int visit[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

int front =0;
int rear=0;
int q[qsize]={0};

int add_q(int v);
int delete_q();
void bfs(int v);

void dfs(int v);

int main()
{
    front = 0;
    rear = 0;
    int i = 0;
    for (i=1; i<12; i++)
    {
        visit[i] = 0;
    }

    printf("bfs route:\n");
    bfs(1);
    printf("\n");
    
    for (i=1; i<12; i++)
    {
        visit[i] = 0;
    }

    printf("dfs route:\n");
    dfs(1);
}

int insert_q(int v)
{
    q[++rear]=v;
}

int delete_q()
{
    if(front!=rear)
        return q[++front];
    else
        return 0;
}


void bfs(int v)
{
    int i;
    for (i=1; i<12; i++)
        visit[i] = 0;

    int u, j;

    insert_q(v);
    visit[v] = 1;
    u = delete_q();
    while (u != 0)
    {
        printf("%5d", u);
        for (j=1; j<12; j++){
            if ((graph[u][j] != 0) && (visit[j] == 0))
            {
                visit[j] = 1;
                insert_q(j);
            }
        }
        u = delete_q();
    }
}

void dfs(int v)
{
    int i;
    if(visit[v]==0){
        printf("%5d", v);
        visit[v]++;
    }
    for (i=1; i<12; i++)
        {
            if((graph[v][i] != 0) && (visit[i] == 0))
                {
                    dfs(i);
                }
        }
}