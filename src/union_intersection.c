/************************************************
* creator: vingc zhang
* time: 2017.03.12
*************************************************/

/*
ref: http://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/
Given two sorted arrays, find their union and intersection.

For example, if the input arrays are:
arr1[] = {1, 3, 4, 5, 7}
arr2[] = {2, 3, 5, 6}
Then your program should print Union as {1, 2, 3, 4, 5, 6, 7} and Intersection as {3, 5}.

Algorithm Union(arr1[], arr2[]): Time Complexity: O(m+n)
For union of two arrays, follow the following merge procedure.
1) Use two index variables i and j, initial values i = 0, j = 0
2) If arr1[i] is smaller than arr2[j] then print arr1[i] and increment i.
3) If arr1[i] is greater than arr2[j] then print arr2[j] and increment j.
4) If both are same then print any of them and increment both i and j.
5) Print remaining elements of the larger array.



Algorithm Intersection(arr1[], arr2[]):  Time Complexity: O(m+n)
For Intersection of two arrays, print the element only if the element is present in both arrays.
1) Use two index variables i and j, initial values i = 0, j = 0
2) If arr1[i] is smaller than arr2[j] then increment i.
3) If arr1[i] is greater than arr2[j] then increment j.
4) If both are same then print any of them and increment both i and j.

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ref: http://www.geeksforgeeks.org/find-union-and-intersection-of-two-unsorted-arrays/
Method 1 (Naive)
Union:
1) Initialize union U as empty.
2) Copy all elements of first array to U.
3) Do following for every element x of second array:
бн..a) If x is not present in first array, then copy x to U.
4) Return U.

Intersection:
1) Initialize intersection I as empty.
2) Do following for every element x of first array
бн..a) If x is present in second array, then copy x to I.
4) Return I.

Time complexity of this method is O(mn) for both operations.
Here m and n are number of elements in arr1[] and arr2[] respectively.

Method 2 (Use Sorting)
1) Sort arr1[] and arr2[]. This step takes O(mLogm + nLogn) time.
2) Use O(m + n) algorithms to find union and intersection of two sorted arrays.

Overall time complexity of this method is O(mLogm + nLogn).

Method 3 (Use Sorting and Searching)
Union:
1) Initialize union U as empty.
2) Find smaller of m and n and sort the smaller array.
3) Copy the smaller array to U.
4) For every element x of larger array, do following
бнбн.b) Binary Search x in smaller array. If x is not present, then copy it to U.
5) Return U.

Intersection:
1) Initialize intersection I as empty.
2) Find smaller of m and n and sort the smaller array.
3) For every element x of larger array, do following
бнбн.b) Binary Search x in smaller array. If x is present, then copy it to I.
4) Return I.

Time complexity of this method is min(mLogm + nLogm, mLogn + nLogn) which can also be written as O((m+n)Logm, (m+n)Logn).
This approach works much better than the previous approach when difference between sizes of two arrays is significant.

*/
