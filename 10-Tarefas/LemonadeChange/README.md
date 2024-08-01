# Trabalho Prático 1 (LeetCode 860)

- Autor: Matheus Renan de Freitas (M5)

O trabalho foi realizado e concluído ainda em horário de aula. O código enviado na plataforma é o mesmo do arquivo, com a adição de uma função `main()` para conveniência - debug e execução local.
Ademais, o arquivo `lemonadeChange.c` do repositório é rigorosamente o mesmo enviado através do e-aula (exceto, talvez, alguma mudança mínima de formatação).

## Lógica do programa
O algoritmo percorre o array de entrada fazendo a contagem das notas de 5 e 10 dólares recebidas. Ao receber uma nota de 5 dólares, não é necessário fornecer troco, portanto o contador é incrementado somente.
Ao receber uma nota de 10 dólares, é necessário já ter recebido ao menos uma nota de 5 dólares para fornecer troco. Se não for possível, a função é encerrada retornando `false`; caso contrário, o contador das notas de 10 dólares é incrementado e o contador das notas de 5 dólares é decrementado, e o programa segue normalmente.
Para dar troco para uma nota de 20 dólares, há duas possibilidades: fornecer uma nota de 10 e uma de 5 (decrementando-as de seus respectivos contadores) ou três notas de 5 (também decrementadas). Se nenhuma dessas possibilidades é alcançada, a função também é encerrada retornando `false`.
Se é possível percorrer todo o *array* de entrada sem atingir nenhuma condição de falha (por retorno `false`), a função, evidentemente, deve retornar `true`, pois todos os clientes receberam adequadamente o troco de suas compras.

## Feito em aula
O código foi feito completamente em horário de aula. O envio foi aceito pela plataforma sem grandes problemas.

## Feito em casa
O códio *per se* não foi alterado em casa. Foi feita a gravação de um vídeo (enviado em particular ao professor) e a confecção deste arquivo `readme`. 
