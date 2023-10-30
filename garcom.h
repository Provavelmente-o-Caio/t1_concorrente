#ifndef GARCOM_H
#define GARCOM_H

#include <stdio.h>
#include "structs.h"
#include "fila.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada, rodada_finalizada;
extern cliente_t** lista_clientes;
extern garcom_t** lista_garcons;
extern pthread_mutex_t clientes_bar;

void recebeMaximoPedidos(garcom_t* garcom) {
    sem_wait(&garcom->sem);
    printf("O garçom %d recebeu todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void registraPedidos(garcom_t* garcom) {
    printf("O garçom %d registra todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void entregaPedidos(garcom_t* garcom, bar_t* bar) {
    for (int i = 0; i < gn; i++) {
        pthread_mutex_lock(&clientes_bar);
        cliente_t cliente = dequeue(bar->fila_clientes);
        printf("Garçom %d entregou o pedido do cliente %d\n",garcom->id, cliente->id);
        fflush(stdout);
        sem_post(&cliente->sem);
        pthread_mutex_unlock(&clientes_bar);
    }
    garcom->terminou_rodada = 1;
}
#endif
