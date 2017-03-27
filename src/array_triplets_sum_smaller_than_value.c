/************************************************
* creator: vingc zhang
* time: 2017.03.27
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/count-triplets-with-sum-smaller-that-a-given-value/
Count triplets with sum smaller than a given value
Given an array of distinct integers and a sum value. Find count of triplets with sum smaller than given sum value. Expected Time Complexity is O(n2).

Examples:

Input : arr[] = {-2, 0, 1, 3}
        sum = 2.
Output : 2
Explanation :  Below are triplets with sum less than 2
               (-2, 0, 1) and (-2, 0, 3)

Input : arr[] = {5, 1, 3, 4, 7}
        sum = 12.
Output : 4
Explanation :  Below are triplets with sum less than 4
               (1, 3, 4), (1, 3, 5), (1, 3, 7) and
               (1, 4, 5)
1. A Simple Solution is to run three loops to consider all triplets one by one.
   For every triplet, compare the sums and increment count if triplet sum is smaller than given sum.
2. An Efficient Solution can count triplets in O(n2) by sorting the array first,
   and then using method of "array_pair_sum_equal_value.c" in a loop.
    1) Sort the input array in increasing order.
    2) Initialize result as 0.
    3) Run a loop from i = 0 to n-2.  An iteration of this loop finds all
       triplets with arr[i] as first element.
       a) Initialize other two elements as corner elements of subarray
           arr[i+1..n-1], i.e., j = i+1 and k = n-1
       b) Move j and k toward each other until they meet, i.e., while (j < k)
            (i) if (arr[i] + arr[j] + arr[k] >= sum), then do k--

            // Else for current i and j, there can (k-j) possible third elements
            // that satisfy the constraint.
            (ii) Else Do ans += (k - j) followed by j++
*/

int partition( int a[], int begin, int end )
{
    int mid = end;
    int i = begin - 1;
    int j = begin;
    int tmp;

    while( j < end )
    {
        if( a[j] < a[mid] )
        {
            i++;
            tmp = a[j];
            a[j] = a[i];
            a[i] = tmp;
        }

        j++;
    }

    i++;
    tmp = a[mid];
    a[mid] = a[i];
    a[i] = tmp;

    return i;
}

void quikSort( int a[], int begin, int end )
{
    if( begin >= end )
    {
        return;
    }

    int p = partition( a, begin, end );

    quikSort( a, begin, p - 1 );
    quikSort( a, p + 1, end );

    return;
}


int cntTriplets( int a[], int n, int sum )
{
    quikSort( a, 0, n - 1 );

    int i,j,k,cnt;

    cnt = 0;
    for( i = 0; i < n - 2; i++ )
    {
        //a[i] as the first item of triplets.
        j = i + 1;
        k = n - 1;
        while( j < k )
        {
            //a[j] and a[k] as the second and third item of triplets respectively.
            if( a[i] + a[j] + a[k] >= sum )
            {
                k--; //move the left forward, take the smaller value as the third item.
            }
            else
            {
                //there are k-j third items making the sum of triplets smaller than sum
                cnt += k - j;
                j++; //move the right forward, take the bigger value as the second item.
            }
        }
    }

    return cnt;
}

void main( void )
{
    int arr[] = {5, 1, 3, 4, 7};
    int n = sizeof arr / sizeof arr[0];
    int sum = 12;

    printf( "cnt:%d\n", cntTriplets( arr, n, 12 ) );
}
