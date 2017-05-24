#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:

[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/

#define null 0

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize) {

    int resSize = matrixRowSize * matrixColSize;
    int * res = (int *) malloc( sizeof( int ) * resSize );
    if( res == null ) {
        return null;
    }

    int x = 0, y = 0; //index in matrix;

    int * flag = (int *) malloc( sizeof( int ) * resSize );
    memset( flag, 0, sizeof( int ) * resSize );

    int i;
    int direct = 0; //0-right,1-down,2-left,3-up

    for( i = 0; i < resSize; i++ ) {
        res[i] =  (*matrix)[x*matrixColSize+y];
        flag[x*matrixColSize+y] = 1;
        //get next x & y

        {
            //first, right direction
            if( direct == 0 ) { //right
                if( y+1 < matrixColSize && flag[x*matrixColSize+y+1] == 0 ) {
                    y = y+1;
                    continue;
                }

                direct = 1;
            }

            if( direct == 1 ) {
                //second, down direction
                if( x+1 < matrixRowSize && flag[(x+1)*matrixColSize+y] == 0 ) {
                    x = x+1;
                    continue;
                }

                direct = 2;
            }

            if( direct == 2 ) {

                //third, left direction
                if( y-1 >= 0 && flag[x*matrixColSize+y-1] == 0 ) {
                    y = y-1;
                    continue;
                }

                direct = 3;
            }

            if( direct == 3 ) {

                //fourth, up direction
                if( x-1 >=0 && flag[(x-1)*matrixColSize+y] == 0 ) {
                    x = x-1;
                    continue;
                }

                direct = 0;

                if( y+1 < matrixColSize && flag[x*matrixColSize+y+1] == 0 ) {
                    y = y+1;
                    continue;
                }

                break;
            }

        }

    }

    return res;
}

int* spiralOrder2(int** matrix, int matrixRowSize, int matrixColSize) {

    int resSize = matrixRowSize * matrixColSize;
    int * res = (int *) malloc( sizeof( int ) * resSize );
    if( res == null ) {
        return null;
    }

    int x = 0, y = 0; //index in matrix;
    int right = matrixColSize - 1, left = 0, top = 0, bottom = matrixRowSize - 1;
    int k = 0;

    while( 1 ) {
        //top
        for( int i = left; i <= right; i++ ) {
            res[k++] = (*matrix)[top*matrixColSize + i];
        }
        ++top;
        if( top > bottom ) break;

        //right
        for( int i = top; i <= bottom; i++ ) {
            res[k++] = (*matrix)[i*matrixColSize + right];
        }
        --right;
        if( right < left ) break;

        //bottom
        for( int i = right; i >= left; i-- ) {
            res[k++] = (*matrix)[bottom*matrixColSize + i];
        }
        --bottom;
        if( bottom > top ) break;

        //left
        for( int i = bottom; i >= top; i-- ) {
            res[k++] = (*matrix)[i*matrixColSize + left];
        }
        ++left;
        if( left > right ) break;
    }

    return res;

}

int main( void ) {
    int nums[3][2] = { {2,5}, {8,4}, {0,-1} };


    int* num = (int*)malloc(sizeof(int)*6);
    memcpy( num, nums,sizeof(int)*6);

    int * res = spiralOrder2( &num, 3, 2 );
    if( res == null ) {
        return -1;
    }

    int i;
    for( i = 0; i < 6; i++ ) {
        printf( "%d,", res[i] );
    }

    return 0;
}
