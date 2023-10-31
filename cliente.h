#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "structs.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada;
extern garcom_t** lista_garcons;

void conversaComAmigos(cliente_t* cliente) {
    printf("Cliente %d está conversando com amigos\n", cliente->id);
    fflush(stdout);
    sleep((rand() % max_conversa)/1000);
    printf("Cliente %d terminou de conversar\n", cliente->id);
    fflush(stdout);
}

void fazPedido(cliente_t* cliente, bar_t* bar) {
    printf("Cliente %d entrou na fila pra pedir\n", cliente->id);
    enqueue(&bar->fila_clientes, cliente);
}

void esperaPedido(cliente_t* cliente) {
    printf("Cliente %d espera o pedido\n", cliente->id);
    fflush(stdout);
    sem_wait(&cliente->sem);
}

void recebePedido(cliente_t* cliente) {
    printf("Cliente %d recebe o pedido\n", cliente->id);
    fflush(stdout);
}

void consomePedido(cliente_t* cliente) {
    sleep((rand() % max_consumo)/1000);
    printf("Cliente %d terminou de consumir a bebida\n", cliente->id);
    fflush(stdout);
}

#endif
