/************************************************
* creator: vingc zhang
* time: 2017.03.18
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/*
ref: http://www.geeksforgeeks.org/kth-smallestlargest-element-unsorted-array/
Given an array and a number k where k is smaller than size of array, we need to find the k¡¯th smallest element in the given array. It is given that ll array elements are distinct.

Examples:

Input: arr[] = {7, 10, 4, 3, 20, 15}
       k = 3
Output: 7

Input: arr[] = {7, 10, 4, 3, 20, 15}
       k = 4
Output: 10
*/

void swap( int * src, int * dst )
{
    int tmp = *dst;
    *dst = *src;
    *src = tmp;
}

int partition( int a[], int begin, int end )
{
    int mid = ( begin + end ) / 2;

    if( begin > end )
    {
        return -1;
    }

    swap( &a[mid], &a[end] );

    int i = begin - 1;
    int j = begin;

    while( j < end )
    {
        if( a[j] <= a[end] )
        {
            i++;
            swap( &a[i], &a[j] );
        }

        j++;
    }

    i++;
    swap( &a[i], &a[end] );

    return i;
}

/* find k'th smallest element in given array */
int quikSearch( int a[], int begin, int end, int k )
{
    int p;


    /* if k is smaller than the number of elements in array */
    if( k > 0 && k <= end - begin + 1 )
    {
        p = partition( a, begin, end );

        if ( p == -1 )
        {
            printf("p==-1\n");
            return -1;
        }

        /* if the number in left half is equal to k - 1 */
        if( p - begin == k - 1 )
            return p;

        /* check if the k'th is in right half array */
        if( k - 1 > p - begin )
        {
            return quikSearch( a, p+1, end, k-(p-begin+1) );
        }

        /* else the k'th is in left half array */
        return quikSearch( a, begin, p-1, k );
    }

    return -1;
}

void main( void )
{
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof( arr ) / sizeof( arr[0] );
    int k = 3;

    int idx = quikSearch( arr, 0, n-1, k );

    if( idx == -1 )
    {
        return;
    }consecutive

    printf( "%d'th smallest: %d\n", k, arr[ idx ] );
}
