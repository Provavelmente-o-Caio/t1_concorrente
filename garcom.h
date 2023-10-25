#ifndef GARCOM_H
#define GARCOM_H

#include <stdio.h>
#include "structs.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada;

void recebeMaximoPedidos(garcom_t* garcom) {
    for (int i = 0; i < gn; i++) {
        printf("Garçom %d esperando pedido\n", garcom->id);
        fflush(stdout);
        sem_wait(&garcom->sem_ativado);
        sem_wait(&garcom->sem_pedidos);
        garcom->num_pedido++;
        printf("Garçom %d recebeu um pedido\n", garcom->id);
        fflush(stdout);
    }
}

void registraPedidos(garcom_t* garcom) {

}

void entregaPedidos(garcom_t* garcom) {
    for (int i = 0; i < garcom->num_pedido; i++) {
        cliente_t* cliente = garcom->fila_clientes[i];
        sem_post(&cliente->sem);
        printf("Garçom %d entregou o pedido do cliente %d\n", garcom->id, cliente->sem);
        garcom->num_pedido--;
    }
}

#endif