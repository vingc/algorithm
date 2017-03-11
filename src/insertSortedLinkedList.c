/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given a linked list which is sorted, how will you insert in sorted way
1) If Linked list is empty then make the node as head and return it.
2) If value of the node to be inserted is smaller than value of head node
    then insert the node at start and make it head.
3) In a loop, find the appropriate node after which the input node (let 9) is
    to be inserted. To find the appropriate node start from head, keep moving
    until you reach a node GN (10 in the below diagram) who's value is
    greater than the input node. The node just before GN is the appropriate
    node (7).
4) Insert the node (9) after the appropriate node (7) found in step 3.
*/

typedef struct node
{
    int  v;
    struct node * next;
}node_t;

typedef struct list
{
    struct node * head;
}list_t;

//sorted in increasing order
void insert( list_t * pList, node_t * pNode )
{
    node_t * pCurNode;

    if( pList == NULL || pNode == NULL )
    {
        return;
    }

    if( pList->head == NULL || pList->head->v >= pNode->v )
    {
        pNode->next = pList->head;
        pList->head = pNode;
        return;
    }

    pCurNode = pList->head;
    while( pCurNode->next != NULL && pCurNode->next->v < pNode->v )
    {
        pCurNode = pCurNode->next;
    }

    pNode->next = pCurNode->next;
    pCurNode->next = pNode;

    return;
}

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
    tmp->next = NULL;

    return tmp;
}

void printList( list_t * pList )
{
    node_t * pCurNode;

    for( pCurNode = pList->head; pCurNode; pCurNode = pCurNode->next )
    {
        printf( "%d ", pCurNode->v );
    }
}

void main( void )
{
    list_t list;

    list.head = NULL;

    insert( &list, newNode( 1 ) );
    insert( &list, newNode( 3 ) );
    insert( &list, newNode( 3 ) );
    insert( &list, newNode( 6 ) );
    insert( &list, newNode( 2 ) );

    printList( &list );
}
