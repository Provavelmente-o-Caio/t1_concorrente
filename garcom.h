#ifndef GARCOM_H
#define GARCOM_H

#include <stdio.h>
#include "structs.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada, rodada_finalizada;
extern cliente_t** lista_clientes;
extern garcom_t** lista_garcons;

void recebeMaximoPedidos(garcom_t* garcom) {
    sem_wait(&garcom->sem);
    printf("O garçom %d recebeu todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void registraPedidos(garcom_t* garcom) {
    printf("O garçom %d registra todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void entregaPedidos(garcom_t* garcom) {
    for (int i = 0; i < gn; i++) {
        for (int j = 0; j < n; j++) {
            cliente_t* cliente = lista_clientes[j];
            if (garcom->fila_clientes[i] == cliente->id) {
                printf("Garçom %d entregou o pedido do cliente %d\n", garcom->id, cliente->id);
                fflush(stdout);
                sem_post(&cliente->sem);
                garcom->num_pedido--;
                garcom->fila_clientes[i] = -1;
            }
        }
    }
    garcom->terminou_rodada = 1;
}

int verificaSeRodadaTerminou() {
    int verificacao = 1;
    for (int i = 0; i < g; i++) {
        garcom_t* garcom = lista_garcons[i];
        if (garcom->terminou_rodada == 0) {
            verificacao = 0;
        }
    }
    return verificacao;
}

#endif
