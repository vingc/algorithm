#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  bool char
#define  true 1
#define  false 0
#define  ALPHABET_SIZE 26

#define  char_int(c) ( (int)(c) - (int)'a')

typedef struct trie_node
{
    struct trie_node * child[ ALPHABET_SIZE ];
    bool isLeaf;
}trie_node_t;

static trie_node_t  root={{NULL},false};

void insert( trie_node_t * root, char * str )
{
    int i;
    int idx;
    
    trie_node_t * cur = root;
    
    for( i = 0; ; i++ )
    {
        if( str[i] == '\0' )
            break;
            
        idx = char_int( str[i] );
        if( cur->child[idx] == NULL )
        {
            trie_node_t * tmp = (trie_node_t *)malloc( sizeof( trie_node_t ) );
            cur->child[idx] = tmp;
        }
        
        cur = cur->child[idx];
    }
    
    cur->isLeaf = true;
}

bool search( trie_node_t * root, char * str )
{
    if( root->isLeaf == true && *str == '\0' )
       return true;
       
    int idx = char_int( *str );
   
    if( root->child[idx] != NULL )
    {
        return search( root->child[idx], str+1 );
    }
    
    return false;//can't match current char.
}

int main() {
	//code
	int  T;
	int  strCnt;
	int i,j;
	char  word[256];
	
	scanf( "%d\n", &T );
	for( i = 0; i < T; i++ )
	{
	    scanf( "%d\n", &strCnt );
	    
	    for( j = 0; j < strCnt; j++ )
	    {
	        memset( word, 0x0, sizeof( word ) );
	        scanf( "%s ", word );
	        insert( &root, word );
	    }
	    
	    memset( word, 0x0, sizeof( word ) );
	    scanf("%s\n", word );
	    
	    printf("%s: %d\n", word, (int)search( &root, word ) );
	}
	
	return 0;
}