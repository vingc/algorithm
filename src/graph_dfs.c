#include <stdio.h>

/* graph : two dimension array, each length is n 
  visited: one dimension array, length is n */
void dfs( int *graph, int start, int n, char * visited )
{
    int i = 0;
    
    //memset( visited, 0x0, sizeof( char ) * n );
    
    if( start < 0 || start >= n || n <= 0 || graph == 0 || visited == 0)
    {
        return;
    }
    
    /* begin from start */
    visited[ start ] = 1; // 1 denoting true 
    printf("%d ", start );
    
    for( i = 0; i < n; i++ )
    {
        if( graph[ start * n + i ] == 1 
         && visited[ i ] == 0 )
        {
            //edge n--i, not visited
            dfs( graph, i, n, visited );
        }
    }
    return;
}

void main( void )
{
    int graph[4][4] = {{0,0,1,1},{1,1,0,0},{1,0,0,1},{0,1,1,0}};
    char visited[4] = {0};
    #if 1
    dfs( (int*)graph, 3, 4, visited );
    #else
    {
    	//All the vertices may not be reachable from a given vertex 
    	int i = 0;
    	for( i; i < 4; i++ )
    	{
    		dfs( (int*)graph, i, 4, visited );
    	}
    }
    #endif
}