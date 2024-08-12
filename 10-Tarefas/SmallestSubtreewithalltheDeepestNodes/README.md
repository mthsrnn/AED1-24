<img align="center" src="https://raw.githubusercontent.com/mthsrnn/AED1-24/main/10-Tarefas/SmallestSubtreewithalltheDeepestNodes/banner.png"/>

# Tarefa 3 - LeetCode 865

- Autor: **Matheus Renan Freitas de Freitas - M5**

- [Link do Problema](https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/description/)
- [Link da Submissão](https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes/submissions/1350589346/)


## O que foi feito em aula:
Em aula, sendo direto, não consegui implementar a solução do problema porque o interpretei mal. Imaginei que deveria retornar somende um nodo ou um nodo que contém como descendente os dois nodos mais profundos da árvore, o que é incorreto.

Sabia que deveria utilizar uma operação muito similar ao código que calcula altura, conforme aprendemos nos slides. Tinha esse código decorado e trouxe-o para a submissão final, mas a implementação inicial estava completamente incorreta.

O maior problema que encontrei foi calcular corretamente a profundidade do nodo que estava percorrendo em cada momento. Só consegui solucionar corretamente esse problema em casa.

## O que foi feito em casa:
Em casa, reparei que, de fato, retornar a sub-árvore que contém os nodos mais profundos significa retornar a sub-árvore que atende essas duas condições:
- A profundidade das sub-árvores descendentes da raiz é a maior possível;
- A profundidade da sub-árvore esquerda da raíz é igual à profundidade da sub-árvore direita.

Essa abordagem soluciona o caso em que a maior profundidade é uma folha única - sem descendentes - pois ao percorrer seus nodos direito e esquerdo como `NULL`, a profundidade do nodo pai é considerada, portanto, será igual para os dois testes de profundidade.

O código funciona percorrendo a árvore em ordem pós fixa, para garantir que será avaliada por último a sub-árvore que contém a profundidade desejada, caso contenha sub-árvores simétricas em cada lado.
