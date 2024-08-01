# Trabalho Prático 2 (LeetCode 1717)

- Autor: Matheus Renan de Freitas (M5)

O trabalho foi realizado parcialmente em horário de aula. Há problemas de `time limit` em todas as soluções exceto na solução 3.

## Lógica do programa
Foram feitas diversas tentativas de resolver o problema, a única que funcionou envolve sobrescrever a string `s` para excluir as ocorrências de cada substring e realizar a contagem (via comparação de tamanhos) dos pontos.

## Feito em aula
O código feito em aula apresentava problemas graves de redundância, pois o fato de que não era necessário passar a string n vezes para cada grupo de caracteres removidos não era conhecido (até olhar o editorial do problema).

## Feito em casa
Em casa, foram feitas outras três versões do programa: a diferença entre elas é a técnica utilizada para exclusão de substrings. `solucao1.c` usa pilha com lista encadeada, `solucao2.c` usa pilha emulada através de um array de caracteres e `solucao3.c` (a única validada) faz a substituição de caracteres diretamente na string `s`.
