/************************************************
* creator: vingc zhang
* time: 2017.03.22
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/check-if-a-given-array-can-represent-preorder-traversal-of-binary-search-tree/
Check if a given array can represent Preorder Traversal of Binary Search Tree
Given an array of numbers, return true if given array can represent
preorder traversal of a Binary Search Tree, else return false.
Expected time complexity is O(n).

Input:  pre[] = {2, 4, 3}
Output: true
Given array can represent preorder traversal
of below tree
    2
     \
      4
     /
    3

Input:  pre[] = {2, 4, 1}
Output: false
Given array cannot represent preorder traversal
of a Binary Search Tree.

Input:  pre[] = {40, 30, 35, 80, 100}
Output: true
Given array can represent preorder traversal
of below tree
     40
   /   \
 30    80
  \      \
  35     100


Input:  pre[] = {40, 30, 35, 20, 80, 100}
Output: false
Given array cannot represent preorder traversal
of a Binary Search Tree.

1. construct BST by preorder from the given array.
2. if there is right subtree of a node, but the current item of array is smaller than the node,
   we can't construct BST by preorder, so result is false.
3. else, if we succeed in constructing BST by preorder used all array items, then result is true.
*/

#define true  1
#define false 0
#define MAX_LEN  20

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
void freeBst( node_t ** root )
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

int constructBst( node_t ** root, node_t * node )
{
    if( node == NULL || root == NULL )
    {
        return -1;
    }

    //reach the leaf node.
    if( *root == NULL )
    {
        *root = node;
        return true;
    }


    if( node->v < (*root)->v )
    {
        /* if root have right subtree, means that we now traverse the right subtree, so can't insert into left subtree */
        if( (*root)->right != NULL )
        {
            return false;
        }

        //insert left subtree
        return constructBst( &(*root)->left, node );
    }

    //insert right subtree
    return constructBst( &(*root)->right, node );
}

int isPresentPreOrderBst( int a[], int n )
{
    int i;

    node_t * root = NULL;

    for( i = 0; i < n; i++ )
    {
        if ( false == constructBst( &root, newNode( a[i] ) ) )
        {
            freeBst( &root );
            return false;
        }
    }

    freeBst( &root );
    return true;
}

//method from geeksforgeeks
int canRepresentBst( int a[], int n )
{
    int stack[ MAX_LEN ];
    int idx = -1; //point to the top of stack
    int i;
    int root; //point to the current root of subtree;

    root = -1; //
    for( i = 0; i < n; i++ )
    {
        //find a value in right side smaller than root, so not preorder
        if( a[i] < root )
        {
            return false;
        }

        //find a greater value than current root, so find this value's root
        while( idx >= 0 && stack[idx] < a[i] )
        {
            root = stack[idx];
            idx--;
        }

        //stack empty,or value is smaller than root, left side, push
        idx++;
        stack[idx] = a[i];
    }

    return true;
}

void main( void )
{
    node_t * root = NULL;

    int a[] = {2, 4, 3}; //true
    int b[] = {2, 4, 1}; //false
    int c[] = {40, 30, 35, 80, 100}; //true
    int d[] = {40, 30, 35, 20, 80, 100}; //false

    printf( "a:%d\n", canRepresentBst( a, 3 ) );
    printf( "b:%d\n", canRepresentBst( b, 3 ) );
    printf( "c:%d\n", canRepresentBst( c, 5 ) );
    printf( "d:%d\n", canRepresentBst( d, 6 ) );
}
