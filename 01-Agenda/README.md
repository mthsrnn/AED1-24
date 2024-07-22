# Agenda pBuffer

- Autor: Matheus Renan de Freitas (M5)

# Desenvolvimento

Desenvolvi a atividade seguindo a seguinte filosofia:

- Modularizar o código em várias funções
- Fazer cada função funcionar corretamente antes de desenvolver a próxima
- Expansões de funcionalidade devem se tornar novas funções
- Cada função desenvolvida deve ser debugada individualmente
- Possiveis vazamentos de memória serão tratados individualmente para cada função

Foi utilizado `gdb` para debugar o buffer, através da função de inspeção de memória.

O programa foi desenvolvido na plataforma `GNU/Linux` e compilado via `gcc 13.2.0`

Os testes de `valgrind` foram executados através do comando `valgrind -s --leak-check=full --track-origins=yes  ./agenda` (em algumas ocasiões, foi utilizado através do servidor para o gdb, para debugar funções individualmente, com a adição da flag `--vgdb-error=0`)

# Funcionamento

## Interpretação do problema
A agenda começou a ser desenvolvida antes da aula extra de discussão. Como tinha dúvidas a respeito de como interpretar algumas características do enunciado, optei por implementar o programa da forma *mais difícil que consegui pensar*, a fim de evitar descontos na nota.

Eis o plano:

- O banco de dados da agenda **não é a heap**, e vice-versa: uma fila de prioridade é instanciada exclusivamente para realizar as operações principais do programa (busca, exclusão, adição e impressão).
- **Ponteiros são variáveis** que guardam endereços de memória, e **não se pode declarar variáveis**: todas as indireções e endereços de ponteiros foram calculados manualmente (não raro, foram atribuidos em *macros*).
- **Todas as operações são feitas utilizando a heap**: a heap é utilizada sempre para buscar, imprimir, adicionar e remover nodos do banco de dados. As regras da heap nunca são quebradas.

## Arquitetura do buffer

- `pBuffer` possui 7 variáveis inteiras e 4 ponteiros alocados de maneira **fixa**. Como são utilizados por quase todas as funções o tempo todo. Tratei-os como **registradores** do estado atual da agenda, de modo que as funções interajam entre si **modificando o buffer em uníssono, reaproveitando dados computados anteriormente.**
- As *strings* lidas são armazenadas em um único registro de tamanho alocado **dinamicamente**. Não há desperdício de memória com a string.
- A heap adicional é um vetor de ponteiros `void`. O tamanho da heap, quando chamada, será **sempre igual ao tamanho do banco de dados, mais um**. Esse espaço extra é disperdiçado, infelizmente, nas operações de remoção, busca e impressão. Priorizou-se a segurança da memoria em revés a essa optimização mínima.
  - Em contrapartida, a heap só é alocada quando necessária. Após a execução de cada operação, há a devolução da memória utilizada.

## Arquitetura do nodo

Quando um nodo é criado, aloca-se um espaço fixo para os ponteiros `void` triviais da lista duplamente encadeada (`pProximo`, `pAnterior`).

É alocado também um espaço para o inteiro que armazena a idade do contato salvo.

Em seguida, soma-se a essas variáveis o tamanho exato da última string lida em `pBuffer`.

A string lida em pBuffer contém um caractere especial de separação para os campos nome e e-mail. Após essa string ser copiada para dentro do nodo, esse caractere é substituido por um separador `'\0'`, pois acessado via operação `(strlen() + 1)` partindo do endereço da última string lida.

Ou seja, os nodos **possuem tamanhos diferentes**, mas **jamais há disperdício da memória alocada**.

## Arquitetura do banco de dados
Inserções na lista são feitas sempre no fim, enquanto remoções são feitas sempre do fim. Essa abordagem garante a regra implícita de prioridade para os nodos que estão à mais tempo na lista.

A adição de um novo nodo é feita **copiando-o primeiro para dentro da lista**. A heap é utilizada, portanto, para realizar a inserção do nodo extra em ordem lexicográfica (ou remoção automática, caso haja um nodo com nome idêntico já armazenado).

A remoção é feita retirando todos os nodos do banco de dados e passando-os para a heap auxiliar. O nodo que tiver nome igual ao que se deseja remover não é devolvido à lista, e recebe `free`.

A impressão e a busca também são feitas passando toda a lista para a heap auxilliar, de tal forma que somente a operação intermediária mude:
  - **Na impressão**, todos os nodos são impressos antes de serem adicionados de volta para a lista.
  - **Na busca**, o nodo é impresso somente se o nome que nele consta for igual ao último nome guardado em `pBuffer`.

## Resultados

Não foram encontrados erros de execução ou erros de memória no `valgrind`. Uma demonstração breve desse comportamento é apresentada no vídeo da atividade.
