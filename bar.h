#ifndef GARCOM_H
#define GARCOM_H

#include <stdio.h>
#include "structs.h"
#include "fila.h"
#include "garcom.h"

extern int n, g, gn, num_rodadas, max_consumo, max_conversa, fechouBar, rodada, rodada_finalizada;
extern cliente_t** lista_clientes;
extern garcom_t** lista_garcons;

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
