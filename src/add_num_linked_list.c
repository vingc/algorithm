/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/add-two-numbers-represented-by-linked-lists/
Add two numbers represented by linked lists | Set 1
Given two numbers represented by two lists, write a function that returns sum list. The sum list is list representation of addition of two input numbers.

Example 1

Input:
  First List: 5->6->3  // represents number 365
  Second List: 8->4->2 //  represents number 248
Output
  Resultant list: 3->1->6  // represents number 613
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

void addLinkedList( list_t * pList1, list_t * pList2 )
{
    list_t  res;
    int carry = 0,sum;

    node_t * node1 = pList1->head;
    node_t * node2 = pList2->head;
    node_t * lastRes, * tmp;

    res.head = NULL;
    lastRes  = NULL;

    while( node1 || node2 )
    {
        sum = carry + (node1?node1->v:0) + (node2?node2->v:0);

        carry = (sum>=10?1:0);
        sum = sum%10;

        tmp = newNode( sum );

        if( res.head == NULL )
        {
            res.head = tmp;
            lastRes = tmp;
        }
        else
        {
            lastRes->next = tmp;
            lastRes = tmp;
        }

        if( node1 )
            node1 = node1->next;
        if( node2 )
            node2 = node2->next;
    }

    if( carry > 0 )
    {
        tmp = newNode( carry );
        if( res.head == NULL )
        {
            res.head = tmp;
        }
        else
        {
            lastRes->next = tmp;
        }
    }

    printList( &res );
    freeListNode( &res );
}

void main( void )
{
    list_t list1,list2;
    list1.head = NULL;
    list2.head = NULL;

    createListByNumStr( &list1, "365" );
    createListByNumStr( &list2, "248" );
    addLinkedList( &list1, &list2 );
    freeListNode( &list1 );
    freeListNode( &list2 );
}


