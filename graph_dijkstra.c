#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX   20 //the max no of vertex
#define FALSE 0
#define TRUE  1

int minChoose( int * distance, int V, char * found )
{
    int min = 0x7fffffff;
    int index = 0;
    int i;
    
    for( i = 0; i < V; i++ )
    {
        if( distance[ i ] <= min && found[ i ] == FALSE )
        {
            min = distance[ i ];
            index = i;
        }
    }
    
    return index;
}

void printSolution( int * distance, int V )
{
    int i = 0;
    
    for( i; i < V - 1; i++ )
    {
        printf( "%d ", distance[ i ] );
    }
    printf( "%d\n", distance[ i ] );
}

/* The function prints V space separated integers where 
    the ith integer denote the shortest distance of ith vertex
    from source vertex */
void dijkstra(int graph[MAX][MAX], int s,int V)
{
    int i,j,u;
    char*  found = (char*)malloc( V * sizeof( char ) );
    if( found == NULL )
    {
        return;
    }
    
    int * distance = (int*)malloc( V * sizeof( int ) );
    if( distance == NULL )
    {
        free( found );
        return;
    }
    
    for( i = 0; i < V; i++ )
    {
        found[ i ] = FALSE;
        distance[ i ] = 10000;
    }
    
    distance[ s ] = 0;
    
    for( i = 0; i < V - 1; i++ )
    {
        u = minChoose( distance, V, found );
        
        found[ u ] = TRUE;
        
        for( j = 0; j < V; j++ )
        {
            //printf("din u:%d, din j:%d,",distance[u],distance[j]);
            if( distance[ u ] != 10000 && found[ j ] == FALSE &&
            	  graph[u][j] && (graph[u][j] + distance[ u ] < distance[ j ]) )
            {
                distance[ j ] = distance[ u ] + graph[ u ][ j ];  
                //printf( "din:%d\n",distance[ j ] );
            }
        }
    }
   //Your code here
   printSolution( distance, V );
   
   free( distance );
   free( found );
}

void main( void )
{
    int graph[MAX][MAX];
    int caseCnt = 0;
    int V = 0, S = 0;
    int i = 0, j = 0, k = 0;
     
    scanf( "%d\n", &caseCnt );
    
    for( k = 0; k < caseCnt; k++ )
    {
        scanf( "%d\n", &V );
        
        for( i = 0; i < V; i++ )
        for( j = 0; j < V; j++ )
            scanf("%d", &graph[i][j] );
            //printf("%d ", graph[i][j]);
             
        scanf( "%d\n", &S );
        
        
        dijkstra( graph, S, V );
    }
}

/*input:
2
2
0 25 25 0
0
3
0 1 43 1 0 6 43 6 0
2
*/