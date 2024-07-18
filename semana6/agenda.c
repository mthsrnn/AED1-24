#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void ImprimeMenu( void );

int main( void ) {
	void *pBuffer;

	ImprimeMenu();

	return EXIT_SUCCESS;
}

void ImprimeMenu( void ) {
	puts( "Escolha a operacao:\n"
	      "1 - Adiciona nome\n"
	      "2 - Remove nome\n"
	      "3 - Lista os nomes\n"
	      "4 - Sair" );
}
