#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
*/
int maxSubArray(int* nums, int numsSize) {
    int i;
    int maxSum = nums[0],curSum = nums[0];
    int maxBegin = 0, maxEnd = 0;
    int curBegin = 0;

    for( i = 1; i < numsSize; i++ ) {
        curSum += nums[i];
        //drop the begin if it's negative.
        if( nums[curBegin] <= 0 ) {
            curSum -= nums[curBegin];
            curBegin++;
        }

        //drop all nums before if sum is less than 0 and less than cur num
        if( curSum <= nums[i] ) {
            curSum = nums[i];
            curBegin = i;
            maxBegin = i;
        }

        //check maxSum
        if( curSum > maxSum ) {
            maxSum = curSum;
            maxEnd = i;
        }
    }

    printf( "%d-%d\n", nums[maxBegin], nums[maxEnd] );
    return maxSum;
}

/*
his problem was discussed by Jon Bentley (Sep. 1984 Vol. 27 No. 9 Communications of the ACM P885)

the paragraph below was copied from his paper (with a little modifications)

algorithm that operates on arrays: it starts at the left end (element A[1]) and scans through to the right end (element A[n]), keeping track of the maximum sum subvector seen so far. The maximum is initially A[0]. Suppose we've solved the problem for A[1 .. i - 1]; how can we extend that to A[1 .. i]? The maximum
sum in the first I elements is either the maximum sum in the first i - 1 elements (which we'll call MaxSoFar), or it is that of a subvector that ends in position i (which we'll call MaxEndingHere).

MaxEndingHere is either A[i] plus the previous MaxEndingHere, or just A[i], whichever is larger.

public static int maxSubArray(int[] A) {
    int maxSoFar=A[0], maxEndingHere=A[0];
    for (int i=1;i<A.length;++i){
    	maxEndingHere= Math.max(maxEndingHere+A[i],A[i]);
    	maxSoFar=Math.max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}
*/
int main( void ) {

    int nums[] = {-2,1,-3,4,-1,2,1,-5,4};
    int size = sizeof( nums ) / sizeof( int );
    printf( "maxSum:%d\n", maxSubArray( nums, size ) );
}
