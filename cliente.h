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
extern pthread_mutex_t mut_pedidos;

void conversaComAmigos(cliente_t* cliente) {
    printf("Cliente %d está conversando com amigos\n", cliente->id);
    fflush(stdout);
    sleep((rand() % max_conversa)/1000);
    printf("Cliente %d terminou de conversar\n", cliente->id);
    fflush(stdout);
}

void fazPedido(cliente_t* cliente) {
    garcom_t* garcom = lista_garcons[rand() % g];
    garcom->fila_clientes[garcom->num_pedido] = cliente;
    garcom->num_pedido++;
    sem_post(&garcom->sem_ativado);
    printf("Cliente %d fez o pedido para o Garçom %d\n", cliente->id, garcom->id);
    fflush(stdout);
}

void esperaPedido(cliente_t* cliente) {
    printf("Cliente %d espera o pedido\n", cliente->id);
    fflush(stdout);
    sem_wait(&cliente->sem);
}

void recebePedido(cliente_t* cliente) {
    printf("Cliente %d recebe o pedido\n", cliente->id);
}

void consomePedido(cliente_t* cliente) {
    sleep((rand() % max_consumo)/1000);
    printf("Cliente %d terminou de consumir a bebida\n");
}

#endif