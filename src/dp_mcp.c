/************************************************
* creator: vingc zhang
* time: 2017.03.13
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/
Given a cost matrix cost[][] and a position (m, n) in cost[][],
write a function that returns cost of minimum cost path to reach (m, n) from (0, 0).
Each cell of the matrix represents a cost to traverse through that cell.
Total cost of a path to reach (m, n) is sum of all the costs on that path (including both source and destination).
You can only traverse down, right and diagonally lower cells from a given cell, i.e.,
from a given cell (i, j), cells (i+1, j), (i, j+1) and (i+1, j+1) can be traversed.
You may assume that all costs are positive integers.

optimal substructure: minCost(m,n) = min(minCost(m-1,n),minCost(m,n-1),minCost(m-1,n-1))+cost(m,n);
*/

#define  R  3
#define  C  3

int min( int x, int y, int z )
{
    if( x < y )
        return x < z ? x : z;
    else
        return y < z ? y : z;
}

int minCost( int cost[R][C], int m, int n )
{
    int mCost[R][C];
    int i = 0, j = 0;

    for( i = 0; i <= m; i++ )
    for( j = 0; j <= n; j++ )
    {
        /* */
        if( i == 0 && j == 0 )
        {
            mCost[i][j] = cost[i][j];
        }
        else if( i == 0 )
        {
            mCost[i][j] = mCost[i][j-1] + cost[i][j];
        }
        else if( j == 0 )
        {
            mCost[i][j] = mCost[i-1][j] + cost[i][j];
        }
        else
        {
            mCost[i][j] = min( mCost[i-1][j], mCost[i][j-1], mCost[i-1][j-1] ) + cost[i][j];
        }
    }

    return mCost[m][n];
}

void main( void )
{
    int cost[R][C] = { {1, 2, 3},
                       {4, 8, 2},
                       {1, 5, 3} };
   printf(" %d ", minCost(cost, 2, 2));
}
