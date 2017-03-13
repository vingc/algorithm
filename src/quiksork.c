#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quikSort( int * array, int begin, int end )
{
  int i = begin - 1;
  int j = begin;
  int med = end;
  int val;

	if( begin >= end )
	{
		return;
	}

	while( j < end )
	{
		if( array[ j ] <= array[ med ] )
		{
			++i;
			val = array[ i ];
			array[ i ] = array[ j ];
			array[ j ] = val;
		}

		++j;
	}
	++i;
	val = array[ i ];
	array[ i ] = array[ med ];
	array[ med ] = val;

	quikSort( array, begin, i-1 );
	quikSort( array, i+1, end );
	return;
}

void main( void )
{
  int i   = 0 ;
	int array[] = { 2,3,4,1,8,0,6,5,9,7 };
	quikSort( array, 0, 9 );

	for( i = 0; i < 10; i++ )
	{
		printf( "%d ", array[ i ] );
	}

	printf( "\n" );
	return;
}

/*

quikSort( int a[], int begin, int end )
{
	int idx = end;
	int i = begin - 1;
	int j = begin;

	if( begin >= end )
		return;

	while( j < end )
	{
		if( a[j] < a[idx] )
		{
			i++;
			swap(a[j],a[i]);
		}
		j++;
	}

  swap(a[i+1],a[idx]);

  quikSort(a,begin, i);
  quiksort(a,i+2,end);
}

//assume k is big enought. ASC ording
void mergeSort( int a[], int begin, int end, int tmp[k] )
{

	int mid = (begin+end)/2;

	if( begin >= end )
		return;

		mergeSort( a, begin, mid );
		mergeSort( a, mid + 1, end );

		{
			//merge
			int i = begin;
			int j = mid+1;
			int t = 0;

			while( i <= mid && j <= end )
			{
				if( a[i] < a[j] )
					tmp[t++] = a[i++];
				else if( a[i] >= a[j] )
					tmp[t++] = a[j++];
			}

			while( i <= mid )
				tmp[t++] = a[i++];
			while( j <= end )
			  tmp[t++] = a[j++];

			i = 0;
			j = begin;
			while( i < t )
				a[j++] = tmp[i++];
		}
}

//ASC order
void insertSort( int a[], int n )
{
	int i = 0;
	int j = 0;
	int value = 0;

	for( i = 1; i < n; i++ )
	{
		if( a[i] < a[i-1] )
		{
			value = a[i];
			j = i;

			while( j > 0 && value < a[j-1] )
			{
				a[j] = a[j-1];
				j--;
			}

			a[j] = value;
		}
	}
}
*/
