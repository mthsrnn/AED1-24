#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * link da submissão: https://leetcode.com/problems/lemonade-change/submissions/1295953778/
 * eu adicionei uma main pro código por conveniência, para conseguir compilar
 * fora do leetcode. NÃO COPIAR PARA DENTRO DO LEETCODE se for testar assim.
*/


bool lemonadeChange ( int* bills, int billsSize ) {
    int i;
    int fiveDollars = 0, tenDollars = 0;

    for ( i = 0; i < billsSize; i++ ) {
        if ( bills[i] == 5 ) {
            fiveDollars++;
        }

        if ( bills[i] == 10 ) {
            tenDollars++;

            if ( fiveDollars < 1 ) {
                return false;
            }

            fiveDollars--;
        }

        if ( bills[i] == 20 ) {
            if ( tenDollars > 0 ) {
                if ( fiveDollars > 0 ) {
                    fiveDollars--;
                    tenDollars--;
                    continue;
                }
            }

            if ( fiveDollars > 2 ) {
                fiveDollars -= 3;
                continue;
            }

            return false;
        }
    }

    return true;
}

int main ( void ) {
    int bills[5] = { 5, 5, 10, 10, 20 };

    lemonadeChange ( bills, 5 ) ? puts ( "True" ) : puts ( "False" );

    return 0;
}
