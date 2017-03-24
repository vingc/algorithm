/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/reverse-alternate-levels-binary-tree/
Given a Perfect Binary Tree, reverse the alternate level nodes of the binary tree.


Given tree:
               a
            /     \
           b       c
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
       h  i j  k l  m  n  o

Modified tree:
  	       a
            /     \
           c       b
         /  \     /  \
        d    e    f    g
       / \  / \  / \  / \
      o  n m  l k  j  i  h

A simple solution is to do following steps.
1) Access nodes level by level.
2) If current level is odd, then store nodes of this level in an array.
3) Reverse the array and store elements back in tree.
*/


#define true  1
#define false 0

#define MAX_LEN  100

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

void printTree( node_t * root )
{
    if( root == NULL )
    {
        printf( "NULL\n" );
        return;
    }


}

void reverseAlter( node_t * root )
{
    int stack[ MAX_LEN ];
    int idx;

    node_t * tmp;
    int levelCnt;
    int level = 0;
    int i;

    node_t * queue[ MAX_LEN ];
    int begin;
    int end;

    queue[0] = root;
    begin = 0;
    end = begin + 1;

    //assume the length of queue is bigger than count of nodes in tree.
    while( begin < end )
    {
        levelCnt = end - begin;

        //next level is odd, store the next level in stack
        memset( stack, 0x0, sizeof( int ) * MAX_LEN );
        idx = -1; //point to the top of stack.

        //traverse level
        for( i = 0; i < levelCnt; i++ )
        {
            tmp = queue[begin+i];

            if( tmp->left )
            {
                queue[end++] = tmp->left;
                stack[++idx] = tmp->left->v;
            }

            if( tmp->right )
            {
                queue[end++] = tmp->right;
                stack[++idx] = tmp->right->v;
            }
        }

        /* reverse next level */
        if( level % 2 == 0 )
        {

            printf( "level-%d:", level+1 );
            for( i = 0; i < levelCnt; i++ )
            {
                tmp = queue[begin+i];
                if( tmp->left )
                {
                    tmp->left->v = stack[idx--];

                    printf( "%c ", tmp->left->v );
                }

                if( tmp->right )
                {
                    tmp->right->v = stack[idx--];
                    printf( "%c ", tmp->right->v );
                }
            }

            printf( "\n" );
        }

        //move the next level
        begin += levelCnt;
        level++;
    }
}

void main( void )
{
    node_t * root = newNode( 'a' );
    root->left = newNode( 'b' );
    root->right = newNode( 'c' );

    root->left->left = newNode( 'd' );
    root->left->right = newNode( 'e' );
    root->right->left = newNode( 'f' );
    root->right->right = newNode( 'g' );

    root->left->left->left = newNode( 'h' );
    root->left->left->right = newNode( 'i' );
    root->left->right->left = newNode( 'j' );
    root->left->right->right = newNode( 'k' );
    root->right->left->left = newNode( 'l' );
    root->right->left->right = newNode( 'm' );
    root->right->right->left = newNode( 'n' );
    root->right->right->right = newNode( 'u' );

    reverseAlter( root );

    freeTree( &root );
    return;
}

/*
ref: method 3, O(n); traverse once
void preorder(struct Node *root1, struct Node* root2, int lvl)
{
    // Base cases
    if (root1 == NULL || root2==NULL)
        return;

    // Swap subtrees if level is even
    if (lvl%2 == 0)
        swap(root1->key, root2->key);

    // Recur for left and right subtrees (Note : left of root1
    // is passed and right of root2 in first call and opposite
    // in second call.
    preorder(root1->left, root2->right, lvl+1);
    preorder(root1->right, root2->left, lvl+1);
}

// This function calls preorder() for left and right children
// of root
void reverseAlternate(struct Node *root)
{
   preorder(root->left, root->right, 0);
}
*/
