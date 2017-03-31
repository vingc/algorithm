/************************************************
* creator: vingc zhang
* time: 2017.03.31
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
ref: http://www.geeksforgeeks.org/median-of-two-sorted-arrays/

There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5

Method 1 (Simply count while Merging)
Method 2 (By comparing the medians of two arrays)
This method works by first getting medians of the two sorted arrays and then comparing them.

Let ar1 and ar2 be the input arrays, each size of array is n;

Algorithm:

1) Calculate the medians m1 and m2 of the input arrays ar1[]
   and ar2[] respectively.
2) If m1 and m2 both are equal then we are done.
     return m1 (or m2)
3) If m1 is greater than m2, then median is present in one
   of the below two subarrays.
    a)  From first element of ar1 to m1 (ar1[0...|_n/2_|])
    b)  From m2 to last element of ar2  (ar2[|_n/2_|...n-1])
4) If m2 is greater than m1, then median is present in one
   of the below two subarrays.
   a)  From m1 to last element of ar1  (ar1[|_n/2_|...n-1])
   b)  From first element of ar2 to m2 (ar2[0...|_n/2_|])
5) Repeat the above process until size of both the subarrays
   becomes 2.
6) If size of the two arrays is 2 then use below formula to get
  the median.
    Median = (max(ar1[0], ar2[0]) + min(ar1[1], ar2[1]))/2
*/

int min( int a, int b )
{
    if ( a < b )
        return a;
    else
        return b;
}

int getKth( int a[], int m, int b[], int n, int k )
{
    //let the m be the smaller
    if( m > n )
    {
        return getKth( b, n, a, m, k );
    }

    //then check if smaller one reach the zero
    if( m == 0 )
        return b[k-1];

    //check if k reach the 1th
    if( k == 1 )
    {
        return min( a[0], b[0] );
    }

    int ma = min( m, k/2 );
    int mb = min( n, k/2 );

    //discard the smallest k/2 items
    if( a[ma-1] < b[mb-1] )
    {
        return getKth( a+ma, m-ma, b, n, k-ma );
    }
    else
    {
        return getKth( a, m, b+mb, n-mb, k-mb );
    }
}

double findMedian( int a[], int m, int b[], int n )
{
    int l = ( m + n + 1 ) / 2;
    int r = ( m + n + 2 ) / 2;

    return( getKth( a, m, b, n, l ) + getKth( a, m, b, n, r ) ) / 2.0;
}

void main( void )
{
    int a[] = {1,3,5};
    int b[] = {2,4,6};

    printf( "%f\n", findMedian( a, 3, b ,3 ) );

    int c[] = {1,3,5};
    int d[] = {4,6};
    printf( "%f\n", findMedian( c, 3, d ,2 ) );

}
