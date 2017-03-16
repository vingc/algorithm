#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFIT 100000

typedef struct graph 
{
    int      V;      // max count of verties
    int      E;      // max count of edges
    int *    edges;  // array of edges, 2D array, length is V*V, value is weight 0 mean no edge
    int *    mstSet;  // verties in MST; length is V, 
    int *    key;     // value of veries; length is V;
    int *    parent;  // store the parent in mst, length is V
}GRAPH;


GRAPH * createGraph( int V, int E )
{
    if( V <= 0 || E <= 0 )
    {
        return NULL;
    }
    
    GRAPH * graph = (GRAPH *)malloc( sizeof( GRAPH ) );
    if( graph == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        return NULL;
    }
    memset( graph, 0x0, sizeof( GRAPH ) );
    
    graph->V = V;
    graph->E = E;
    
    graph->edges = (int *)malloc( sizeof( int ) * V * V );
    if( graph->edges == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->edges, 0x0, sizeof( int ) * V * V );
    
    graph->mstSet = (int *)malloc( sizeof( int ) * V );
    if( graph->mstSet == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->mstSet, 0x0, sizeof( int ) * V );
    
    graph->key = (int *)malloc( sizeof( int ) * V );
    if( graph->key == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->key, 0x0, sizeof( int ) * V );
    
    graph->parent = (int *)malloc( sizeof( int ) * V );
    if( graph->parent == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->parent, 0x0, sizeof( int ) * V );
    
    return graph;
    
err:
    if( graph->edges )
        free( graph->edges );
    if( graph->mstSet )
        free( graph->mstSet );
    if( graph->key )
        free( graph->key );
    if( graph->parent )
        free( graph->parent );
        
    free( graph );
    return NULL;
}

void freeGraph( GRAPH * graph )
{
    if ( graph == NULL )
        return;
        
    if( graph->edges )
        free( graph->edges );
    if( graph->mstSet )
        free( graph->mstSet );
    if( graph->key )
        free( graph->key );
    if( graph->parent )
        free( graph->parent );
        
    free( graph );
    return;
}

void initEdge( GRAPH * graph, int idx, int src, int dst, int weight )
{
    if( graph == NULL || idx < 0 || idx >= graph->E ||
        src < 0 || src >= graph->V ||
        dst < 0 || dst >= graph->V ||
        src == dst ||
        weight < 0 )
    {
        printf( "initEdge err\n" );
        return;
    }
    
    //convert to matrix
    graph->edges[src * graph->V + dst] = weight;
    graph->edges[dst * graph->V + src] = weight;
    
    return;
}

void printSolution( GRAPH * graph )
{
    int i = 0;
    if( graph == NULL )
    {
        printf( "printSolution err\n" );
        return;
    }
    
    printf( "%10s  %10s\n", "weight", "vietes" );
    for(; i < graph->V; i++ )
    {
        if( graph->parent[ i ] != -1 )
        {
            printf( "%10d  %5d---%d\n", graph->key[i],
                   graph->parent[ i ], i );
        }
    }
}

int minChoose( GRAPH * graph )
{
    int i, idx = -1, min = INFIT;
    
    /* select the verties not in MST,but have the minimum key */
    for( i = 0; i < graph->V; i++ )
    {
        if( graph->mstSet[ i ] == 0 &&
            graph->key[ i ] < min )
        {
            min = graph->key[ i ];
            idx = i;
        }
    }
    
    return idx;
}

void primMST( GRAPH * graph )
{
    int i,j,u;
    
    //init
    for( i = 0; i < graph->V; i++ )
    {
        graph->mstSet[ i ] = 0; //keep track of edges in mstTree.
        graph->key[ i ] = INFIT; 
        graph->parent[ i ] = -1; // strore the parent of verties in MST, 
    }
    
    //begin from 0;
    graph->key[7] = 0; //begin from 7 or 0 get two mst,same weight sums,
    
    //get the minimum of key in left verties, like dijkstra SPT
    for( i = 0; i < graph->V; i++ )
    {
        u = minChoose( graph );
        graph->mstSet[ u ] = 1;
        
        for( j = 0; j < graph->V; j++ )
        {
            //update the key of adjacent verties to u
            if( graph->edges[u * graph->V + j] != 0 &&
                graph->mstSet[ j ] == 0 &&
                graph->edges[u * graph->V + j] < graph->key[ j ] )
            {
                graph->key[ j ] = graph->edges[u * graph->V + j];
                graph->parent[ j ] = u;
            }
        }
    }
    
    printSolution( graph );
}

void main( void )
{
    GRAPH * graph = createGraph( 9, 14 );
    initEdge( graph, 0, 8, 2, 2 );
    initEdge( graph, 1, 6, 5, 2 );
    initEdge( graph, 2, 7, 6, 1 );
    initEdge( graph, 3, 0, 1, 4 );
    initEdge( graph, 4, 2, 5, 4 );
    initEdge( graph, 5, 8, 6, 6 );
    initEdge( graph, 6, 2, 3, 7 );
    initEdge( graph, 7, 7, 8, 7 );
    initEdge( graph, 8, 0, 7, 8 );
    initEdge( graph, 9, 1, 2, 8 );
    initEdge( graph, 10, 3, 5, 14 );
    initEdge( graph, 11, 5, 4, 10 );
    initEdge( graph, 12, 1, 7, 11 );
    initEdge( graph, 13, 3, 4, 9 );
    
    primMST( graph );
    
    freeGraph( graph );
}