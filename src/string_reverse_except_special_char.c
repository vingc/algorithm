/************************************************
* creator: vingc zhang
* time: 2017.03.24
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Given a string, that contains special character together with alphabets (¡®a¡¯ to ¡®z¡¯ and ¡®A¡¯ to ¡®Z¡¯),
reverse the string in a way that special characters are not affected.

Examples:

Input:   str = "a,b$c"
Output:  str = "c,b$a"
Note that $ and , are not moved anywhere.
Only subsequence "abc" is reversed

Input:   str = "Ab,c,de!$"
Output:  str = "ed,c,bA!$"
*/

#define true     1
#define false    0

#define MAX_LEN  100

int isAlphabet( char  ch )
{
    if( ( ch >= 'a' && ch <= 'z' ) ||
        ( ch >= 'A' && ch <= 'Z' ) )
    {
        return true;
    }

    return false;
}

void reverseExSpec( char * str )
{
    int strLen = strlen( str );
    int i,j;
    char tmp;

    i = 0;
    j = strLen - 1;
    while( i < j )
    {
        /* swap the char and skip the special char */
        if( ! isAlphabet( str[i] ) )
        {
            i++; //skip special
        }
        else if( ! isAlphabet( str[j] ) )
        {
            j--; //skip special
        }
        else
        {
            //swap
            tmp = str[j];
            str[j] = str[i];
            str[i] = tmp;
            //move on
            i++;
            j--;
        }
    }

    printf( "rev: %s\n", str );
    return;
}

void main( void )
{
    char str[ MAX_LEN ];
    //snprintf( str, MAX_LEN, "%s", "a,b$c" );
    snprintf( str, MAX_LEN, "%s", "Ab,c,de!$" );
    reverseExSpec( str );
}
