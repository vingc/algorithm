/************************************************
* creator: vingc zhang
* time: 2017.03.15
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given a set of non-negative integers, and a value sum, determine if there is a subset of the given set with sum equal to given sum.

Examples: set[] = {3, 34, 4, 12, 5, 2}, sum = 9
Output:  True  //There is a subset (4, 5) with sum 9.

The isSubsetSum problem can be divided into two subproblems
¡­a) Include the last element, recur for n = n-1, sum = sum ¨C set[n-1]
¡­b) Exclude the last element, recur for n = n-1.
If any of the above the above subproblems return true, then return true.

Following is the recursive formula for isSubsetSum() problem.

isSubsetSum(set, n, sum) = isSubsetSum(set, n-1, sum) ||
                           isSubsetSum(set, n-1, sum-set[n-1])
Base Cases:
isSubsetSum(set, n, sum) = false, if sum > 0 and n == 0
isSubsetSum(set, n, sum) = true, if sum == 0
*/

int isSubSetSum( int set[], int n, int sum )
{
    /* there is a subset which sum equal to the input number */
    if( sum == 0 )
    {
        return 1;
    }

    /* don't find the subset */
    if( n == 0 || sum < 0 )
    {
        return 0;
    }

    return isSubSetSum( set, n-1, sum - set[n-1] ) ||
           isSubSetSum( set, n-1, sum );
}

void main ( void )
{
    int set[]={3,4,5,16,17,9,20};
    int sum = 10;

    printf("is find the subset which sum is %d: %d\n", sum, isSubSetSum( set, 7, sum ) );
}
