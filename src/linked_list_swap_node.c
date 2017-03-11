/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/
wap nodes in a linked list without swapping data
Given a linked list and two keys in it, swap nodes for two given keys. Nodes should be swapped by changing links. Swapping data of nodes may be expensive in many situations when data contains many fields.

It may be assumed that all keys in linked list are distinct.

Examples:

Input:  10->15->12->13->20->14,  x = 12, y = 20
Output: 10->15->20->13->12->14

Input:  10->15->12->13->20->14,  x = 10, y = 20
Output: 20->15->12->13->10->14

Input:  10->15->12->13->20->14,  x = 12, y = 13
Output: 10->15->13->12->20->14
This may look a simple problem, but is interesting question as it has following cases to be handled.
1) x and y may or may not be adjacent.
2) Either x or y may be a head node.
3) Either x or y may be last node.
4) x and/or y may not be present in linked list.
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


//insert node at the head of list
void insert( list_t * pList, node_t * pNode )
{
    pNode->next = pList->head;
    pList->head = pNode;
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

void createListByNumStr( list_t * pList, char * pstr )
{
    if( pList == NULL || pstr == NULL )
        return;

    while( *pstr != '\0' )
    {
        insert( pList, newNode( (int)*pstr - 48 ) );
        pstr++;
    }

    printList( pList );
}

void freeListNode( list_t * pList )
{
    node_t * tmp;
    while( pList->head )
    {
        tmp = pList->head;
        pList->head = pList->head->next;
        free( tmp );
    }
}

void printList( list_t * pList )
{
    node_t * pCurNode;

    printf("list: ");
    for( pCurNode = pList->head; pCurNode && pCurNode->next; pCurNode = pCurNode->next )
    {
        printf( "%d->", pCurNode->v );
    }

    if( pCurNode )
        printf( "%d", pCurNode->v );

    printf( "\n" );
}

/* k1/k2 is diff */
void swapNode( list_t * pList, int k1, int k2 )
{
    node_t * prev1 = NULL;
    node_t * prev2 = NULL;
    node_t * key1  = NULL;
    node_t * key2  = NULL;

    node_t * tmp;

    /* find k1 & k2 */
    tmp = pList->head;
    while( tmp )
    {
        if( tmp->v == k1 )
        {
            key1 = tmp;
            break;
        }

        prev1 = tmp;
        tmp = tmp->next;
    }

    if( key1 == NULL )
    {
        return;
    }

    /* find k2 */
    tmp = pList->head;
    while( tmp )
    {
        if( tmp->v == k2 )
        {
            key2 = tmp;
            break;
        }

        prev2 = tmp;
        tmp = tmp->next;
    }

    if( key2 == NULL )
    {
        return;
    }

    #if 0
    /* if key1 is head */
    if( prev1 == NULL || prev2 == NULL )
    {
        /* swap pointer, make prev1 = NULL */
        if( prev2 == NULL )
        {
            tmp = prev1;
            prev1 = prev2;
            prev2 = tmp;

            tmp  = key1;
            key1 = key2;
            key2 = tmp;
        }

        if( key1->next == key2 )
        {
            pList->head = key2;
            key1->next = key2->next;
            key2->next = key1;

        }
        else
        {
            pList->head = key2;
            prev2->next = key1;

            tmp = key2->next;
            key2->next = key1->next;
            key1->next = tmp;
        }

        return;
    }

    /* if key1->next == key2 */
    if( key1->next == key2 || key2->next == key1 )
    {
        /* swap pointer, make key1->next == key2 */
        if( key2->next == key1 )
        {
            tmp = prev1;
            prev1 = prev2;
            prev2 = tmp;

            tmp  = key1;
            key1 = key2;
            key2 = tmp;
        }

        prev1->next = key2;
        key1->next = key2->next;
        key2->next = key1;

        return;
    }

    prev1->next = key2;
    prev2->next = key1;

    tmp = key2->next;
    key2->next = key1->next;
    key1->next = tmp;
    #else
       // If key1 is not head of linked list
    if (prev1 != NULL)
        prev1->next = key2;
    else // Else make key2 as new head
        pList->head = key2;

    // If key2 is not head of linked list
    if (prev2 != NULL)
        prev2->next = key1;
    else  // Else make key1 as new head
        pList->head = key1;

    // Swap next pointers
    tmp = key2->next;
    key2->next = key1->next;
    key1->next  = tmp;
    #endif
    return;
}


void main( void )
{
    list_t list1;
    list1.head = NULL;

    createListByNumStr( &list1, "365789" );
    swapNode( &list1, 3, 9 );
    printList( &list1 );

    freeListNode( &list1 );
}
