#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"

void conversaComAmigos(cliente_t* cliente) {
    printf("Cliente %d está conversando", cliente->id);
    srand(time(NULL));
    int tempoConversa = rand() % cliente->tempoMaxConversa + 1;
    sleep(tempoConversa);
    printf("Cliente %d terminou de conversar", cliente->id);
}

void fazPedido(cliente_t* cliente) {
    printf("Cliente %d fez pedido", cliente->id);
    sem_wait(&cliente->sem);
}

void esperaPedido(cliente_t* cliente) {
    printf("Cliente %d espera o pedido", cliente->id);
}

void recebePedido(cliente_t* cliente) {
    printf("Cliente %d recebe o pedido", cliente->id);
}

void consomePedido(cliente_t* cliente) {
    srand(time(NULL));
    int tempoConsumo = rand() % cliente->tempoMaxConsumo + 1;
    sleep(tempoConsumo);
    sem_post(&cliente->sem);
    printf("Cliente %d terminou de consumir a bebida");
}

#endif