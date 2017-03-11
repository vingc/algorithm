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