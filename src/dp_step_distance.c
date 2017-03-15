/************************************************
* creator: vingc zhang
* time: 2017.03.15
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/count-number-of-ways-to-cover-a-distance/
Given a distance ¡®dist, count total number of ways to cover the distance with 1, 2 and 3 steps.

Examples:

Input:  n = 3
Output: 4
Below are the four ways
 1 step + 1 step + 1 step
 1 step + 2 step
 2 step + 1 step
 3 step

Input:  n = 4
Output: 7

optimal substructure: let s[n] to be the number of all ways to cover the n steps.
s[n] = s[n-1]+s[n-2]+s[n-3], sum of the numbers of ways with last step is 1 or 2 or 3.
*/

#define MAX   20
int ways( int n )
{
    int sum[MAX]; // keep track the numbers of ways to cover the i distance.

    int i = 0;

    for( i = 0; i <= n; i++ )
        sum[i] = 0;

    sum[0] = 1;
    //sum[1] = 1;
    //sum[2] = 2;
    for( i = 1; i <= n; i++ )
    {
        sum[i] += sum[i-1];
        if( i >= 2 )
        {
            sum[i] += sum[i-2];
        }
        if( i >= 3 )
        {
            sum[i] += sum[i-3];
        }
    }

    return sum[n];
}

void main( void )
{
    printf("3:%d, 4:%d, 5:%d\n", ways(3), ways(4), ways(5) );
}
