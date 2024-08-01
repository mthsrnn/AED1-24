#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize) {
    int smallest = 201, outputSize = 0;
    int cmpOutput;
    char* output = (char *) calloc(200, sizeof(char));

    /* encontra o tamanho da menor palavra */
    for ( int i = 0; i < strsSize; i++ ) {
        if( strlen(strs[i]) < smallest ) {
            smallest = strlen(strs[i]);
        }
    }

    /* loop principal */
    for ( int i = 0; i < smallest; i++ ) { //para cada caractere
        for ( int j = 0; j < strsSize - 1; j++ ) { // de cada string (ate o tamahnho da menor)
            cmpOutput = strs[j][i] - strs[j+1][i]; // testa se os caracteres sao iguais (== 0)
            if ( cmpOutput ) 
                break; // para o loop se achar caracteres diferentes no mesmo indice
        }
        if ( cmpOutput == 0 ) {
            output[outputSize++] = strs[0][i]; //adiciona na string se forem todos iguais
        } else {
            return output; // se achar caracteres diferentes, retorna a string do jeito que tá
        }
    }
    return output; // vai retornar a string inteira (se não tiver nenhuma outra ou se todas foram iguais)
}

int main(void)
{
    int strsSize = 3;
    char* strs[] = {"c", "acc", "ccc"};
    char * saida = longestCommonPrefix(strs, strsSize);

    printf("%s", saida);
    free(saida);

    return EXIT_SUCCESS;
}
