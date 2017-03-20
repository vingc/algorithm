/************************************************
* creator: vingc zhang
* time: 2017.03.20
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://quiz.geeksforgeeks.org/given-sorted-array-number-x-find-pair-array-whose-sum-closest-x/
Given a sorted array and a number x, find the pair in array whose sum is closest to x
Given a sorted array and a number x, find a pair in array whose sum is closest to x.
Examples:
Input: arr[] = {10, 22, 28, 29, 30, 40}, x = 54
Output: 22 and 30

Input: arr[] = {1, 3, 4, 7, 10}, x = 15
Output: 4 and 10

1) Initialize a variable diff as infinite (Diff is used to store the
   difference between pair and x).  We need to find the minimum diff.
2) Initialize two index variables l and r in the given sorted array.
       (a) Initialize first to the leftmost index:  l = 0
       (b) Initialize second  the rightmost index:  r = n-1
3) Loop while l < r.
       (a) If  abs(arr[l] + arr[r] - sum) < diff  then
           update diff and result
       (b) Else if(arr[l] + arr[r] <  sum )  then l++
       (c) Else r--
*/

//a sorted by ASC array with size n
int pairSum( int a[], int n, int x )
{
    int l,r,diff;
    int pair1, pair2, sum;

    diff = 0x7FFFFFFF;
    l = 0; //smallest
    r = n-1; //biggest

    while( l < r )
    {
        sum = a[l] + a[r];
        if( abs( sum - x ) < diff )
        {
            pair1 = l;
            pair2 = r;
            diff = abs( sum - x );
        }

        if( sum > x )
        {
            //move to smaller item
            r--;
        }
        else
        {
            //move to bigger item
            l++;
        }
    }

    printf( " pair: %d, %d\n ", a[pair1], a[pair2] );
}

void main( void )
{
    int a[] = { 11,22,33,44,55,66,77,99 };
    int x = 88;
    int n = sizeof( a ) / sizeof( a[0] );

    pairSum( a, n, x );
}
