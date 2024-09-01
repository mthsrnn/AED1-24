<img align="center" src="https://raw.githubusercontent.com/mthsrnn/AED1-24/main/10-Tarefas/MostProfitAssigningWork/banner.png"/>

# Tarefa 4 - LeetCode 826

- Autor: **Matheus Renan Freitas de Freitas - M5**

- [Link do Problema](https://leetcode.com/problems/most-profit-assigning-work/description/)
- [Link da Submissão](https://leetcode.com/problems/most-profit-assigning-work/submissions/1373495448/)


## O que foi feito em aula:
A tarefa foi concluida integralmente em sala de aula.

## O que foi feito em casa:
Esse arquivo readme! :)

## Como a solução foi implementada?
A solução proposta utiliza o algoritmo `quicksort` adaptado parar receber dois arrays de mesmo tamanho: o objetivo é ordenar o primeiro array decrescentemente em relação a si, e o segundo array em relação ao primeiro. Para tal, apenas replica todas as mudanças de variáveis executadas no primeiro array no segundo, realizando comparações relacionadas somente ao primeior array.

O que se busca com essa abordagem é manter a relação `i = job`, de modo que o indice acessado tanto em `difficulty` quanto `profit` ainda corresponda ao mesmo trabalho.

Desse modo, os trabalhos são distribuídos aos `workers` seguindo a ordem do array `profit`, de modo que todos recebam o trabalho executável (isto é, que possui dificuldade condizente com a habilidade do trabalhador) mais lucrativo possível.

Por fim, o lucro da tarefa distribuida é somado ao contador `lucro`, que é retornado ao fim da execução.
