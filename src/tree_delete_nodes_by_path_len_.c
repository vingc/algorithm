/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Remove nodes on root to leaf paths of length < K
Given a Binary Tree and a number k,
remove all nodes that lie only on root to leaf path(s) of length smaller than k.
If a node X lies on multiple root-to-leaf paths and if any of the paths has path length >= k,
then X is not deleted from Binary Tree.
In other words a node is deleted if all paths going through it have lengths smaller than k.

Consider the following example Binary Tree

               1
           /      \
         2          3
      /     \         \
    4         5        6
  /                   /
 7                   8
Input: Root of above Binary Tree
       k = 4

Output: The tree should be changed to following
           1
        /     \
      2          3
     /             \
   4                 6
 /                  /
7                  8
There are 3 paths
i) 1->2->4->7      path length = 4
ii) 1->2->5        path length = 3
iii) 1->3->6->8    path length = 4
There is only one path " 1->2->5 " of length smaller than 4.
The node 5 is the only node that lies only on this path, so
node 5 is removed.
Nodes 2 and 1 are not removed as they are parts of other paths
of length 4 as well.

If k is 5 or greater than 5, then whole tree is deleted.

If k is 3 or less than 3, then nothing is deleted.

The idea here is to use post order traversal of the tree.
Before removing a node we need to check that all the children of that node in the shorter path are already removed.
There are 2 cases:
i) This node becomes a leaf node in which case it needs to be deleted.
ii) This node has other child on a path with path length >= k. In that case it needs not to be deleted.

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

int deleteNode( node_t ** root, int k )
{
    node_t * curNode = *root;
    int deleteFlag;

    if ( curNode == NULL && k > 1 )
    {
        return true;
    }

    //leaf and 1 < k, then delete
    if ( curNode->left == NULL && curNode->right == NULL && k > 1 )
    {
        printf( "delete:%d\n", curNode->v );
        free( curNode );
        *root = NULL;
        return true;
    }

    if( k <= 1 )
    {
        //this level, path equal to k, so don't need to delete any node in the path,
        return false;
    }

    deleteFlag = true;

    if( curNode->left )
    {
        deleteFlag &= deleteNode( &curNode->left, k - 1 );
    }

    if( curNode->right )
    {
        deleteFlag &= deleteNode( &curNode->right, k - 1 );
    }

    //all children have been deleted.
    if( deleteFlag == true )
    {
        printf( "delete:%d\n", curNode->v );
        free( curNode );
        *root = NULL;
        return true;
    }

}

void main( void )
{
    /*
               1
           /      \
         2          3
      /     \         \
    4         5        6
  /                   /
 7                   8*/
    node_t * root = newNode( 1 );
    root->left = newNode( 2 );
    root->right = newNode( 3 );
    root->left->left = newNode( 4 );
    root->left->right = newNode( 5 );
    root->right->right = newNode( 6 );
    root->left->left->left = newNode( 7 );
    root->right->right->left = newNode( 8 );
    root->right->right->left->right = newNode( 9 );

    deleteNode( &root, 5 );

}
