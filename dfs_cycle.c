#include <stdio.h>
#include <stdlib.h>


int graph_1[12][12] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,0,0,0,0},
    {0,1,0,1,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,1,0,0,0},
    {0,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,1,0,1},
    {0,0,0,0,0,0,0,0,1,0,1,0}
};

int graph_2[12][12] = {
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,0,0,1,0,0,0,0,0,0},
    {0,1,0,1,0,0,0,0,0,0,0,0},
    {0,0,1,0,1,0,0,0,0,0,0,0},
    {0,0,0,1,0,1,0,0,1,0,0,0},
    {0,1,0,0,1,0,1,0,0,0,0,0},
    {0,0,0,0,0,1,0,1,0,1,0,0},
    {0,0,0,0,0,0,1,0,1,0,0,0},
    {0,0,0,0,1,0,0,1,0,0,0,1},
    {0,0,0,0,0,0,1,0,0,0,1,0},
    {0,0,0,0,0,0,0,0,0,1,0,1},
    {0,0,0,0,0,0,0,0,1,0,1,0}
};

int visit[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

void clear_visit();

int length = 0;
int source;
void find_cycle(int v, int graph[][12], int visit[]);

int main()
{
    source =1;
    printf("find cycle in 1st graph.\n");
    find_cycle(1, graph_1, visit);
    clear_visit();
    
    length = 0;
    printf("\n");
    printf("find cycle in 2nd graph.\n");
    find_cycle(1, graph_2, visit);
}

void clear_visit()
{
    int i;
    for(i=0; i<12; i++)
    {
        visit[i] = 0;
    }
}

void find_cycle(int v, int graph[][12], int visit[])
{
    int i;
    if(visit[v]==0){
        printf("%3d", v);
        visit[v]++;
    }
    for (i=1; i<12; i++)
    {
        if((graph[v][i] != 0) && (visit[i] == 0))
        {
            length++;
            find_cycle(i, graph, visit);
            continue;
        }

        else if((graph[v][i] != 0) && (i == source) && length > 3)
        {
            printf("\nfound cycle!\n");
            break;
        }
    }
    length--;
}
