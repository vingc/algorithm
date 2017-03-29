/************************************************
* creator: vingc zhang
* time: 2017.03.29
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given an unsorted array of nonnegative integers, find a continous subarray which adds to a given number.

Examples:

Input: arr[] = {1, 4, 20, 3, 10, 5}, sum = 33
Ouptut: Sum found between indexes 2 and 4

Input: arr[] = {1, 4, 0, 0, 3, 10, 5}, sum = 7
Ouptut: Sum found between indexes 1 and 4

Input: arr[] = {1, 4}, sum = 0
Output: No subarray found
*/

int subArraySum( int a[], int n, int sum )
{
    int i;
    int curSum = 0;
    int start = 0;

    /* Add elements one by one to curr_sum and if the curr_sum exceeds the
       sum, then remove starting element */
    for( i = 0; i < n; i++ )
    {
        while( curSum > sum && start <= i - 1 )
        {
            curSum -= a[start];
            start++;
        }

        if( curSum == sum )
        {
            printf( "find subarray: %d-%d\n", start, i-1 );
            return 1;
        }

        curSum += a[i];
    }

    return 0;
}

void main( void )
{
    int arr[] = {15, 2, 4, 8, 9, 5, 10, 23};
    int n = sizeof(arr)/sizeof(arr[0]);
    int sum = 23;
    subArraySum(arr, n, sum);

}
