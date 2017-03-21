/************************************************
* creator: vingc zhang
* time: 2017.03.21
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/find-maximum-path-sum-in-a-binary-tree/
Given a binary tree, find the maximum path sum. The path may start and end at any node in the tree.

Input: Root of below tree
       1
      / \
     2   3
Output: 6
**/


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

int max( int a, int b )
{
    if( a < b )
        return b;
    else
        return a;
}

/*
1. let A1 to be the maximum path sum of left subtree of root,
   let A2 to be the maximum path sum of right subtree of root,
   let B1 to be the maximum depth sum of left subtree of root,
   let B2 to be the maximum depth sum of right subtree of root,
2. so the maximum path sum of root is max(A1,A2,B1+B2+root.value)*/
void findMaxPathSum( node_t * root, int * MaxDepthSum, int * MaxPathSum )
{
    int leftMaxDepthSum = 0 ;
    int rightMaxDepthSum = 0;

    int leftMaxPathSum = 0;
    int rightMaxPathSum = 0;

    if( root == NULL )
    {
        return;
    }

    //if no subtree, the maximum of path sum from root is the value of root.
    if( root->left == NULL || root->right == NULL )
    {
        *MaxDepthSum = root->v; //only root node
        *MaxPathSum = root->v;  //only root node
        return;
    }

    //recursive the subtree
    findMaxPathSum( root->left, &leftMaxDepthSum, &leftMaxPathSum );
    findMaxPathSum( root->right, &rightMaxDepthSum, &rightMaxPathSum );

    //extend the depth path to root
    *MaxDepthSum = max( leftMaxDepthSum, rightMaxDepthSum ) + root->v;
    *MaxPathSum  = max( max( leftMaxPathSum, rightMaxPathSum ),
                       leftMaxDepthSum + rightMaxDepthSum + root->v );

    return;
}

void main( void )
{

    node_t * root = newNode( 0 );
    root->left = newNode( 1 );
    root->right = newNode( 2 );
    root->left->left = newNode( 3 );
    root->right->right = newNode( 4 );
    //root->right->right->left = newNode( 5 );

    int maxPathSum;
    int maxDepthSum;

    findMaxPathSum( root, &maxDepthSum, &maxPathSum );

    printf( "maxDepthSum:%d, maxPathSum:%d\n", maxDepthSum, maxPathSum );
}
