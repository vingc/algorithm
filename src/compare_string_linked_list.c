/************************************************
* creator: vingc zhang
* time: 2017.03.11
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/compare-two-strings-represented-as-linked-lists/
Given two linked lists, represented as linked lists (every character is a node in linked list).
Write a function compare() that works similar to strcmp(),
i.e., it returns 0 if both strings are same,
1 if first linked list is lexicographically greater,
and -1 if second string is lexicographically greater.

Examples:

Input: list1 = g->e->e->k->s->a
       list2 = g->e->e->k->s->b
Output: -1

Input: list1 = g->e->e->k->s->a
       list2 = g->e->e->k->s
Output: 1

Input: list1 = g->e->e->k->s
       list2 = g->e->e->k->s
Output: 0
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


//insert node at the end of list
void insert( list_t * pList, node_t * pNode )
{
    node_t * pCurNode = pList->head;

    if( pList->head == NULL )
    {
        pList->head = pNode;
        return;
    }

    while( pCurNode->next != NULL )
    {
        pCurNode = pCurNode->next;
    }

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

void createListByStr( list_t * pList, char * pstr )
{
    if( pList == NULL || pstr == NULL )
        return;

    while( *pstr != '\0' )
    {
        insert( pList, newNode( (int)*pstr ) );
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

    for( pCurNode = pList->head; pCurNode; pCurNode = pCurNode->next )
    {
        printf( "%c ", pCurNode->v );
    }

    printf( "\n" );
}

#if 0
int compare(Node *list1, Node *list2)
{
    // Traverse both lists. Stop when either end of a linked
    // list is reached or current characters don't match
    while (list1 && list2 && list1->c == list2->c)
    {
        list1 = list1->next;
        list2 = list2->next;
    }

    //  If both lists are not empty, compare mismatching
    //  characters
    if (list1 && list2)
        return (list1->c > list2->c)? 1: -1;

    // If either of the two lists has reached end
    if (list1 && !list2) return 1;
    if (list2 && !list1) return -1;

    // If none of the above conditions is true, both
    // lists have reached end
    return 0;
}
#endif // 0

int compareNode( node_t * node1, node_t * node2 )
{
    if( node1 == NULL && node2 == NULL )
        return 0;
    if( node1 == NULL && node2 != NULL )
        return -1;
    if( node1 != NULL && node2 == NULL )
        return 1;

    if( node1->v == node2->v )
        return compareNode( node1->next, node2->next );

    return node1->v - node2->v;
}

int compareStrLinkedList( list_t * pList1, list_t * pList2 )
{
    return compareNode( pList1->head, pList2->head );
}

void main( void )
{
    list_t List1, List2;

    List1.head = NULL;
    List2.head = NULL;

    createListByStr( &List1, "geeksa" );
    createListByStr( &List2, "geeksb" );
    printf("%d\n", compareStrLinkedList( &List1, &List2 ) );
    freeListNode( &List1 );
    freeListNode( &List2 );

    createListByStr( &List1, "geeksa" );
    createListByStr( &List2, "geeks" );
    printf("%d\n", compareStrLinkedList( &List1, &List2 ) );
    freeListNode( &List1 );
    freeListNode( &List2 );

    createListByStr( &List1, "geeks" );
    createListByStr( &List2, "geeksb" );
    printf("%d\n", compareStrLinkedList( &List1, &List2 ) );
    freeListNode( &List1 );
    freeListNode( &List2 );

    createListByStr( &List1, "geeks" );
    createListByStr( &List2, "geeks" );
    printf("%d\n", compareStrLinkedList( &List1, &List2 ) );
    freeListNode( &List1 );
    freeListNode( &List2 );
}
