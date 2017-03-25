/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
ref: http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/
lps[i] = the longest proper prefix of pat[0..i]
              which is also a suffix of pat[0..i].

A proper prefix is prefix with whole string not allowed.
For example, prefixes of ¡°ABC¡± are ¡°¡±, ¡°A¡±, ¡°AB¡± and ¡°ABC¡±.
Proper prefixes are ¡°¡±, ¡°A¡± and ¡°AB¡±.
Suffixes of the string are ¡°¡±, ¡°C¡±, ¡°BC¡± and ¡°ABC¡±.
*/

#define MAX_LEN  100

void initLpsArray( char * pat, int m, int * lps )
{
    int i,j;
    int len; //the length of last proper prefix

    len = 0;
    lps[0] = 0; //always 0

    i = 1;
    while( i < m )
    {
        if( pat[i] == pat[len] )
        {
            len++;
            lps[i] = len;  //length is index+1

            i++; //move on
        }
        else
        {
            if( len == 0 )
            {
                lps[i] = 0; //suffix don't have matched prefix
                i++; //move on
            }
            else
            {
                len = lps[len-1]; //similar to search pattern in string.
            }
        }
    }


    printf( "lps:" );
    for( i = 0; i < m; i++ )
    {
        printf( "%d, ", lps[i] );
    }
    printf( "\n" );
}

void searchKMP( char * str, char * pat )
{
    int m = strlen( pat );
    int n = strlen( str );

    if( n == 0 || m == 0 )
    {
        return;
    }

    int i,j;
    int lps[MAX_LEN];

    initLpsArray( pat, m, lps );

    i = 0;
    j = 0;
    while( i < n )
    {
        if( str[i] == pat[j] )
        {
            //move on
            i++;
            j++;

            if( j == m )
            {
                printf( "found index:%d\n", i - j );
                j = lps[j-1]; // skip lps[j-1] characters in pat,
            }
        }
        else
        {
            if( j !=  0 )
            {
                j = lps[j-1]; // skip lps[j-1] characters in pat,
            }
            else
            {
                //don't have same char in pat. move on
                i++;
            }
        }
    }
}

void main( void )
{
    char *txt = "ABABDABACDABABCABAB";
    char *pat = "ABABCABAB";
    searchKMP( txt, pat );
}
