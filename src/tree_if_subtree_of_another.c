/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Check if a binary tree is subtree of another binary tree | Set 2
Given two binary trees, check if the first tree is subtree of the second one. A subtree of a tree T is a tree S consisting of a node in T and all of its descendants in T.

The subtree corresponding to the root node is the entire tree; the subtree corresponding to any other node is called a proper subtree.

For example, in the following case, Tree1 is a subtree of Tree2.


        Tree1
          x
        /    \
      a       b
       \
        c


        Tree2
              z
            /   \
          x      e
        /    \     \
      a       b      k
       \
        c

1. find the root node of tree1 in tree2, when we find the node AS S1;
2. compare the subtree S1 as the root node to tree1, if equal, then result is true.
3. else, goto #1, until traverse the whole tree2, then result is false.
*/


#define true  1
#define false 0

#define MAX_LEN  20

typedef struct node
{
    int v;
    int hv; //horizontal value
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
        freeTree( &curNode->left );
    }

    if( curNode->right )
    {
        freeTree( &curNode->right );
    }

    free( curNode );
    *root = NULL;

    return;
}

//preorder
int findRoot( node_t * root1, node_t * root2 )
{
    int ret;

    if( root1 == NULL )
    {
        return false;
    }

    if( root1->v == root2->v )
    {
        if( isEqualTree( root1, root2 ) )
        {
            return true;
        }
    }

    ret = findRoot( root1->left, root2 );
    if( ret == false )
    {
        ret = findRoot( root1->right, root2 );
    }
    return ret;
}

/* check if root2 is subtree of root1 */
int isEqualTree( node_t * root1, node_t * root2 )
{
    int ret = true;

    if( root1 == NULL && root2 == NULL )
    {
        return true;
    }

    if( root1 == NULL || root2 == NULL )
    {
        return false;
    }

    if( root1->v == root2->v )
    {
        /* the left subtrees are equal to each other, and the right subtrees are equal to each other */
        ret &= isEqualTree( root1->left, root2->left );
        ret &= isEqualTree( root1->right, root2->right );
        if( ret == true )
        {
            return true;
        }
    }

    return false;
}

int isSubTree( node_t * root1, node_t * root2 )
{
    if( root2 == NULL )
    {
        return true;
    }

    if( root1 == NULL )
    {
        return false;
    }

    return findRoot( root1, root2 );
}

void main( void )
{
    node_t * root2 = newNode( 'x' );
    root2->left = newNode( 'a' );
    root2->left->right = newNode( 'c' );
    root2->right = newNode( 'b' );

    node_t * root1 = newNode( 'x' );
    root1->left = newNode( 'a' );
    root1->left->right = newNode( 'c' );
    root1->right = newNode( 'b' );
    root1->right->right = newNode( 'd' );

    node_t * root3 = newNode( 'z' );
    root3->left = root2;
    root3->right = newNode( 'e' );

    printf( "%d\n", isSubTree( root2, root3 ) );
}
