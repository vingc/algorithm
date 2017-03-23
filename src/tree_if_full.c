/************************************************
* creator: vingc zhang
* time: 2017.03.23
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
A full binary tree is defined as a binary tree in which all nodes have either zero or two child nodes.
Conversely, there is no node in a full binary tree, which has one child node.
*/

#define true  1
#define false 0


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

//postorder free list
void freeTree( node_t ** root )
{
    node_t * curNode = *root;
    if( curNode == NULL )
    {
        return;
    }

    if( curNode->left )
    {
        freeBst( &curNode->left );
    }

    if( curNode->right )
    {
        freeBst( &curNode->right );
    }

    free( curNode );
    *root = NULL;

    return;
}


int bTreeIsFull( node_t * root )
{
    //null tree, full
    if( root == NULL )
    {
        return true;
    }

    //have no child, leaf, full
    if ( root->left == NULL && root->right == NULL )
    {
        return true;
    }

    //have one child node, not full
    if( root->left == NULL || root->right == NULL )
    {
        return false;
    }

    //all subtree is full ,so the parent tree is full
    return bTreeIsFull( root->left ) && bTreeIsFull( root->right );
}

void main( void )
{
    node_t * root = NULL;
    root = newNode( 0 );
    root->left = newNode( 1 );
    root->right = newNode( 2 );
    root->right->right = newNode( 2 );
    root->left->left = newNode( 4 );
    root->left->right = newNode( 4 );

    printf( "%d\n", bTreeIsFull( root ) );

    freeTree( root );
}
