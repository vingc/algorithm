/************************************************
* creator: vingc zhang
* time: 2017.03.16
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
MergeSort(headRef)
1) If head is NULL or there is only one element in the Linked List
    then return.
2) Else divide the linked list into two halves.
      FrontBackSplit(head, &a, &b); // a and b are two halves
3) Sort the two halves a and b.
      MergeSort(a);
      MergeSort(b);
4) Merge the sorted a and b (using SortedMerge() discussed here)
   and update the head pointer using headRef.
     *headRef = SortedMerge(a, b);
*/

typedef struct node
{
    struct node * next;
    int value;
}node_t, list_t;

void frontBackSplit( node_t * list, node_t ** front, node_t ** back )
{
    node_t * slow;
    node_t * fast;

    if( list->next == NULL )
    {
        *front = list;
        *back = NULL;
        return;
    }

    /* split the list to two halves */
    slow = list;
    fast = list->next;

    while( fast != NULL )
    {
        fast = fast->next;
        if( fast != NULL )
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = list;
    *back = slow->next;
    slow->next = NULL;
    return;
}

//ASC order
node_t * merge( node_t * front, node_t * back )
{
    node_t * result;

    if( front == NULL )
    {
        result = back;
    }
    else if( back == NULL )
    {
        result = front;
    }
    else if ( front->value < back->value )
    {
        result = front;
        result->next = merge( front->next, back );
    }
    else
    {
        result = back;
        result->next = merge( front, back->next );
    }

    return result;
}

void mergeSort( node_t ** list )
{
    node_t * front;
    node_t * back;

    if( *list == NULL || (*list)->next == NULL )
    {
        return;
    }

    frontBackSplit( *list, &front, &back );

    mergeSort( &front );
    mergeSort( &back );

    *list = merge( front, back );
}

//sorted in increasing order
void insert( node_t ** pList, node_t * pNode )
{
    pNode->next = *pList;
    *pList = pNode;

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

    tmp->value = v;
    tmp->next = NULL;

    return tmp;
}

void printList( node_t * pList )
{
    node_t * pCurNode;

    for( pCurNode = pList; pCurNode; pCurNode = pCurNode->next )
    {
        printf( "%d ", pCurNode->value );
    }

    printf( "\n" );
}

void main( void )
{
    node_t * list = NULL;
    insert( &list, newNode(10) );
    insert( &list, newNode(2) );
    insert( &list, newNode(7) );
    insert( &list, newNode(9) );
    insert( &list, newNode(5) );
    printList( list );

    mergeSort( &list );
    printList( list );
}
