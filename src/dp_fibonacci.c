/************************************************
* creator: vingc zhang
* time: 2017.03.13
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ref: http://www.geeksforgeeks.org/dynamic-programming-set-1/
Dynamic Programming is an algorithmic paradigm that solves a given complex problem
by breaking it into subproblems and stores the results of subproblems
to avoid computing the same results again.
Following are the two main properties of a problem that suggest that the given problem
can be solved using Dynamic programming.
1) Overlapping Subproblems
2) Optimal Substructure

Like Divide and Conquer,
Dynamic Programming combines solutions to sub-problems.
Dynamic Programming is mainly used when solutions of same subproblems are needed again and again.
In dynamic programming, computed solutions to subproblems are stored in a table so that
these don¡¯t have to recomputed.
So Dynamic Programming is not useful when there are no common (overlapping) subproblems because
there is no point storing the solutions if they are not needed again.
For example, Binary Search doesn¡¯t have common subproblems.
If we take example of following recursive program for Fibonacci Numbers,
there are many subproblems which are solved again and again.
*/
/* simple recursive program for Fibonacci numbers */
int fib(int n)
{
   if ( n <= 1 )
      return n;
   return fib(n-1) + fib(n-2);
}

/*
There are following two different ways to store the values so that these values can be reused:
a) Memoization (Top Down)
b) Tabulation (Bottom Up)

Both Tabulated and Memoized store the solutions of subproblems.
In Memoized version, table is filled on demand while in Tabulated version,
starting from the first entry, all entries are filled one by one.
Unlike the Tabulated version,
all entries of the lookup table are not necessarily filled in Memoized version.
*/
/* C/C++ program for Memoized version for nth Fibonacci number */
#include<stdio.h>
#define NIL -1
#define MAX 100

int lookup[MAX];

/* Function to initialize NIL values in lookup table */
void _initialize()
{
  int i;
  for (i = 0; i < MAX; i++)
    lookup[i] = NIL;
}

/* function for nth Fibonacci number */
int fib(int n)
{
   if (lookup[n] == NIL)
   {
      if (n <= 1)
         lookup[n] = n;
      else
         lookup[n] = fib(n-1) + fib(n-2);
   }

   return lookup[n];
}

/* C program for Tabulated version */
#include<stdio.h>
int fib(int n)
{
  int f[n+1];
  int i;
  f[0] = 0;   f[1] = 1;
  for (i = 2; i <= n; i++)
      f[i] = f[i-1] + f[i-2];

  return f[n];
}
