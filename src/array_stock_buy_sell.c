/************************************************
* creator: vingc zhang
* time: 2017.03.29
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
The cost of a stock on each day is given in an array,
find the max profit that you can make by buying and selling in those days.
For example, if the given array is {100, 180, 260, 310, 40, 535, 695},
the maximum profit can earned by buying on day 0, selling on day 3.
Again buy on day 4 and sell on day 6.
If the given array of prices is sorted in decreasing order,
then profit cannot be earned at all.
*/


void findBuySellDay( int a[], int n )
{
    int i, buy;

    buy = -1;

    for( i = 0; i < n-1; i++ )
    {
        /* check the ordering */
        if( a[i] > a[i+1] )
        {
            if( buy >= 0 )
            {
                //already buy,then sell before desc
                printf( "buy:%d,sell:%d\n", buy, i );
                buy = -1;
            }
        }
        else if( a[i] < a[i+1] )
        {
            if( buy == -1 )
            {
                //buy before incre
                buy = i;
            }
        }
    }

    //end case
    if( i == n-1 && buy >= 0 )
    {
        //already buy,then sell before desc
        printf( "buy:%d,sell:%d\n", buy, i );
    }
    return;
}

void main( void )
{
    int price[] = {100, 180, 260, 310, 40, 535, 695};
    int n = sizeof(price)/sizeof(price[0]);

    // fucntion call
    //findBuySellDay(price, n);
    int a[] = {0,0,1,1,0,1,0,1,1,0};
    fun( a, 0, 10 );
}


void fun( int a[], int begin, int end )
{
    int i;

    for( i = begin; i < end; i++ )
    {
        if( a[i] == 1 )
        {
            fun( a, i+1, end );
            a[i] = 0;
            fun( a, i+1, end );
            a[i] = 1;//restore
            break;
        }
    }

    if( i == end  )
    {
        //print array
        for( i = 0; i < end; i++ )
        {
            printf( "%d ", a[i] );
        }
        printf( "\n" );
    }
}


