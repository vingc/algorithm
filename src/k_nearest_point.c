#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* if given some points in xy-cooperation surface and pick one point A as the origin,
find the nearest k points of A.
solution: use K-size maxHeap to search all points.
1. the distance of a point B to A is (B.x-A.x)^2 + (B.y-A.y)^2; regard A as the origin point zero.
2. take the first K points to create k-size maxHeap;
3. traverse the left points, check if distance of the top point of maxHeap is longer
   than any others in left points, remote the top point and add the nearer point to maxHeap.
4. when have traversed all the left points, the points in maxHeap is the nearest points from A;
*/

typedef struct point
{

    int x;
    int y;
    int dist; //(B.x-A.x)^2 + (B.y-A.y)^2
}point_t;

typedef struct point_list
{
    point_t * head; //array of size
    int       size;
    int       capacity;
}point_list_t;


void printSolution( point_list_t * list )
{
    int i;


    for( i = 0; i < list->size; i++ )
    {
        printf( "(%d,%d) ", list->head[i].x, list->head[i].y );
    }
}

void maxHeapSwap( point_t * src, point_t * dst )
{
    point_t tmp;

    tmp   = *src;
    *src  = *dst;
    *dst  = tmp;
}


int pointCompare( point_t * src, point_t * dst )
{
    return src->dist - dst->dist;
}

void maxHeapFixUp( point_list_t * list, int idx )
{
    int j = (idx - 1)/2;

    if( j >= 0 && idx != 0 )
    {
        if( pointCompare( &list->head[j], &list->head[idx] ) < 0 )
        {
            //move  the bigger up
            maxHeapSwap( &list->head[j], &list->head[idx] );
            maxHeapFixUp( list, j );
        }
    }

    return;
}

void maxHeapFixDown( point_list_t * list, int idx )
{
    int j    = 2*idx+1; //left child
    int less = idx;

    if( j < list->size && pointCompare( &list->head[j], &list->head[less] ) > 0 )
    {
        less = j;
    }

    j++; //right child
    if( j < list->size && pointCompare( &list->head[j], &list->head[less] ) > 0 )
    {
        less = j;
    }

    if( less != idx )
    {
        //move  the bigger up
        maxHeapSwap( &list->head[less], &list->head[idx] );
        maxHeapFixDown( list, less );
    }

    return;
}

void maxHeapAdd( point_list_t * list, point_t * point )
{
    if( list->size < list->capacity )
    {
        list->head[list->size++] = *point;
        maxHeapFixUp( list, list->size - 1 );
    }
    else
    {
        printf( "maxHeapAdd() capacity is full\n" );
    }

    return;
}

void maxHeapRemove( point_list_t * list )
{
    if( list->size > 0 )
    {
        //take the last to be top, then resize and heapify
        maxHeapSwap( &list->head[0], &list->head[list->size-1] );
        list->size--;
        maxHeapFixDown( list, 0 );
    }
}


/* list: keep the given points except origin A. the distances of points have been concluded.

      k: is the no of nearest points we need the find out.*/
void kFind( point_list_t * list, int k )
{
    point_list_t heap;
    int          i;

    heap.size     = 0;
    heap.capacity = k;
    heap.head     = (point_t *)malloc( sizeof( point_t ) * k );
    if( heap.head == NULL )
    {
        printf( "kFind() malloc(%d) err\n", k );
        return;
    }

    memset( heap.head, 0x0, sizeof( point_t ) * k );

    if( list->size <= k )
    {
        //memcpy( heap.list, list->list, list->size * sizeof( point_t ) );
        printSolution( list );
        free( heap.head );
        return;
    }

    /* 2. pick the first K to create the k-size maxHeap */
    for( i = 0; i < k; i++ )
    {
        //point = &list->head[i];
        maxHeapAdd( &heap, &list->head[i] );
    }

    /* 3. pick the left point, compareTo the top,if is nearer, then remove top, and add it to maxHeap*/
    for( i = k; i < list->size; i++ )
    {
        if( pointCompare( &heap.head[0], &list->head[i] ) > 0 )
        {
            //maxHeapSwap( &heap.head[0], &list->head[i] );
            //maxHeapFixDown( &heap, 0 );
            maxHeapRemove( &heap );
            maxHeapAdd( &heap, &list->head[i] );
        }
    }

    printSolution( &heap );
    free( heap.head );
    return;
}

void listPointAdd( point_list_t * list, int x, int y, point_t * A )
{
    int distX = x - A->x;
    int distY = y - A->y;

    if( list->size < list->capacity )
    {
        list->head[list->size].x = x;
        list->head[list->size].y = y;
        list->head[list->size].dist = distX * distX + distY * distY;

        list->size++;
    }
}

void main( void )
{
    point_list_t list;
    int k = 9;
    point_t A;
    int capacity = 10;

    A.x = 0;
    A.y = 0;

    list.size = 0;
    list.capacity = capacity;
    list.head = (point_t *)malloc( sizeof( point_t ) * list.capacity );

    listPointAdd( &list, 1, 1, &A );
    listPointAdd( &list, 1, 2, &A );
    listPointAdd( &list, 2, 2, &A );

    listPointAdd( &list, 3, 3, &A );
    listPointAdd( &list, 5, 5, &A );
    listPointAdd( &list, -1, 5, &A );

    listPointAdd( &list, 1, -5, &A );
    listPointAdd( &list, -2, -6, &A );
    listPointAdd( &list, -2, -1, &A );
    listPointAdd( &list, 4, 7, &A );

    kFind( &list, k );
}
