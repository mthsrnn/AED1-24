#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimeMenu(void);
void limpaStdin(void);
int adicionaNome(char * entrada, char ** saida);
char *removeNome(char *entrada);
void listaNomes(char *entrada);

int main(void) {
  char opt, buffer;
  char *lista = (char *) calloc(1, sizeof(char));
  char *entrada;
  int quantosNomes = 0;
  int *indiceAdicionados;

  do {
    imprimeMenu();

    scanf("%c^['\n']", &opt);

    switch (opt) {
      case '1':
        puts("Insirar o nome para adicionar:");
        scanf("%s", entrada);
        indiceAdicionados = (int *) realloc(indiceAdicionados, sizeof(int)*(quantosNomes+1));
        indiceAdicionados[quantosNomes] = adicionaNome(entrada, &lista);
        quantosNomes++;
      break;

      case '2':
        puts("Insirar o nome para remover:");
        scanf("%s", entrada);
        //lista = removeNome(entrada);
      break;

      case '3':
        //listaNomes(entrada);
        puts(lista);
      break;

      case '4':
        return EXIT_SUCCESS;
      break;

      default:
        puts("Opçao invalida!");
      break;

    }
    
  } while (opt != '4');
  
  return EXIT_SUCCESS;
}

void imprimeMenu(void){
  puts("Escolha a operação:\n1 - Adiciona nome\n2 - Remove nome\n3 - Lista os nomes\n4 - Sair");
}

int adicionaNome(char * entrada, char ** saida){
  int lastpos = strlen(*saida);
  int oldpos = lastpos;
  char * novoPonteiro = realloc(*saida, sizeof(char)*(strlen(*saida)+strlen(entrada)-1));
  
  if (novoPonteiro== NULL){
    fputs("Erro de alocacao", stderr);
    exit(EXIT_FAILURE);
  }

  for( int i = 0; i < strlen(entrada); i++ ){
    novoPonteiro[lastpos] = entrada[i];
    lastpos ++;
  }

  *saida = novoPonteiro;
  return oldpos;
}
