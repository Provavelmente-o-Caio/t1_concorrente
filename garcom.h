#ifndef GARCOM_H
#define GARCOM_H

#include <stdio.h>
#include "structs.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada, rodada_finalizada;
extern cliente_t** lista_clientes;
extern garcom_t** lista_garcons;

void recebeMaximoPedidos(garcom_t* garcom) {
    sem_wait(&garcom->sem); // Espera o garçom receber todos os pedidos
    printf("O garçom %d recebeu todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void registraPedidos(garcom_t* garcom) {
    printf("O garçom %d registra todos os pedidos\n", garcom->id);
    fflush(stdout);
}

void entregaPedidos(garcom_t* garcom) {
    // Verifica cada pedido
    for (int i = 0; i < gn; i++) {
        for (int j = 0; j < n; j++) {
            cliente_t* cliente = lista_clientes[j]; // Ve o cliente na posição j
            if (garcom->fila_clientes[i] == cliente->id) { // Se o cliente estiver na lista do garçom, entrega seu pedido
                sem_post(&cliente->sem); // Libera o cliente para fazer seu próximo pedido
                printf("Garçom %d entregou o pedido do cliente %d\n", garcom->id, cliente->id);
                fflush(stdout);
                --garcom->num_pedido;
                garcom->fila_clientes[i] = -1;
            }
        }
    }
    garcom->terminou_rodada = 1; // Coloca a flag de fim de rodada como true
}

int verificaSeRodadaTerminou() {  // Verifica se a rodada do garçom terminou
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
