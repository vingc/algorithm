#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFIT 100000

/*
only serve Directed Acyclic Graph (DAG);
notice:
1. the first vertex picked,it's in-degree must be 0,a vertex with no in-coming edges
*/
typedef struct graph 
{
    int      V;      // max count of verties
    int      E;      // max count of edges
    int *    edges;  // array of edges, 2D array, length is V*V, value is weight 0 mean no edge
    int *    visited;  // verties visited; length is V, 
    int *    stack;  // stack to save the verties visited; length is V
    int      stackIdx;
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
    
    graph->visited = (int *)malloc( sizeof( int ) * V );
    if( graph->visited == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->visited, 0x0, sizeof( int ) * V );
    
    graph->stack = (int *)malloc( sizeof( int ) * V );
    if( graph->stack == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        goto err;
    }
    memset( graph->stack, 0x0, sizeof( int ) * V );
    
    return graph;
    
err:
    if( graph->edges )
        free( graph->edges );
    if( graph->visited )
        free( graph->visited );
    if( graph->stack )
        free( graph->stack );
        
    free( graph );
    return NULL;
}

void freeGraph( GRAPH * graph )
{
    if ( graph == NULL )
        return;
        
    if( graph->edges )
        free( graph->edges );
    if( graph->visited )
        free( graph->visited );
    if( graph->stack )
        free( graph->stack );
        
    free( graph );
    return;
}

//directed acyclic graph; DAG, topological sorting
void initEdge( GRAPH * graph, int src, int dst )
{
    if( graph == NULL || 
        src < 0 || src >= graph->V ||
        dst < 0 || dst >= graph->V ||
        src == dst )
    {
        printf( "initEdge err\n" );
        return;
    }
    
    //convert to matrix，directed
    graph->edges[src * graph->V + dst] = 1;
    
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
    for( i = graph->V - 1; i >= 0; i-- )
    {
        if( graph->stack[i] != -1 )
        {
            printf( "%d ", graph->stack[i] );
        }
    }
}

void topologicalSortUtil( GRAPH * graph, int src )
{
    int dst = 0;
    
    graph->visited[src] = 1;
    
    //dfs
    for( dst = 0; dst < graph->V; dst++ )
    {
        //directed edge, if have edge from src to dst,then explore from dst
        if( graph->edges[src * graph->V + dst] != 0 &&
            graph->visited[dst] == 0 )
        {
            topologicalSortUtil( graph, dst );
        }
    }
    
    //after all children expored, push current vertex;
    graph->stack[ graph->stackIdx ] = src;
    graph->stackIdx++;
}

void topologicalSort( GRAPH * graph )
{
    int i,j,u;
    
    //init
    for( i = 0; i < graph->V; i++ )
    {
        graph->visited[ i ] = 0; //unvisited
        graph->stack[ i ] = -1;
    }
    
    graph->stackIdx = 0;
    
    
    //get the minimum of key in left verties, like dijkstra SPT
    for( i = 0; i < graph->V; i++ )
    {
        if( graph->visited[ i ] == 0 )
        {
            topologicalSortUtil( graph, i );
        }
    }
    
    printSolution( graph );
}

void main( void )
{
    GRAPH * graph = createGraph( 6, 6 );
    initEdge( graph, 5, 2 );
    initEdge( graph, 5, 0 );
    initEdge( graph, 2, 3 );
    initEdge( graph, 3, 1 );
    initEdge( graph, 4, 0 );
    initEdge( graph, 4, 1 );
    
    topologicalSort( graph );
    
    freeGraph( graph );
}