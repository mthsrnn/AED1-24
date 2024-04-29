#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INI_ENTRADA 10

void imprimeMenu(void);
char *scanEntrada(void);
char *adicionaNome(char *entrada, char *vetor);
char *removeNome(char *entrada, char *vetor);
void listaNomes(char *entrada);

int main(void) {
  int opt;
  char *lista = (char *)calloc(1, sizeof(char));
  char *entrada;

  do {
    imprimeMenu();

    scanf("%d", &opt);

    switch (opt) {
    case 1:
      puts("Insira o nome para adicionar:");
      entrada = scanEntrada();
      lista = adicionaNome(entrada, lista);
      free(entrada);
      break;

    case 2:
      puts("Insira o nome para remover:");
      entrada = scanEntrada();
      lista = removeNome(entrada, lista);
      free(entrada);
      break;

    case 3:
      // listaNomes(entrada);
      puts(lista);
      break;

    case 4:

      free(lista);
      return EXIT_SUCCESS;
      break;

    default:
      puts("Opcao invalida!");
      break;
    }

  } while (opt != 4);
  
  free(lista); //não é pra entrar aqui, mas se entrar, nao dá memory leak

  return EXIT_SUCCESS;
}

void imprimeMenu(void) {
  puts("Escolha a operacao:\n1 - Adiciona nome\n2 - Remove nome\n3 - Lista os nomes\n4 - Sair");
}

char *scanEntrada(void) {
  size_t tamanho = INI_ENTRADA;
  char *saida = malloc(sizeof(char) * INI_ENTRADA);
  if (saida == NULL) {
    fputs("Erro de alocacao.", stderr);
    exit(EXIT_FAILURE);
  }
  int c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF); //limpa o buffer
  while ((c = getchar()) != '\n' && c != EOF) {
    if (i == tamanho) {
      tamanho *= 2;
      saida = realloc(saida, sizeof(char) * (tamanho + 1));
      if (saida == NULL) {
        fputs("Erro de alocacao.", stderr);
        exit(EXIT_FAILURE);
      }
    }
    saida[i] = c;
    i++;
  }
  saida = realloc(saida, sizeof(char) * (i+1));
  if (saida == NULL) {
    fputs("Erro de alocacao.", stderr);
    exit(EXIT_FAILURE);
  }
  saida[i] = '\0';
  return saida;
}

char *adicionaNome(char *entrada, char *vetor) {
  int tamanhoEntrada = strlen(entrada), i;
  int tamanhoVetor = strlen(vetor);
  char *novoPonteiro = realloc(vetor, sizeof(char) * (tamanhoVetor + tamanhoEntrada + 2)); //o "padding" (+2) extra é pra caber o \0 e a virgula

  if (novoPonteiro == NULL) {
    fputs("Nao foi possivel realocar o vetor", stderr);
    exit(EXIT_FAILURE);
  }

  for (i = 0; i < tamanhoEntrada; i++) {
    novoPonteiro[tamanhoVetor++] = entrada[i];
  }

  novoPonteiro[tamanhoVetor] = ',';
  tamanhoVetor++;
  novoPonteiro[tamanhoVetor]='\0';

  return novoPonteiro;
}

char *removeNome(char *entrada, char *vetor) {
  int tamanhoEntrada = strlen(entrada), i, j, k;
  int tamanhoVetor = strlen(vetor);

  if (tamanhoEntrada <= 0 || tamanhoVetor <= 0) {
    puts("Entrada e/ou saida vazias(s)");
    return vetor;
  }
  
  for (i = 0; i < tamanhoVetor; i++){
    if (vetor[i] == entrada[0]){
      for (j = 0; j < tamanhoEntrada; j++){
        if(vetor[i + j] != entrada[j])
          break;
      }
      if (j == tamanhoEntrada && ((i == 0) && (vetor[j] == ',') || (vetor[i - 1] == ',') && (vetor[i+j]==','))){
        tamanhoVetor -= tamanhoEntrada;
        while (i < tamanhoVetor){
          vetor[i] = vetor[i+j+1];
          i++;
        }
        vetor[tamanhoVetor] = '\0';
        return realloc(vetor, sizeof(char)*tamanhoVetor);
      }
    }
  }

  puts("Nome nao encontrado.");
  return vetor;
}
