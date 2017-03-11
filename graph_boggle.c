#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M  3 
#define N  3 
#define MAX_WORDS  10

char * dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};

int wordsCnt = sizeof( dictionary ) / sizeof( char * );

char string[ M * N + 1 ];
int  strPoint = 0;
int visited[M][N];
//int result[ MAX_WORDS ] = { 0 }; // 1 denote that found the word in dictionary

int isWord( char * string )
{
    int i = 0;
    for( i; i < wordsCnt; i++ )
    {
        if( strcmp( string, dictionary[i] ) == 0 )
            return 1;
    }
    
    return 0;
}

void searchUtil( int graph[M][N], int row, int col )
{
    int i,j;
    string[strPoint++] = graph[row][col];
    visited[row][col] = 1;
    
    if ( isWord(string) )
    {
        //if( result)
        printf("%s\n",string);
    }
    
    /* traverse adjacent verties */
    for( i = row-1; i<=row+1 && i<M; i++ )
    for( j = col-1; j<=col+1 && j<N; j++ )
    if( i >= 0 && j >= 0 && visited[i][j] == 0 )
    {
        searchUtil( graph, i, j );
    }
    
    /* clear the visited flat,so we can use it again */
    visited[row][col] = 0;
    string[--strPoint] = '\0';
}


//dfs
search( int graph[M][N] )
{
    int i,j;  
    
    /* select each cell as start vertex, perform DFS */
    for( i = 0; i < M; i++ )
    for( j = 0; j < N; j++ )
    {
        memset( string, 0x0, sizeof( string ) );
        memset( visited, 0x0, sizeof( visited ) );
        strPoint = 0;
        
        searchUtil( graph, i, j );
    }
}

/*Input: dictionary[] = {"GEEKS", "FOR", "QUIZ", "GO"};
       boggle[][]   = {{'G','I','Z'},
                       {'U','E','K'},
                       {'Q','S','E'}};
      isWord(str): returns true if str is present in dictionary
                   else false.

Output:  Following words of dictionary are present
         GEEKS
         QUIZ*/
void main( void )
{
    int boggle[M][N] = {{'G','I','Z'},
                        {'U','E','K'},
                        {'Q','S','E'}};
    
    search( boggle );
    
}