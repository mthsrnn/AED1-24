#include <stdio.h>
#include <stdlib.h>

void doubleQuicksort( int *array, int *array2, int inicio, int fim ) {
	if( inicio >= fim )
		return;

	// objetivo: ordenar profit e fazer as mesmas trocas em difficulty (pra manter
	// a relação em i = job)

	int temp = array[inicio];
	int temp2 = array2[inicio];
	int i = inicio, k = fim;

	while( k > i ) {
		for( k; array[k] <= temp && k > i; k-- ); // procura elemento no array da direita menor que o pivot
		array[i] = array[k]; // troca
		array[k] = temp;
		array2[i] = array2[k];
		array2[k] = temp2;

		for( i; array[i] >= temp && i < k; i++ ); // procura elemento no array da esquerda maior que o pivot
		array[k] = array[i]; // troca
		array[i] = temp;
		array2[k] = array2[i];
		array2[i] = temp2;
	}

	doubleQuicksort( array, array2, inicio, i - 1 );
	doubleQuicksort( array, array2, k + 1, fim );
}

int maxProfitAssignment( int *difficulty, int difficultySize, int *profit,
                         int profitSize, int *worker, int workerSize ) {

	int lucro = 0;
	doubleQuicksort( profit, difficulty, 0, profitSize - 1 );

	for( int i = 0; i < workerSize; i++ ) {
		for( int j = 0; j < profitSize; j++ ) {
			if( worker[i] >= difficulty[j] ) {
				lucro += profit[j];
				break;
			}
		}
	}

	return lucro;
}

int main( void ) {
    int diff[] = {2, 4, 6, 8, 10};
    int profit[] = {10,20,30,40,50};
    int worker[] = {4, 5, 6, 7};
    
    printf("%d\n", maxProfitAssignment(diff, 5, profit, 5, worker, 4));

	return EXIT_SUCCESS;
}
