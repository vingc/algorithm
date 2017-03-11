#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct edge
{
    int      src;    // one vertie of edge
    int      dst;    // one vertie of edge
    int      weight; // weight of edge
    int      used;   // denoting, used in result graph;
}EDGE;

typedef struct graph 
{
    int      V;      // max count of verties
    int      E;      // max count of edges
    EDGE *   edges;  // array of edges, length is E
}GRAPH;

typedef struct subset
{
    int      parent;
    int      rank;
}SUBSET;

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
    
    graph->V = V;
    graph->E = E;
    
    graph->edges = (EDGE *)malloc( sizeof( EDGE ) * E );
    if( graph->edges == NULL )
    {
        //log: memory err
        printf( "createGraph err\n" );
        free( graph );
        return NULL;
    }
    
    memset( graph->edges, 0x0, sizeof( EDGE ) * E );
    return graph;
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
        
    graph->edges[ idx ].src     = src;
    graph->edges[ idx ].dst     = dst;
    graph->edges[ idx ].weight  = weight;
    
    return;
}

int compare( EDGE * edgeS, EDGE * edgeD )
{
    return edgeS->weight - edgeD->weight;
}

void swap( EDGE * edgeS, EDGE * edgeD )
{
    EDGE   temp;
    
    temp   = *edgeS;
    *edgeS = *edgeD;
    *edgeD = temp;
}

void quikSort( EDGE * edges, int begin, int end )
{
    int i = begin - 1;
    int j = begin;
    
    int idx = end;
    
    if( edges == NULL || begin >= end )
    {
        return;
    }
    
    //idx = (begin + end)/2; //get a index, it's value to seperate 
    
    while( j < end )
    {
        if( edges[ j ].weight <= edges[ idx ].weight )
        {
            if( ++i != j )
            {
                swap( &edges[ i ], &edges[ j ] );
            }
        }
        
        j++;
    }
    
    swap( &edges[ ++i ], &edges[ idx ] );
    
    quikSort( edges, begin, i - 1 );
    quikSort( edges, i + 1, end );
    return;
}

int find( SUBSET * subset, int i )
{
    //path compression
    if( subset[i].parent != i )
    {
        subset[i].parent = find( subset, subset[i].parent );
    }
    
    return subset[i].parent;
}

void unionSet( SUBSET * subset, int x, int y )
{
    //rank algorithm can optimize this place.
    if( subset[x].rank < subset[y].rank )
    {
        subset[x].parent = y;
    }
    else if( subset[x].rank > subset[y].rank )
    {
        subset[y].parent = x;
    }
    else
    {
        subset[y].parent = x;
        subset[x].rank++;
    }
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
    for(; i < graph->E; i++ )
    {
        if( graph->edges[ i ].used )
        {
            printf( "%10d  %5d---%d\n", graph->edges[i].weight,
                   graph->edges[i].src, graph->edges[i].dst );
        }
    }
}

void kruskalMST( GRAPH * graph )
{
    SUBSET * subset;
    int i,j;
    int srcSet, dstSet;
    
    if( graph == NULL )
    {
        return;
    }
    
    subset = (SUBSET *)malloc( sizeof( SUBSET ) * graph->V );
    if( subset == NULL )
    {
        return;
    }
    
    for( i = 0; i < graph->V; i++ )
    {
        subset[ i ].parent = i; //signlton set, representative is itself
        subset[ i ].rank = 0;
    }
    
    //asc order
    quikSort( graph->edges, 0, graph->E - 1 );
    
    j = 0; //the count of accepted edges.
    for( i = 0; i < graph->E; i++ )
    {
        srcSet = find( subset, graph->edges[ i ].src );
        dstSet = find( subset, graph->edges[ i ].dst );
        
        //equal,denote circle
        if( srcSet == dstSet )
        {
            continue;
        }
        
        graph->edges[ i ].used = 1; //use this edge
        
        if( ++j == graph->V - 1 )
        {
            break; //get the result
        }
        
        unionSet( subset, srcSet, dstSet );
    }
    
    printSolution( graph );
    free( subset );
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
    
    kruskalMST( graph );
    
    free( graph->edges );
    free( graph );
}