/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/print-nodes-top-view-binary-tree/
Top view of a binary tree is the set of nodes visible when the tree is viewed from the top.
Given a binary tree, print the top view of it. The output nodes can be printed in any order.
Expected time complexity is O(n)

A node x is there in output if x is the topmost node at its horizontal distance.
Horizontal distance of left child of a node x is equal to horizontal distance of x minus 1,
and that of right child is horizontal distance of x plus 1.

       1
    /     \
   2       3
  /  \    / \
 4    5  6   7
Top view of the above binary tree is
4 2 1 3 7

        1
      /   \
    2       3
      \
        4
          \
            5
             \
               6
Top view of the above binary tree is
2 1 3 6

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

//level order traverse
void topView( node_t * root )
{
    node_t * pop;
    node_t * queue[ MAX_LEN ];
    int begin;// point to the begin of queue, first valid point of item
    int end; // point to the end of queue. first null point of item

    node_t * map[ 2 * MAX_LEN ]; //keep the top most node at each horizontal value.
    int midHv = MAX_LEN;

    if( root == NULL )
    {
        return;
    }

    memset( queue, 0x0, sizeof( node_t * ) * MAX_LEN );
    memset( map, 0x0, sizeof( node_t * ) * 2 * MAX_LEN );

    root->hv = midHv;
    begin = 0;
    queue[begin] = root;
    end = begin+1;

    //FIFO
    while( begin != end )
    {
        pop = queue[begin];
        begin = ( begin + 1 ) % MAX_LEN;

        if( pop == NULL )
        {
            break;
        }

        //add to map; only when it's the first node of particular hv
        if( pop->hv >= 0 && pop->hv < 2 * MAX_LEN && map[ pop->hv ] == NULL )
        {
            map[ pop->hv ] = pop;
        }

        if( pop->left )
        {
            pop->left->hv = pop->hv - 1;
            queue[end] = pop->left;
            end = ( end + 1 ) % MAX_LEN;
        }


        if( pop->right )
        {
            pop->right->hv = pop->hv + 1;
            queue[end] = pop->right;
            end = ( end + 1 ) % MAX_LEN;
        }
    }

    int i = 0;
    for( i = 0; i < 2 * MAX_LEN; i++ )
    {
        if( map[i] == NULL )
        {
            continue;
        }

        printf( "%d ", map[i]->v );
    }
}

void main( void )
{
    /* Create following Binary Tree
             1
           /  \
          2    3
           \
            4
             \
              5
               \
                6*/
    node_t * root = NULL;
    root = newNode( 1 );
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->right = newNode(4);
    root->left->right->right = newNode(5);
    root->left->right->right->right = newNode(6);

    topView( root );
}
