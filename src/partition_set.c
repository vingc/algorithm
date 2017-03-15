/************************************************
* creator: vingc zhang
* time: 2017.03.13
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
Given a set of integers, the task is to divide it into two sets S1 and S2 such that the absolute difference between their sums is minimum.

If there is a set S with n elements, then if we assume Subset1 has m elements, Subset2 must have n-m elements and the value of abs(sum(Subset1) ¨C sum(Subset2)) should be minimum.

Example:

Input:  arr[] = {1, 6, 11, 5}
Output: 1
Explanation:
Subset1 = {1, 5, 6}, sum of Subset1 = 12
Subset2 = {11}, sum of Subset2 = 11
*/
// A Recursive C program to solve minimum sum partition
// problem.

int min( int x, int y )
{
    if( x < y )
        return x;
    else
        return y;
}

// Function to find the minimum sum
int findMinRec(int arr[], int i, int sumCalculated, int sumTotal)
{
    // If we have reached last element.  Sum of one
    // subset is sumCalculated, sum of other subset is
    // sumTotal-sumCalculated.  Return absolute difference
    // of two sums.
    if (i==0)
        return abs((sumTotal-sumCalculated) - sumCalculated);


    // For every item arr[i], we have two choices
    // (1) We do not include it first set
    // (2) We include it in first set
    // We return minimum of two choices
    return min(findMinRec(arr, i-1, sumCalculated+arr[i-1], sumTotal),
               findMinRec(arr, i-1, sumCalculated, sumTotal));
}

// Returns minimum possible difference between sums
// of two subsets
int findMin(int arr[], int n)
{
    // Compute total sum of elements
    int sumTotal = 0;
    for (int i=0; i<n; i++)
        sumTotal += arr[i];

    // Compute result using recursive function
    return findMinRec(arr, n, 0, sumTotal);
}

// Driver program to test above function
int main( void )
{
    int arr[] = {3, 1, 4, 2, 2, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    printf(" The minimum difference between two sets is %d\n", findMin(arr, n) );
    return 0;
}
