#include <stdio.h>

/* graph is two dimension array, each length is n */
void bfs( int * graph, int start, int n, char * visited )
{
    int i = 0, j = 0;
    int *  queue; //queue is on dimension array, length is n
    int begin = 0, end = 0; //point to the queue.
    int cur;
    
    if( graph == 0 || n <= 0 || start >= n || start < 0 )
    {
        //parameter error
       return;
    }
    
    queue = (int *)malloc( n * sizeof( int ) );
    if( queue == 0 )
    {
        //memory error
        return;
    }
    
    memset( queue, 0x0, sizeof( int ) * n );
    
    visited[ start ] = 1; //1 represent true 
    queue[0] = start; //add to the queue;
    begin = 0;// current position of valid data.
    end = (0+1)%n; // current position of invalid data.
    
    while( begin != end )
    {
        cur = queue[ begin ];
        begin = (begin + 1) % n;
        
        printf("%d ", cur);
        
        for( i = 0; i < n; i++ )
        {
            if( graph[ cur * n + i ] == 1 && visited[ i ] == 0 )
            {
                visited[ i ] = 1;
                queue[ end ] = i;
                end = ( end + 1 ) % n;
                if( end == begin )
                {
                    //error
                    free( queue );
                    return;
                }
            }
            
        }
    }
    
    free( queue );
    return;
    
    
    
}

int main() {
	//code
	int graph[4][4] = { {0,0,1,1},{ 1, 0, 0, 1 },{ 0, 1, 1, 0},{1,1,1,1} };
	int n = 4;
	#if 1
	bfs( (int *)graph, 3, 4, visited );
	#else
  {
    char visited[4] = {0};
  	//All the vertices may not be reachable from a given vertex 
  	int i = 0;
  	for( i; i < 4; i++ )
  	{
  		bfs( (int*)graph, i, 4, visited );
  	}
  }
	#endif
	return 0;
}