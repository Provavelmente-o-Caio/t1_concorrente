# T1 Concorrente
Um bar resolveu liberar um número específico de rodadas grátis para seus **N** clientes presentes no estabelecimento antes de fechar. Esse bar possui **G** garçons. Cada garçom consegue atender a um número limitado **Gn** de clientes por vez e esta capacidade é igual para todos os garçons. Cada garçom somente vai para a copa para buscar os pedidos quando todos os **Gn** clientes que ele pode atender tiverem feito pedido. Antes de fazer um novo pedido, cada cliente conversa com seus amigos durante um tempo aleatório. Após ter seu pedido atendido, um cliente pode fazer um novo pedido após consumir sua bebida (o que também leva um tempo aleatório). Uma nova rodada (**R**) somente pode ocorrer quando foram atendidos todos os clientes que conseguiram fazer pedidos na rodada anterior. Nem todos os clientes precisam pedir uma bebida a cada rodada. A simulação acaba quando o número de rodadas **R** é atingido.

# Construição da Solução
Implemente uma solução que permita a passagem por parâmetro para o programa: (i) o número de clientes presentes no estabelecimento (**N**); (ii) o número de garçons que estão trabalhando (**G**); (iii) a capacidade de atendimento dos garçons (**Gn**); (iv) o número de rodadas grátis que serão liberadas no bar (**R**); (v) tempo máximo (em milissegundos) que um cliente pode ficar conversando antes de fazer um novo pedido; (vi) tempo máximo (em milissegundos) que um cliente fica consumindo a bebida. O programa deverá receber, obrigatoriamente, os parâmetros nessa ordem via linha de comando:
```c
./programa <clientes> <garcons> <clientes/garcon> <rodadas> <max.conversa> <max.consumo>
```
Cada garçom e cada cliente devem ser representados por threads, estruturalmente definidas conforme os pseudocódigos a seguir:

![image](https://github.com/Provavelmente-o-Caio/t1_concorrente/assets/61165700/375200cd-3b1c-4dbc-852b-8779cadbae10)

Este trabalho deve ser implementado em C, usando a biblioteca POSIX PThreads, no Linux, utilizando semáforos e threads. A utilização de mutexes também é permitida, se necessário.
As seguintes regras devem ser respeitadas:
- Os pedidos dos clientes são atendidos pelos garçons em ordem de chegada na fila de pedidos de cada garçom (a solução não deve permitir que clientes furem essa fila);
- O garçom só pode ir para a copa quando tiver recebido seus Gn pedidos;
- O programa deve mostrar a evolução da simulação, portanto planeje bem o que será apresentado. Deve ficar claro o que está acontecendo no bar a cada rodada. Os pedidos dos clientes, os atendimentos pelos garçons, os deslocamentos para o pedido, a garantia de ordem de atendimento, etc.

# Formato de Entrega e Avaliação
O trabalho deverá ser realizado em grupos de 3 alunos e o número máximo de grupos será limitado. Todos os arquivos contendo o código do trabalho, bem como Makefile e um relatório apresentando sucintamente a solução, deverão ser submetidos pelo Moodle. Não serão aceitos trabalhos entregues fora do prazo ou por email. Trabalhos que não compilam no Linux com o Makefile fornecido ou que não executam receberão nota ZERO, bem como trabalhos que sejam considerados como plágio.

Os itens para avaliação são: (i) funcionamento do programa; (ii) execução das threads sem ocorrência de deadlocks e/ou outros problemas de sincronização; (iii) saída do programa (de modo a permitir a avaliação de seu funcionamento); (iv) clareza do código (utilização de comentários e nomes de variáveis adequadas); (v) apresentação do trabalho; (vi) qualidade do relatório; (vii) compilação sem warnings; e (viii) sem vazamento de memória.

Durante as apresentações, o professor irá avaliar o conhecimento individual dos alunos sobre os conteúdos teóricos e práticos vistos em aula e sobre a solução adotada no trabalho. A nota atribuída à cada aluno i no trabalho (𝑁𝑜𝑡𝑎𝑇𝑟𝑎𝑏𝑎𝑙ℎ𝑜) será calculada da seguinte forma, onde 𝐴𝑖 é a nota referente à apresentação do aluno i e 𝑆 é a nota atribuída à solução do trabalho:
$$
NotaTrabalho_i = \frac{A_i*S}{10}
$$