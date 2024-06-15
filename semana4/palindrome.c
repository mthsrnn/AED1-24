#include <stdbool.h>
#include <stdio.h>

bool isPalindrome ( int x ) {
    if ( x < 0 ) { return false; }

    unsigned int number = x, reversed = 0;

    while ( number > 0 ) {
        reversed = ( reversed * 10 ) + ( number % 10 );
        number /= 10;
    }

    return x == reversed ? true : false;

}

int main ( void ) {
    isPalindrome ( 121 ) ? printf ( "True\n" ) : printf ( "False\n" );
    printf ( "deu!" );
    return 0;
}
