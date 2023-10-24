// Grupo: Caio Ferreira Cardoso, Gabriel Reimann Cervi, Lucas Brand Martins

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "cliente.h"
#include "garcom.h"

int n, g, gn, num_rodadas, max_consumo, max_conversa;
int fechouBar = 0;
int rodada = 0;
garcom_t** lista_garcons = NULL;

pthread_mutex_t mut_rodada;

void* thread_cliente(void* arg) {
    cliente_t* cliente = (cliente_t*) arg;
    while(!fechouBar) {
        conversaComAmigos(cliente); // tempo variavel
        fazPedido(cliente);
        esperaPedido(cliente);
        recebePedido(cliente);
        consomePedido(cliente); // tempo variavel
    }
}

void* thread_garcom(void* arg) {
    garcom_t* garcom = (garcom_t*) arg;
    while(!fechouBar) {
        recebeMaximoPedidos();
        registraPedidos();
        entregaPedidos();
        rodada++; // serve como parâmetro para fechar o bar
    }
}

int main(int argc, char* argv[]) {
    printf("teste0");
    if (argc < 7) {
        printf("Uso: %s [clientes] [garcons] [clientes/garcons] [rodadas] [max_conversa] [max_consumo]\n", argv[0]);
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

    srand(time(NULL));
    pthread_mutex_init(&mut_rodada, NULL);
    printf("teste1");
    lista_garcons = (garcom_t**) malloc(g*sizeof(garcom_t));
    for (int i = 0; i < g; i++) {
        garcom_t* garcom = malloc(sizeof(garcom_t));
        lista_garcons[i] = garcom;
        garcom->id = i;
        sem_init(&garcom->sem, 0, gn);
        garcom->fila_clientes = (cliente_t*) malloc(gn * sizeof(cliente_t));
    }
    printf("teste2");
    cliente_t clientes[n];
    for (int i = 0; i < n; i++) {
        clientes[i].id = i;
        sem_init(&clientes[i].sem, 0, 0);
    }

    // Criação de Threads
    for (int i = 0; i < n; i++)
        pthread_create(&threads_clientes[i], NULL, thread_cliente, (void*)&clientes[i]);


    for (int i = 0; i < g; i++)
        pthread_create(&threads_garcons[g], NULL, thread_garcom, (void*)lista_garcons[i]);


    // Sincronização das Threads
    for (int i = 0; i < n; i++) {
        pthread_join(threads_clientes[i], NULL);
        sem_destroy(&clientes[i].sem);
    }

    for (int i = 0; i < g; i++) {
        pthread_join(threads_garcons[i], NULL);
        sem_destroy(&lista_garcons[i]->sem);
    }

    

    return 0;
}