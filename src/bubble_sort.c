/************************************************
* creator: vingc zhang
* time: 2017.03.16
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ASC order */
void bubbleSort( int a[], int n )
{
    int i = 0;
    int j = 0;
    int tmp,swapFlag;

    for( i = 0; i < n-1; i++ )
    {
        swapFlag = 0;
        for( j = 0; j < n-i-1; j++ )
        {
            if( a[j] > a[j+1] )
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
                swapFlag = 1;
            }
        }

        if( swapFlag == 0 )
        {
            //already ordered
            break;
        }
    }


}

/* ASC order */
void selectSort( int a[], int n )
{
    int i,j,k,tmp;

    for( i = 0; i < n-1; i++ )
    {
        k = i;

        /* find the smallest */
        for( j = i+1; j < n; j++ )
        {
            if( a[j] < a[k] )
            {
                k = j;
            }
        }

        /*swap the i and k*/
        if( k != i )
        {
            tmp = a[i];
            a[i] = a[k];
            a[k] = tmp;
        }
    }
}

void main( void )
{
    int a[] = { 4,1,6,2,7,5 };
    int n = sizeof( a ) / sizeof( a[0] );

    int i;

    //bubbleSort( a, n );
    selectSort( a, n );
    for( i = 0; i < n; i++ )
    {
        printf("%d ", a[i] );
    }
}
