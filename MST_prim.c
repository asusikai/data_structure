#include <stdio.h>

#include <stdlib.h>

#include <math.h>
#include <time.h>
#include <string.h> // memset

#define MAX_VERTEX 14
#define MAX_QUEUE 15
#define INF 1000L

typedef struct EDGE {

    int n;

    int** key;

}Edge;


Edge* Init_Edge(int max_vertex); 
void Init_Graph(Edge* e, int n);
void Insert_Edge(Edge* e, int v1, int v2, int weight); 
int selected[MAX_VERTEX];
int dist[MAX_VERTEX];
int get_min_vertex(int n);
void prim(Edge* e, int s, int n);
int selected_gm[MAX_VERTEX];

int main(void) {

    Edge* e = Init_Edge(MAX_VERTEX);

    int i,j;
    
    for(i=0; i<MAX_VERTEX; i++)
    {
        for(j=0; j<MAX_VERTEX; j++)
        {
            Insert_Edge(e,i,j,INF);
        }
    }
    
    for(i=0; i<MAX_VERTEX; i++)
    {
        for(j=0; j<MAX_VERTEX; j++)
        {
            if(i=j)
            {
                Insert_Edge(e,i,i,0);
            }
        }
    }

    Insert_Edge(e,0,1,2);
    Insert_Edge(e,0,2,4);
    Insert_Edge(e,0,3,10);
    Insert_Edge(e,1,4,8);
    Insert_Edge(e,2,3,15);
    Insert_Edge(e,2,5,3);
    Insert_Edge(e,2,6,13);
    Insert_Edge(e,3,4,18);
    Insert_Edge(e,3,6,6);
    Insert_Edge(e,4,7,11);
    Insert_Edge(e,5,8,20);
    Insert_Edge(e,6,9,5);
    Insert_Edge(e,6,11,14);
    Insert_Edge(e,7,9,16);
    Insert_Edge(e,7,10,12);
    Insert_Edge(e,8,11,11);
    Insert_Edge(e,9,12,17);
    Insert_Edge(e,9,13,22);
    Insert_Edge(e,10,13,1);
    Insert_Edge(e,11,12,19);
    Insert_Edge(e,12,13,24);

    prim(e, 0, MAX_VERTEX);
 

    return 0;

}

int get_min_vertex(int n) {

    // 선택된 애들이 아닌 애들 중에 가장 dist가 작은 애를 반환한다.

    int v, i;

 

    v = -1;

 

    for (i = 0; i < n; i++)

        if (!selected[i]) { // 그래프에 선택되지 않은 정점을 발견할 때까지 반복합니다.

            v = i;

            break;

        }

 

    for (i = 0; i < n; i++)

        if (!selected[i] && (dist[i] < dist[v]))

            // 선택되지 않은 간선 중에 더 작은 간선이 발견될때까지 반복한다.

            v = i;

 

    return v;

}


void prim(Edge* e, int s, int n) {

    

    int i, u, v;

 

    for (u = 0; u < n; u++) {

        dist[u] = INF;

        selected[u] = 0;

    }

 

    dist[s] = 0;

 

    for (i = 0; i < n; i++) {

        u = get_min_vertex(n); 

 

        selected[u] = 1;    

 

        if (dist[u] == INF) 

            return;

 

        printf("%d ", u+1);

 

        for (v = 0; v < n; v++)

            if (e->key[u][v] != INF) 

                if (!selected[v] && e->key[u][v] < dist[v]) {

                    

                    dist[v] = e->key[u][v]; 

                }

    }

 

    printf("\n\nShow each weight from start vertex to the others\n");

 

    for (i = 0; i < n; i++) {

        printf("dist[%d] = %d\n", i+1, dist[i]);

    }

 

    printf("\n\n");

}



 

 

Edge* Init_Edge(int max_vertex) {// MAX_VERTEX*MAX_VERTEX 크기의 key 행렬 생성

    Edge* e;

 

    e = (Edge*)malloc(sizeof(Edge));

 

    e->n = 0;

    e->key = (int**)malloc(sizeof(int*) * max_vertex);

 

    for (int i = 0; i < max_vertex; i++) {

 

        e->key[i] = (int*)malloc(sizeof(int) * max_vertex);

 

        memset(e->key[i], 0, sizeof(int) * max_vertex);



    }

 

    return e;

}


void Insert_Edge(Edge* e, int v1, int v2, int weight) {

    

    e->key[v1][v2] = weight;

    e->key[v2][v1] = weight;


}