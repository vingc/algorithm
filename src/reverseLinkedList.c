/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given a linked list, how to reverse it; or reverse every k nodes (where k is an input to the function).

Example:
Inputs:   1->2->3->4->5->6->7->8->NULL and k = 3
Output:   3->2->1->6->5->4->8->7->NULL.

Inputs:   1->2->3->4->5->6->7->8->NULL and k = 5
Output:   5->4->3->2->1->8->7->6->NULL.

Inputs:   1->2->3->4->5->6->7->8->NULL and k = capacity
Output:   8->7->6->5->4->3->2->1->NULL.

1. reverse the whole list,
2. then reverse list which regard every k-nodes as one node .
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

    printf( "\n" );
}

void reverse( list_t * pList )
{
    node_t * prev;
    node_t * cur;
    node_t * next;

    if( pList->head == NULL )
    {
        return;
    }

    prev = NULL;
    cur  = pList->head;
    next = cur->next;
    while( 1 )
    {
        cur->next = prev;
        prev = cur;
        cur  = next;

        if( next != NULL )
        {
            next = next->next;
        }
        else
        {
            //prev is the last;
            break;
        }
    }

    pList->head = prev;
}

/* recursive */
void reverseUtil( list_t * pList, node_t * prev, node_t * cur )
{
    if( cur->next == NULL )
    {
        pList->head = cur;
    }
    else if( cur->next != NULL )
    {
        reverseUtil( pList, cur, cur->next );
    }

    cur->next = prev;
}

void reverse2( list_t * pList )
{

    if( pList->head == NULL )
    {
        return;
    }

    reverseUtil( pList, NULL, pList->head );
}

 //reverse every k nodes

void  reverseUtil2( node_t **begin, node_t **left, node_t *prev, node_t *cur, int cnt )
{
    if( cur == NULL )
    {
        *begin = prev; // the last node of k-nodes will be the begin node
        *left = NULL;  // no left node
        return;
    }
    else if ( cnt == 0 )
    {
        *begin = prev; // the last node of k-nodes will be the begin node
        *left = cur;   // save the left node
        return;
    }
    else
    {
        cnt--; //control the depth of recursion.
        reverseUtil2( begin, left, cur, cur->next, cnt );

        cur->next = prev; //reverse
    }
}

void reverseKNodes( list_t * pList, int k )
{
    node_t * begin; //the begin of k-nodes
    node_t * left;  // the begin of left-nodes
    node_t * resHead = NULL;
    node_t * prev = NULL;
    node_t * next;

    left = pList->head;
    while( left )
    {
        /*next used to save the left nodes, k used to control the depth of recursion
        reverse the next-k-nodes, the last node will become the begin, the first will become the last.
        */
        reverseUtil2( &begin, &next, NULL, left, k );
        left->next = NULL;

        //connect the begin of reversed k-nodes to the previous reversed node.
        if( resHead == NULL )
        {
            resHead = begin;
        }
        else
        {
            prev->next = begin;
        }
        prev = left; //move the prev to the end node of reversed k-nodes
        left = next; // copy next to left
    }

    pList->head = resHead;
}

#if 0
/* Reverses the linked list in groups of size k and returns the
   pointer to the new head node. */
struct node *reverse (struct node *head, int k)
{
    struct node* current = head;
    struct node* next = NULL;
    struct node* prev = NULL;
    int count = 0;

    /*reverse first k nodes of the linked list */
    while (current != NULL && count < k)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }

    /* next is now a pointer to (k+1)th node
       Recursively call for the list starting from current.
       And make rest of the list as next of first node */
    if (next !=  NULL)
       head->next = reverse(next, k);

    /* prev is new head of the input list */
    return prev;
}
#endif // 0
void main( void )
{
    list_t list;

    list.head = NULL;

    insert( &list, newNode( 1 ) );
    insert( &list, newNode( 3 ) );
    insert( &list, newNode( 4 ) );
    insert( &list, newNode( 6 ) );
    insert( &list, newNode( 2 ) );
    insert( &list, newNode( 7 ) );

    printList( &list );

    reverseKNodes( &list, 3 );
    printList( &list );
    //reverse( &list );
    //printList( &list );

    //reverse2( &list );
    //printList( &list );
}
