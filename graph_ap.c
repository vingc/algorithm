#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define bool  char 
#define true  1 
#define false 0 
#define MAX_CNT  20

#define min(a,b) (a>b?b:a)

typedef struct node
{
    struct node * next;
    int v;
}node_t;

typedef struct list 
{
    node_t * head; 
    int size;
}list_t;

typedef struct graph
{
    int      V;
    int      E;
    list_t * list; //array of list, adjacent verties of vertex
}graph_t;


graph_t * createGraph( int V, int E )
{
    if( V <= 0 || E <= 0 )
    {
        return NULL;
    }
    
    graph_t * graph = (graph_t *)malloc( sizeof( graph_t ) );
    if( graph == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        return NULL;
    }
    memset( graph, 0x0, sizeof( graph_t ) );
    
    graph->V = V;
    graph->E = E;
    
    graph->list = (list_t *)malloc( sizeof( list_t ) * V );
    if( graph->list == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->list, 0x0, sizeof( list_t ) * V );
    
    
    return graph;
    
err:
    if( graph->list )
        free( graph->list );
        
    free( graph );
    return NULL;
}

void freeGraph( graph_t * graph )
{
    int i = 0;
    node_t * tmp;
    
    if ( graph == NULL )
        return;
        
    
    if( graph->list )
    {
        for( i = 0; i < graph->V; i++ )
        {
            while(graph->list[i].head)
            {
                tmp = graph->list[i].head;
                graph->list[i].head = tmp->next;
                free(tmp);
            }
        }
        free( graph->list );
    }
        
    free( graph );
    return;
}

node_t * newNode( int v )
{
    node_t * node = (node_t *)malloc( sizeof( node_t ) );
    if( node == NULL )
        return NULL;
        
    node->next = NULL;
    node->v = v;
    return node;
}

void addEdge( graph_t * graph, int start, int end )
{
    node_t * tmp;
    
    tmp = newNode( end );
    tmp->next = graph->list[start].head;
    graph->list[start].head = tmp;
    
    tmp = newNode( start );
    tmp->next = graph->list[end].head;
    graph->list[end].head = tmp;
}


int parent[MAX_CNT];
int visited[MAX_CNT];
int disc[MAX_CNT];
int low[MAX_CNT];
int ap[MAX_CNT];
int time;

void apUtil( graph_t * graph, int u )
{
    node_t * node;
    int v;
    int child = 0;
    
    visited[u] = true;
    disc[u] = low[u] = ++time;
    
    for( node = graph->list[u].head; node != NULL; node = node->next )
    {
        v = node->v;
        if( visited[v] == false )
        {
            child++;
            parent[v] = u;
            apUtil( graph, v );
            
            /* if the subtree rooted with v, 
            has connect to an ancestor of u, 
            then low[v] will lower than low[u];
            low[u] compare will every low time of subtree, 
            to get the lowest, when return to upstack,
            then the low[parent[u]] will get the lowest time too */
            low[u] = min( low[u], low[v] );
            
            /* case 1: the root of DFS tree, 
            has more than one child, must be AP*/
            if( parent[u] == -1 && child > 1 )
            {
                ap[u] = true;
            }
            
            /* case 2: if the low[v] bigger than disc[u], 
            mean there isn't back edge from v to u */
            if( parent[u] != -1 && low[v] >= disc[u] )
            {
                ap[u] = true;
            }
        }
        else if( v != parent[u] )
        {
            /* if v has been visited by others, 
            low[v] must be less than low[u],
            v is the ancestor of u, updat the low[u] by disc[v] */
            low[u] = min( low[u], disc[v] );
        }
    }
}

void apProcess( graph_t * graph )
{
    int i = 0;
    
    for( i = 0; i < graph->V; i++ )
    {
        visited[i] = false;
        disc[i] = 0;
        low[i] = 0;
        ap[i] = false;
        parent[i] = -1;
    }
    
    for( i = 0; i < graph->V; i++ )
    {
        if( visited[i] == false )
            apUtil( graph, i );
    }
    
    for( i = 0; i< graph->V; i++ )
    {
        if( ap[i] == true )
            printf("%d ", i);
    }
}

void main( void )
{
    graph_t * graph = createGraph( 4, 3 );
    addEdge( graph, 0, 1 );
    addEdge( graph, 2, 1 );
    addEdge( graph, 2, 3 );
    
    apProcess( graph );
    
    freeGraph( graph );
}


