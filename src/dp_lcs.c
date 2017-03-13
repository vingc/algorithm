/************************************************
* creator: vingc zhang
* time: 2017.03.13
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/
LCS Problem Statement: Given two sequences, find the length of longest subsequence present in both of them.
A subsequence is a sequence that appears in the same relative order,
but not necessarily contiguous. For example, ��abc��, ��abg��, ��bdf��, ��aeg��, ����acefg��, .. etc are subsequences of ��abcdefg��.
So a string of length n has 2^n different possible subsequences.

It is a classic computer science problem,
the basis of diff (a file comparison program that outputs the differences between two files),
and has applications in bioinformatics.

Examples:
LCS for input Sequences ��ABCDGH�� and ��AEDFHR�� is ��ADH�� of length 3.
LCS for input Sequences ��AGGTAB�� and ��GXTXAYB�� is ��GTAB�� of length 4.

1) Consider the input strings ��AGGTAB�� and ��GXTXAYB��. Last characters match for the strings. So length of LCS can be written as:
    L(��AGGTAB��, ��GXTXAYB��) = 1 + L(��AGGTA��, ��GXTXAY��)

2) Consider the input strings ��ABCDGH�� and ��AEDFHR. Last characters do not match for the strings. So length of LCS can be written as:
    L(��ABCDGH��, ��AEDFHR��) = MAX ( L(��ABCDG��, ��AEDFHR��), L(��ABCDGH��, ��AEDFH��) )
*/
/* Dynamic Programming C/C++ implementation of LCS problem */
//#include<bits/stdc++.h>

int max(int a, int b);

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs( char *X, char *Y, int m, int n )
{
   int L[m+1][n+1];
   int i, j;

   /* Following steps build L[m+1][n+1] in bottom up fashion. Note
      that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
   for (i=0; i<=m; i++)
   {
     for (j=0; j<=n; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;

       else if (X[i-1] == Y[j-1])
         L[i][j] = L[i-1][j-1] + 1;

       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }

   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
   return L[m][n];
}

/* Utility function to get max of 2 integers */
int max(int a, int b)
{
    return (a > b)? a : b;
}

/* Driver program to test above function */
int main()
{
  char X[] = "AGGTAB";
  char Y[] = "GXTXAYB";

  int m = strlen(X);
  int n = strlen(Y);

  printf("Length of LCS is %d\n", lcs( X, Y, m, n ) );

  return 0;
}
