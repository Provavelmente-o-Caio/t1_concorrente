// Grupo: Caio Ferreira Cardoso, Gabriel Reimann Cervi, Lucas Brand Martins

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
/*
void thread_cliente() {
    while(!fechouBar) {
        conversaComAmigos(); // tempo variavel
        fazPedido();
        esperaPedido();
        recebePedido();
        consomePedido(); // tempo variavel
    }
}

void thread_garcom() {
    while(!fechouBar) {
        recebeMaximoPedidos();
        registraPedidos();
        entregaPedidos();
        rodada++; // serve como parâmetro para fechar o bar
    }
}
*/
int main(int argc, char* argv[]) {

    if (argc < 1) {
        printf("Uso: %s [clientes] [garcons] [clientes/garcons] [rodadas] [max_conversa] [max_consumo]", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]); // numero clientes
    int g = atoi(argv[2]); // numero garcons
    int gn = atoi(argv[3]); // capacidade de atendimento
    int rodadas = atoi(argv[4]); // numero de rodadas
    int max_conversa = atoi(argv[5]); // tempo maximo antes de fazer um novo pedido
    int max_consumo = atoi(argv[6]); // tempo maximo de consumo de uma bebida

//    pthread_t clientes[n];
//    pthread_t garcons[g];
/*
   // Criação de Threads
    for (int i = 0; i < n; i++) {
        pthread_create(&clientes[i], NULL, thread_cliente, NULL);
    }

    for (int i = 0; i < g; i++) {
        pthread_create(&garcons[g], NULL, thread_garcom, NULL);
    }

    // Sincronização das Threads
    for (int i = 0; i < n; i++) {
        pthread_join(&clientes[i])
    }

    for (int i = 0; i < g; i++) {
        pthread_join(&garcons[i])
    }
*/
  return 0;
}