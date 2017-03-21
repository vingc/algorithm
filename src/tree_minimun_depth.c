/************************************************
* creator: vingc zhang
* time: 2017.03.21
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/find-minimum-depth-of-a-binary-tree/
Find Minimum Depth of a Binary Tree
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from root node down to the nearest leaf node.
*/

typedef struct node
{
    int v;
    struct node * left;
    struct node * right;
}node_t;



node_t * newNode( int v )
{
    node_t * tmp;
    tmp  = (node_t *)malloc( sizeof( node_t ) );
    if( tmp == NULL )
    {
        printf( "newNode() malloc(%d) fail\n", sizeof( node_t ) );
        return NULL;
    }

    tmp->v = v;
    tmp->left  = NULL;
    tmp->right = NULL;

    return tmp;
}


int min( int a, int b )
{
    if ( a < b )
        return a;
    else
        return b;
}

//Time complexity less than O(n);
void findMinDepth( node_t * root, int curDepth, int * minDepth )
{
    if( root == NULL )
    {
        *minDepth = min( curDepth, *minDepth );
        return;
    }

    curDepth++;

    //we want to find the minimum, so if curDepth reach the minDepth, we don't need to dive deeper.
    if( curDepth >= *minDepth
    || ( root->left == NULL && root->right == NULL ))
    {
        *minDepth = min( curDepth, *minDepth );
        return;
    }

    if( root->left )
        findMinDepth( root->left, curDepth, minDepth );
    if( root->right )
        findMinDepth( root->right, curDepth, minDepth );
}

void main( void )
{
    node_t * root = newNode( 0 );
    root->left = newNode( 1 );
    root->right = newNode( 2 );
    root->left->left = newNode( 3 );
    root->right->right = newNode( 4 );
    //root->right->right->left = newNode( 5 );

    int depth = 100;

    findMinDepth( root, 0, &depth );
    printf( "minDepth:%d\n", depth );
}
