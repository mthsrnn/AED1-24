#include <stdio.h>

int climbStairs ( int n ) {

    if ( n == 1 ) { return 1; }

    int a = 0, b = 1, c = 2;

    for ( int i = 0; i < n; i ++ ) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;

}

int main ( void ) {

    int saida = climbStairs ( 255 );
    printf ( "%d\n", saida );
    return 0;
}
