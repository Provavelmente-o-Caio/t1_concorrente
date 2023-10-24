// Grupo: Caio Ferreira Cardoso, Gabriel Reimann Cervi, Lucas Brand Martins

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#include "structs.h"
#include "cliente.h"
#include "garcom.h"

int n, g, gn, num_rodadas, max_consumo, max_conversa;
int fechouBar = 0;
int rodada = 0;

void* thread_cliente(void* arg) {
    cliente_t* cliente = (cliente_t*) arg;
    printf("teste10");
    //while(!fechouBar) {
        conversaComAmigos(cliente); // tempo variavel
        fazPedido(cliente);
        esperaPedido(cliente);
        recebePedido(cliente);
        consomePedido(cliente); // tempo variavel
    //}
}

void* thread_garcom(void* arg) {
    //while(!fechouBar) {
        recebeMaximoPedidos();
        registraPedidos();
        entregaPedidos();
        //rodada++; // serve como parâmetro para fechar o bar
    //}
}

int main(int argc, char* argv[]) {

    if (argc < 7) {
        printf("Uso: %s [clientes] [garcons] [clientes/garcons] [rodadas] [max_conversa] [max_consumo]", argv[0]);
        return 1;
    }

    n = atoi(argv[1]); // numero clientes
    g = atoi(argv[2]); // numero garcons
    gn = atoi(argv[3]); // capacidade de atendimento
    num_rodadas = atoi(argv[4]); // numero de rodadas
    max_conversa = atoi(argv[5]); // tempo maximo antes de fazer um novo pedido
    max_consumo = atoi(argv[6]); // tempo maximo de consumo de uma bebida


    pthread_t threads_clientes[n];
    pthread_t threads_garcons[g];

    cliente_t clientes[n];
    for (int i = 0; i < n; i++) {
        clientes[i].
        sem_init(&clientes[i].sem, 0, 1);
    }

    garcom_t garcons[g];

    for (int i = 0; i < g; i++) {
        sem_init(&garcons[i].sem, 0, gn);
    }
    printf("teste2");
    // Criação de Threads
    for (int i = 0; i < n; i++)
        pthread_create(&threads_clientes[i], NULL, thread_cliente, (void*)&clientes);

    printf("teste3");

    for (int i = 0; i < g; i++)
        pthread_create(&threads_garcons[g], NULL, thread_garcom, (void*)&garcons[i]);

    printf("teste4");
    // Sincronização das Threads
    for (int i = 0; i < n; i++)
        pthread_join(threads_clientes[i], NULL);

    for (int i = 0; i < g; i++)
        pthread_join(threads_garcons[i], NULL);
    
    free(bar);

    return 0;
}