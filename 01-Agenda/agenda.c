#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Atalhos para as variáveis fixas alocadas no buffer
#define VAR_I                        0
#define VAR_J                        1
#define OPT                          2
#define TAM_BUFFER                   3
#define TAM_STR                      4
#define TAM_HEAP                     5
#define TAM_LISTA                    6
#define INT_OFFSET     sizeof(int) * 7
#define PTR_OFFSET  sizeof(void *) * 3
#define PTR_FIRST                    0
#define PTR_LAST                     1
#define PTR_NODO                     2
#define PTR_PROXIMO                  1
#define PTR_ANTERIOR                 0

void ImprimeMenu( void );
void *AlocaBuffer( void );
void *ExpandeBufferString ( void * pBuffer );
void *LePessoa ( void * pBuffer);
void * CriaNodo ( void *pBuffer );
void ImprimeNodo ( void * nodo );

int main( void ) {

	void *pBuffer = AlocaBuffer();

	do {

		ImprimeMenu();

		scanf( "%d", ( int * )pBuffer + OPT );

		getchar();

		switch( ( ( int * )pBuffer )[OPT] ) {
		case 1:

            pBuffer = LePessoa(pBuffer);       
	        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = CriaNodo(pBuffer);
            
			break;

		case 2:
			puts( "Insira o nome para remover:" );
			break;

		case 3:
			ImprimeNodo(( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO]);
			break;

		case 4:
            free(pBuffer);
			return EXIT_SUCCESS;
			break;

		default:
			puts( "Opcao invalida!" );
			break;
		}

	} while( ( ( int * )pBuffer )[OPT] );

	free( pBuffer );
	return EXIT_SUCCESS;
}

void ImprimeMenu( void ) {
	puts( "Escolha a operacao:\n"
	      "1 - Adicionar pessoa\n"
	      "2 - Remover pessoa\n"
	      "3 - Buscar pessoa\n"
	      "4 - Sair" );
}

void *AlocaBuffer( void ) {
	void *pBuffer = malloc( ( 7 * sizeof( int ) ) + ( 3 * sizeof( void * ) ) +
	                        ( 21 * sizeof( char ) ) + sizeof( void * ) );

    if ( pBuffer == NULL) {
        puts("Erro de alocação de memória.");
        exit(-1);
    }

	( ( int * )pBuffer )[VAR_I] = 0;
	( ( int * )pBuffer )[VAR_J] = 0;
	( ( int * )pBuffer )[OPT] = 0;
	( ( int * )pBuffer )[TAM_BUFFER] = ( int )( ( 7 * sizeof( int ) ) + ( 3 * sizeof( void * ) ) + ( 21 * sizeof( char ) ) + sizeof( void * ) );
	( ( char * )pBuffer + INT_OFFSET + PTR_OFFSET + 1)[20] = '\0'; // nota para o futuro: grandes chances dessa linha quebrar a heap lá pra frente
	( ( int * )pBuffer )[TAM_STR] = 20;
	( ( int * )pBuffer )[TAM_HEAP] = 0;
	( ( int * )pBuffer )[TAM_LISTA] = 0;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST] = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST] = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = NULL;

	return pBuffer;
}

void *ExpandeBufferString ( void * pBuffer ) {

    ( ( int * )pBuffer )[TAM_BUFFER] += 20;
    ( ( int * )pBuffer )[TAM_STR] += 20;

    pBuffer = (void *) realloc(pBuffer, ((int *)pBuffer)[TAM_BUFFER]);
    if ( pBuffer == NULL) {
        puts("Erro de alocação de memória.");
        exit(-1);
    }

    return pBuffer;
}

void *LePessoa (void * pBuffer) {
    // IDEIA: armazenar o nome e o e-mail NA MESMA STRING separada por ';', e depois quebrar usando o separador, já dentro do nodo

    puts("Insira o nome:");

    ( ( int * )pBuffer )[VAR_I] = 0;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET + 1))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }

    puts("Insira o e-mail:");
    
    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET + 1))[--( ( int * )pBuffer )[VAR_I]]=';';
    
    ( ( int * )pBuffer )[VAR_I]++;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET + 1))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }

    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET + 1))[--( ( int * )pBuffer )[VAR_I]]='\0';

    puts("Insira a idade:");

    scanf("%d", &( ((int *) pBuffer)[VAR_J] ) );

    //TODO: TRIM DA STRING (remover alocação extra) (escovação de bits, só fazer quando tiver tudo pronto)

    return pBuffer; //NA DÚVIDA, TUDO QUE (RE)ALOCAR PBUFFER TEM QUE RETORNAR O ENDEREÇO DE PBUFFER PRA MAIN
    
}

void * CriaNodo ( void *pBuffer ) {
    // o tamanho da string deve estar em I, a idade deve estar em J, a string no slot da string

    void *nodo = (void *) malloc( 1 + (2 * sizeof(void *)) + (sizeof(int)) + (sizeof(char) * ( ( int * )pBuffer )[VAR_I]));

    ((void **) nodo)[PTR_ANTERIOR] = NULL;
    ((void **) nodo)[PTR_PROXIMO] = NULL;

    strcpy((char *) (nodo + (2 * sizeof(void *)) + (sizeof(int)) + 1), ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET + 1)));

    ((int *) (nodo + 2* sizeof (void *) + 1))[0] = ( ( int * )pBuffer )[VAR_J];
    

    //TODO: tratar erros aqui

    return nodo;
}

void ImprimeNodo ( void * nodo ) {
    printf("Nome e Email: %s\nIdade:%d\n", (char *) (nodo + (2 * sizeof(void *) + (sizeof(int)) + 1)), ((int *) (nodo + (2* sizeof (void *)) + 1))[0]);
}
