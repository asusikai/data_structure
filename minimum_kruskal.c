#include <stdio.h>

#define MAX_VER     15
#define MAX_EDGE    30

/*
1. make n nodes & routes
2. add route with minimum cost
3. check if it makes cycle, and if it does, reject route
4. when route quantity is n-1 end
*/

typedef struct edge{
    int s,d;
    int w;
}EDGE;

struct vertices{
    int p;
    int rank;
}vt[MAX_VER];

EDGE e[MAX_EDGE];

void insert_info(int, int, int, int);
void mst_kruskal(int, int);
void make_set(int);
void connect(int, int);
int find_set(int);
void sort_edge(int);
void max_heapify(int, int);
void build_max_heap(int);

int main()
{
    int nv, ne;

    // input the number of vertices and edges.
    nv = 14;
    ne = 21;

    insert_info(0,1,2,2);
    insert_info(1,1,3,4);
    insert_info(2,1,4,10);
    insert_info(3,2,5,8);
    insert_info(4,3,4,15);
    insert_info(5,3,6,3);
    insert_info(6,3,7,13);
    insert_info(7,4,5,18);
    insert_info(8,4,7,6);
    insert_info(9,5,8,11);
    insert_info(10,6,9,20);
    insert_info(11,7,10,5);
    insert_info(12,7,12,14);
    insert_info(13,8,10,16);
    insert_info(14,8,11,12);
    insert_info(15,9,12,11);
    insert_info(16,10,13,17);
    insert_info(17,10,14,22);
    insert_info(18,11,14,1);
    insert_info(19,12,13,19);
    insert_info(20,13,14,24);

    mst_kruskal( nv, ne);
    

    return 0;

}

void insert_info(int i, int s, int d, int w)
{
    e[i].s = s;
    e[i].d = d;
    e[i].w = w;
}

/*
    make_set()
    create a new set whose only member is itself.
*/
void make_set( int v)
{
    vt[v].p     = v;
    vt[v].rank  = 0;
}

/*
    find_set()
    returns a pointer to the representative of the set.
*/
int find_set( int v)
{
    if( vt[v].p != v)
    {
        vt[v].p = find_set( vt[v].p);
    }
   
    return vt[v].p;
}

/*
    connect()
    unites the dynamic sets that contain two elements.
*/
void connect( int v, int u)
{
    v   = find_set( v);
    u   = find_set( u);

    // compare V with U.
    if( vt[v].rank > vt[u].rank)
    {
        vt[u].p = v;
    }
    else
    {
        vt[v].p = u;

        // if v has the equal number of vertices with u.
        if( vt[v].rank == vt[u].rank)
        {
            vt[u].rank = vt[u].rank + 1;
        }
    }
}

/*
    mst_kruskal()
    it uses disjoint-set and finds a safe edge.
*/
void mst_kruskal( int nv, int ne)
{
    int i;
    int total   = 0;

    for( i = 0 ; i < nv ; i ++)
    {
        // create a new set whose only member is itself.
        make_set(i);
    }

    // sort the edges.
    sort_edge( ne);

    for( i = 0  ; i < ne ; i ++)
    {
        // examine whether two representative is not similar each other.
        if( find_set( e[i].s) != find_set( e[i].d))
        {
            // unites the dynamic sets that contain two elements.
            connect( e[i].s, e[i].d);

            total = total + e[i].w;

            printf("(%d, %d), total weight : %d\n", e[i].s, e[i].d, total);
        }
    }
}

/*
    sort_edge()
    sort the edges by heap sort
*/
void sort_edge( int ne)
{
    EDGE temp;
    int i;

    build_max_heap( --ne);

    for( i = ne ; i > 0 ; i --)
    {
        temp    = e[i];
        e[i]    = e[0];
        e[0]    = temp;

        max_heapify( 0, i);
    }
}

/*
    max_heapify()
    maintain the characteristic of the heap.
*/
void max_heapify( int index, int size)
{
    EDGE temp;
    int left    = index * 2 + 1;
    int right   = index * 2 + 2;
    int largest = index;

    if( left < size && e[left].w > e[largest].w)
    {
        largest = left;
    }
   
    if( right < size && e[right].w > e[largest].w)
    {
        largest = right;
    }

    if( largest != index)
    {
        temp        = e[largest];
        e[largest]  = e[index];
        e[index]    = temp;

        max_heapify( largest, size);
    }
}

/*
    build_max_heap()
    make the max heap
*/
void build_max_heap( int ne)
{
    int i;

    for(i = ne/2 ; i >= 0 ; i--)
    {
        max_heapify( i, ne);
    }
}