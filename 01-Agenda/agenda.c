#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Atalhos para as variáveis fixas alocadas no buffer
#define INT_OFFSET     sizeof(int) * 7
#define PTR_OFFSET  sizeof(void *) * 4
#define STR_INI     sizeof(char ) *  1

#define VAR_I                        0
#define VAR_J                        1
#define OPT                          2
#define TAM_BUFFER                   3
#define TAM_STR                      4
#define TAM_HEAP                     5
#define TAM_LISTA                    6
#define PTR_FIRST                    0
#define PTR_LAST                     1
#define PTR_NODO                     2
#define PTR_NODOAUX                  3
#define PTR_PROXIMO                  1
#define PTR_ANTERIOR                 0

// eu não ia fazer macros pra evitar confusão, só que o código da heap ficou impossivel de gerenciar por falta de espaço horizontal, então só vou usar elas lá
#define GET_INT(a) (( ( int * )pBuffer )[a])
#define GET_PTR(a) (( ( void ** )( pBuffer + INT_OFFSET ) )[a])
#define GET_NOME(a) ((char *) (a + (2 * sizeof(void *) + (sizeof(int)) ))) // esse macro é muito bom, faz a conversão para o endereço do nome dentro de um nodo
#define GET_HEAP(a) (( void ** ) ( pBuffer + ( INT_OFFSET ) + ( PTR_OFFSET ) + (GET_INT(TAM_STR) + 1)))[a] 
#define GET_STR  ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))

void ImprimeMenu( void );
void* AlocaBuffer( void );
void* ExpandeBufferString ( void * pBuffer );
void * CortaBufferString ( void * pBuffer );
void* LePessoa ( void * pBuffer);
void* CriaNodo ( void *pBuffer );
void ImprimeNodo ( void * nodo );
void AdicionaNodoParaLista ( void * pBuffer );
void ImprimeLista ( void * pBuffer );
void RemoveNodoDaLista ( void * pBuffer );
void* ConstroiHeap ( void * pBuffer );
void* DestroiHeap ( void * pBuffer );
void RemoveNodoDaLista ( void * pBuffer );
void HeapPush ( void * pBuffer );
void HeapPop ( void * pBuffer );
void AdicionaHeapOrdenado ( void * pBuffer );
void* PushListaParaHeap ( void * pBuffer );
void* PopHeapParaLista ( void * pBuffer );

// FUNÇÕES FINAIS: as que realmente fazem cada parte do programa
void* AdicionaPessoa ( void * pBuffer);
void* RemovePessoa ( void * pBuffer );
void* BuscaPessoa ( void * pBuffer );
void Saida ( void * pBuffer );

int main( void ) {

	void *pBuffer = AlocaBuffer();

	do {

		ImprimeMenu();

		scanf( "%d", ( int * )pBuffer + OPT );

		getchar();

		switch( ( ( int * )pBuffer )[OPT] ) {
		case 1:
            pBuffer = AdicionaPessoa ( pBuffer );
            break;

		case 2:

            pBuffer = RemovePessoa( pBuffer );

			break;

		case 3:
            pBuffer = BuscaPessoa( pBuffer );
			break;

        case 4:
            ImprimeLista( pBuffer );
			break;

		case 5:

            Saida( pBuffer );
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

void* AdicionaPessoa ( void * pBuffer) {
    pBuffer = LePessoa(pBuffer);       

	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = CriaNodo( pBuffer );
    GET_PTR(PTR_NODOAUX) = GET_PTR(PTR_NODO);
    AdicionaNodoParaLista( pBuffer );
    pBuffer = PushListaParaHeap( pBuffer );
    if ( GET_INT(VAR_J) == -1) {
        printf("\"%s\" ja esta na lista!\n", GET_NOME(GET_PTR(PTR_NODOAUX)));
        free(GET_PTR(PTR_NODOAUX));
        GET_PTR(PTR_NODOAUX) = NULL;
    }
    pBuffer = PopHeapParaLista ( pBuffer );

    return pBuffer;
}

void* RemovePessoa ( void * pBuffer ) {
    if ( ( ( int * )pBuffer )[TAM_LISTA] == 0 ) {
        puts("A agenda esta vazia.");
        return pBuffer;
    }

    puts("Insira o nome para remover:");

    ( ( int * )pBuffer )[VAR_I] = 0;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }
    
    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[--( ( int * )pBuffer )[VAR_I]]='\0';

    pBuffer = CortaBufferString( pBuffer );

    GET_INT(VAR_I) = 0;

    pBuffer = PushListaParaHeap( pBuffer );
    while (GET_INT(TAM_HEAP) > 0) {
        HeapPop( pBuffer );
        if ( GET_NOME(GET_PTR(PTR_NODO))!= NULL && !strcmp(GET_NOME(GET_PTR(PTR_NODO)),( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET)))){
            puts( "Contato removido:" );
            ImprimeNodo( GET_PTR(PTR_NODO) );
            free(GET_PTR(PTR_NODO));
            GET_PTR(PTR_NODO) = NULL;
            pBuffer = PopHeapParaLista ( pBuffer );
            puts("");
            return pBuffer;
        }
        AdicionaNodoParaLista( pBuffer ); 
    }
    puts("Pessoa não encontrada.");
    pBuffer = DestroiHeap( pBuffer );
    return pBuffer;
}

void* BuscaPessoa ( void * pBuffer ) {
    puts("Insira o nome para buscar:");

    ( ( int * )pBuffer )[VAR_I] = 0;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }
    
    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[--( ( int * )pBuffer )[VAR_I]]='\0';

    pBuffer = CortaBufferString( pBuffer );

    GET_INT(VAR_I) = 0;

    pBuffer = PushListaParaHeap( pBuffer );
    while (GET_INT(TAM_HEAP) > 0) {
        HeapPop( pBuffer );
        if ( GET_NOME(GET_PTR(PTR_NODO))!= NULL && !strcmp(GET_NOME(GET_PTR(PTR_NODO)),( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET)))){
            puts( "Contato encontrado:" );
            ImprimeNodo( GET_PTR(PTR_NODO) );
            HeapPush ( pBuffer );
            pBuffer = PopHeapParaLista ( pBuffer );
            puts("");
            return pBuffer;
        }
        AdicionaNodoParaLista( pBuffer ); 
    }
    puts("Pessoa não encontrada.");
    pBuffer = DestroiHeap( pBuffer );
    return pBuffer;
}

void ImprimeMenu( void ) {
	puts( "Escolha a operacao:\n"
	      "1 - Adicionar pessoa\n"
	      "2 - Remover pessoa\n"
	      "3 - Buscar Pessoa\n"
          "4 - Listar todos\n"
	      "5 - Sair" );
}

void *AlocaBuffer( void ) {
	void *pBuffer = malloc( ( INT_OFFSET ) + 
                            ( PTR_OFFSET ) +
	                        ( STR_INI ) +
                            sizeof( void * ) );

    if ( pBuffer == NULL) {
        puts("Erro de alocação de memória.");
        exit(-1);
    }

	( ( int * )pBuffer )[VAR_I] = 0;
	( ( int * )pBuffer )[VAR_J] = 0;
	( ( int * )pBuffer )[OPT] = 0;
	( ( int * )pBuffer )[TAM_BUFFER] = ( int )( ( INT_OFFSET ) + ( PTR_OFFSET ) + ( STR_INI ) + sizeof( void * ) );
    ( ( int * )pBuffer )[TAM_STR] = 0;
	( ( char * )pBuffer + INT_OFFSET + PTR_OFFSET )[( ( int * )pBuffer )[TAM_STR]] = '\0'; // nota para o futuro: grandes chances dessa linha quebrar a heap lá pra frente
	( ( int * )pBuffer )[TAM_HEAP] = 0;
	( ( int * )pBuffer )[TAM_LISTA] = 0;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST]  = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST]   = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO]   = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODOAUX]= NULL;

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

void * CortaBufferString ( void * pBuffer ) {
    GET_INT(VAR_J) = GET_INT(TAM_STR);
    GET_INT(TAM_STR) = strlen( GET_STR ) + 1;

    GET_INT(TAM_BUFFER) -= (GET_INT(VAR_J) - GET_INT(TAM_STR));
    
    pBuffer = (void *) realloc(pBuffer, ((int *)pBuffer)[TAM_BUFFER]);
    if ( pBuffer == NULL) {
        puts("Erro de alocação de memória.");
        exit(-1);
    }
    return pBuffer;
}

void *LePessoa (void * pBuffer) {
    // IDEIA: armazenar o nome e o e-mail NA MESMA STRING separada por '\3', e depois quebrar usando o separador, já dentro do nodo

    puts("Insira o nome:");

    ( ( int * )pBuffer )[VAR_I] = 0;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }

    puts("Insira o e-mail:");
    
    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[--( ( int * )pBuffer )[VAR_I]]='\3';
    
    ( ( int * )pBuffer )[VAR_I]++;

    while ( (( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[( ( int * )pBuffer )[VAR_I]++] = getchar()) != '\n' ) {
        if (( ( int * )pBuffer )[VAR_I] >= ( ( int * )pBuffer )[TAM_STR]) {
            pBuffer = ExpandeBufferString(pBuffer);
        }
    }

    ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET ))[--( ( int * )pBuffer )[VAR_I]]='\0';

    pBuffer = CortaBufferString( pBuffer );

    puts("Insira a idade:");

    scanf("%d", &( ((int *) pBuffer)[VAR_J] ) );

    //TODO: TRIM DA STRING (remover alocação extra) (escovação de bits, só fazer quando tiver tudo pronto)

    return pBuffer; //NA DÚVIDA, TUDO QUE (RE)ALOCAR PBUFFER TEM QUE RETORNAR O ENDEREÇO DE PBUFFER PRA MAIN
    
}

void * CriaNodo ( void *pBuffer ) {
    // o tamanho da string deve estar em I, a idade deve estar em J, a string no slot da string

    void *nodo = (void *) malloc( 2 + (2 * sizeof(void *)) + (sizeof(int)) + (sizeof(char) * ( ( int * )pBuffer )[VAR_I]));

    ((void **) nodo)[PTR_ANTERIOR] = NULL;
    ((void **) nodo)[PTR_PROXIMO]  = NULL;
    ((int *) (nodo + 2* sizeof (void *) ))[0] = ( ( int * )pBuffer )[VAR_J];

    strcpy((char *) (nodo + (2 * sizeof(void *)) + (sizeof(int)) ), ( ( char * )(pBuffer + INT_OFFSET + PTR_OFFSET )));

    for ( ( ( int * )pBuffer )[VAR_J] = 0;( ( int * )pBuffer )[VAR_J] < ( ( int * )pBuffer )[VAR_I]; ( ( int * )pBuffer )[VAR_J]++  ) {
        if ( ((char *) (nodo + (2 * sizeof(void *)) + (sizeof(int)) ))[( ( ( int * )pBuffer )[VAR_J]) ] == '\3' ){
             ((char *) (nodo + (2 * sizeof(void *)) + (sizeof(int)) ))[( ( ( int * )pBuffer )[VAR_J])] = '\0';
        }
    }

    //TODO: tratar erros aqui

    return nodo;
}

void ImprimeNodo ( void * nodo ) {
    printf("\n\tNome: %s\n\tEmail: %s\n\tIdade:%d\n", 
           (char *) (nodo + (2 * sizeof(void *) + (sizeof(int)) )), 
           (char *) (nodo + (2 * sizeof(void *) + (sizeof(int)) + 1 + (strlen(((char *) (nodo + (2 * sizeof(void *) + (sizeof(int)) ))))))), 
           ((int *) (nodo + (2* sizeof (void *)) ))[0]);
}

void AdicionaNodoParaLista ( void * pBuffer ) {
    /*
     CONDIÇÕES:
     pFirst e pLast devem estar inicializados
     o nodo a ser adicionado deve estar em PTR_NODO

    Como endereçar em pBuffer:
    ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST] = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST] = NULL;
	( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = NULL;

    Como endereçar em nodo:
    ((void **) nodo)[PTR_ANTERIOR] = NULL;
    ((void **) nodo)[PTR_PROXIMO] = NULL;

    */

    if ( ( ( int * )pBuffer )[TAM_LISTA] == 0 ) {

        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO];
        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO];

        ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_ANTERIOR] = NULL;
        ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_PROXIMO] = NULL;

    } else { 
        
        ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST])[PTR_PROXIMO] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO];
        ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_ANTERIOR] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST];
        ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_PROXIMO] = NULL;

        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO];

    }

    ( ( int * )pBuffer )[TAM_LISTA]++;
    GET_PTR(PTR_NODO) = NULL;

}



void RemoveNodoDaLista ( void * pBuffer ) {

        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST];

        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST] = ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_PROXIMO];

        if (  ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST] != NULL) {
            ( (void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST])[PTR_ANTERIOR] = NULL;
        }

        if ( --( ( int * )pBuffer )[TAM_LISTA] == 0 ) {
            ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST] = NULL;
        }   

}

void ImprimeLista ( void * pBuffer ) {
    if ( ( ( int * )pBuffer )[TAM_LISTA] == 0 ) {
        puts("A agenda esta vazia.");
    } else {
        ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_FIRST];
        ImprimeNodo( ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] );
        
        while (( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] != ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_LAST]) {
            puts("\n-----------------------------");
            ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] = ((void **) ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO])[PTR_PROXIMO];
            ImprimeNodo( ( ( void ** )( pBuffer + INT_OFFSET ) )[PTR_NODO] );

        }
        puts("");
    }
}

void *ConstroiHeap ( void * pBuffer ) {
    /* Requisitos e convenções:
    * TAM_LISTA deve conter o tamanho da lista
    * TAM_BUFFER deve conter o tamanho correto do buffer
    * VAR_I é usado como indice
    * VAR_J é usado como sinal (erro ou encontrado):
    * */
    
    pBuffer = realloc(pBuffer, GET_INT(TAM_BUFFER) + GET_INT(TAM_LISTA) * sizeof(void *) + 1 );

	( ( int * )pBuffer )[VAR_I] = 0;
	( ( int * )pBuffer )[VAR_J] = 0;
	( ( int * )pBuffer )[TAM_HEAP] = 0;

    return pBuffer;
}

void *DestroiHeap ( void * pBuffer ) {
    /* Requisitos:
    * TAM_BUFFER deve conter o tamanho correto do buffer
    * Todos os nodos já foram removidos com seguranças;
    */
    
    pBuffer = realloc(pBuffer, ((int *)pBuffer)[TAM_BUFFER]);

    return pBuffer;
}

void HeapPush ( void * pBuffer ) {

    if ( GET_INT(TAM_HEAP) == 0 ) {
        GET_HEAP(0) = GET_PTR(PTR_NODO);
        GET_INT(TAM_HEAP)++;

    } else {
        GET_INT(VAR_I) = 0;

        if ( strcmp(GET_NOME(GET_PTR(PTR_NODO)), GET_NOME(GET_HEAP(VAR_I))) == 0 ) {
            GET_PTR(PTR_NODOAUX) = GET_PTR(PTR_NODO);
            GET_INT(VAR_J) = -1;
            return;
        }

        while ( GET_INT(VAR_I) < GET_INT(TAM_HEAP) ) {
            if ( strcmp(GET_NOME(GET_PTR(PTR_NODO)), GET_NOME(GET_HEAP(GET_INT(VAR_I)))) > 0 ) {
                memmove(&GET_HEAP(GET_INT(VAR_I)+1), &GET_HEAP(GET_INT(VAR_I)), (GET_INT(TAM_HEAP) - GET_INT(VAR_I))*sizeof(void *));
                GET_HEAP(GET_INT(VAR_I)) = GET_PTR(PTR_NODO);
                GET_INT(TAM_HEAP)++;
                return;
            }
            GET_INT(VAR_I)++;
        }

        GET_HEAP(GET_INT(VAR_I)) = GET_PTR(PTR_NODO);
        GET_INT(TAM_HEAP)++;

    }
}

void* PushListaParaHeap ( void * pBuffer ) {
    pBuffer = ConstroiHeap( pBuffer );

    while( GET_INT(TAM_LISTA) > 0) {
        RemoveNodoDaLista ( pBuffer );
        HeapPush (pBuffer);
    }

    return pBuffer;
}

void HeapPop ( void * pBuffer ) {
    GET_PTR(PTR_NODO) = GET_HEAP(GET_INT(TAM_HEAP)-1);
    GET_INT(TAM_HEAP)--;
}

void * PopHeapParaLista ( void * pBuffer ) {

    while ( GET_INT(TAM_HEAP) > 0) {
        HeapPop( pBuffer );
        AdicionaNodoParaLista( pBuffer );
    }

    pBuffer = DestroiHeap( pBuffer );
    return pBuffer;
}

void Saida( void * pBuffer ) {

    while( GET_INT(TAM_LISTA) > 0) {
        RemoveNodoDaLista ( pBuffer );
        free(GET_PTR(PTR_NODO));
        GET_PTR(PTR_NODO) = NULL;
    }

    if ( GET_PTR(PTR_NODO) != NULL )
        free( GET_PTR(PTR_NODO) );

    free(pBuffer);

}
