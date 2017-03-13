/************************************************
* creator: vingc zhang
* time: 2017.03.13
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX  20

/*
The Longest Increasing Subsequence (LIS) problem is to find the length of the longest
subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order.
For example, the length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is {10, 22, 33, 50, 60, 80}.
L(i) = 1 + max( L(j) ) where 0 < j < i and arr[j] < arr[i]; or
L(i) = 1, if no such j exists.
*/
/*
memorized method:
a[]: the given array of length n+1;
list[]: the array to store LIS length no of i which 0<=i<n and a[i] is end node of LIS */
void lis( int a[], int n, int * res )
{
    int i = 0;

    for( i = 0; i < n; i++ )
    {
        if( res[i] == 0 )
        {
            res[i] = 1;
            lis( a, i, res );
        }

        if( a[i] < a[n] && res[i] + 1 > res[n] )
        {
            //a[i]...a[n-1], a longer LIS,add one no.
            res[n] = res[i] + 1;
        }
    }

}

/* Driver program to test above function */
int main()
{
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
    int n = sizeof(arr)/sizeof(arr[0]);
    int res[MAX]={0};
    int cur_max_list = 0,i;

    lis( arr, n-1, res );

    for( i = 0; i < n; i++ )
    {
        if ( cur_max_list < res[i] )
            cur_max_list = res[i];
    }

    printf("Length of lis is %d\n", cur_max_list );
    return 0;
}

#if 0
tabulated method
/* lis() returns the length of the longest increasing
  subsequence in arr[] of size n */
int lis( int arr[], int n )
{
    int *lis, i, j, max = 0;
    lis = (int*) malloc ( sizeof( int ) * n );

    /* Initialize LIS values for all indexes */
    for (i = 0; i < n; i++ )
        lis[i] = 1;

    /* Compute optimized LIS values in bottom up manner */
    for (i = 1; i < n; i++ )
        for (j = 0; j < i; j++ )
            if ( arr[i] > arr[j] && lis[i] < lis[j] + 1)
                lis[i] = lis[j] + 1;

    /* Pick maximum of all LIS values */
    for (i = 0; i < n; i++ )
        if (max < lis[i])
            max = lis[i];

    /* Free memory to avoid memory leak */
    free(lis);

    return max;
}
#endif // 0
