/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Merge a linked list into another linked list at alternate positions
Given two linked lists, insert nodes of second list into first list at alternate positions of first list.
For example, if first list is 5->7->17->13->11 and second is 12->10->2->4->6, t
he first list should become 5->12->7->10->17->2->13->4->11->6 and second list should become empty.
The nodes of second list should only be inserted when there are positions available.
For example, if the first list is 1->2->3 and second list is 4->5->6->7->8,
then first list should become 1->4->2->5->3->6 and second list to 7->8.

Use of extra space is not allowed (Not allowed to create additional nodes),
i.e., insertion must be done in-place. Expected time complexity is O(n) where n is number of nodes in first list.

The idea is to run a loop while there are available positions in first loop
and insert nodes of second list by changing pointers.
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

void mergeList( list_t * pList1, list_t * pList2 )
{
    node_t * node1 = pList1->head;
    node_t * node2 = pList2->head;
    node_t * tmp;

    while( node1 && node2 )
    {
        //take node from list2
        tmp = node2;
        node2 = node2->next;

        //insert node into list1 after node1
        tmp->next = node1->next;
        node1->next = tmp;

        //forward node1 two node.
        node1 = node1->next->next;
    }


    pList2->head = node2;

    printList( pList1 );
    printList( pList2 );
}


void main( void )
{
    list_t list1,list2;
    list1.head = NULL;
    list2.head = NULL;

    createListByNumStr( &list1, "365" );
    createListByNumStr( &list2, "24" );
    mergeList( &list1, &list2 );
    freeListNode( &list1 );
    freeListNode( &list2 );
}

