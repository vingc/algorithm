/************************************************
* creator: vingc zhang
* time: 2017.03.16
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://quiz.geeksforgeeks.org/binary-search/
Search a sorted array by repeatedly dividing the search interval in half.
Begin with an interval covering the whole array.
If the value of the search key is less than the item in the middle of the interval, narrow the interval to the lower half.
Otherwise narrow it to the upper half. Repeatedly check until the value is found or the interval is empty.
bSearch();

ref: http://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
An element in a sorted array can be found in O(log n) time via binary search.
But suppose we rotate an ascending order sorted array at some pivot unknown to you beforehand.
So for instance, 1 2 3 4 5 might become 3 4 5 1 2.
Devise a way to find an element in the rotated array in O(log n) time.
brSearch();
*/

/* a[]: sorted by ASC ordering */
int bSearch( int a[], int begin, int end, int value )
{
    int mid = (begin+end)/2;

    if( begin > end )
    {
        return -1;
    }

    if( value == a[mid] )
    {
        return mid;
    }

    if( value < a[mid] )
    {
        return bSearch( a, begin, mid-1, value );
    }
    else
    {
        return bSearch( a, mid+1, end, value );
    }
}

int findPivot( int a[], int begin, int end )
{
    int mid = 0;

    if( begin > end )
        return -1;
    if( begin == end )
        return begin;

    mid = begin + (end-begin)/2;

    if( mid+1 <= end && a[mid] > a[mid+1] )
    {
        return mid;
    }

    if( mid-1 >= begin && a[mid] < a[mid-1] )
    {
        return mid-1;
    }


    if( a[begin] >= a[mid] )
        return findPivot( a, begin, mid-1 );

    return findPivot( a, mid+1, end );

}

int brSearch( int a[], int begin, int end, int value )
{
    int pivot;

    pivot = findPivot( a, begin, end );

    if( pivot == -1 )
    {
        return bSearch( a, begin, end, value );
    }

    if( a[pivot] == value )
        return pivot;

    if( a[0] <= value )
        return bSearch( a, 0, pivot-1, value );

    return bSearch( a, pivot+1, end, value );
}


int brSearch2( int a[], int begin, int end, int value )
{
    int mid = 0;

    if( begin > end )
        return;

    mid = (begin+end)/2;

    if( a[mid] == value )
        return mid;

    /* if sorted from begin to mid */
    if( a[begin] <= a[mid] )
    {
        if( value >= a[begin] && value <= a[mid] )
        {
            return brSearch2( a, begin, mid-1, value );
        }

        /* from mid to end, maybe not sorted */
        return brSearch2( a, mid+1, end, value );
    }

    /* from mid to end, must be sorted */
    if( value >= a[mid] && value <= a[end] )
    {
        return brSearch2( a, mid+1, end, value );
    }

    /* from begin to mid is not sorted */
    return brSearch2( a, begin, mid-1, value );
}

void main( void )
{
    int a[] = { 1,2,3,4,5,6,7,8,9,10 };
    int n = sizeof( a ) / sizeof( a[0] );

    //printf("bsearch index: %d\n", bSearch( a, 0, n-1, 1 ) );

    int b[] = { 3,4,5,6,7,1,2 };
    printf("findPivot:%d\n", findPivot( b, 0, 6 ) );
    printf("brSearch: %d\n", brSearch( b, 0, 6, 7 ) );
    printf( "brSearch2: %d\n", brSearch2( b, 0, 6, 1 ) );
}
