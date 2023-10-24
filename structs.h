#ifndef STRUCTS_H
#define STRUCTS_H

#include <semaphore.h>

typedef struct {
    int fechouBar;
    int rodada;
    int maxRodadas;
} bar_t;

typedef struct {
    int id;
    int tempoMaxConversa;
    int tempoMaxConsumo;
    sem_t sem;
    bar_t* bar;
} cliente_args_t;

typedef struct {
    int id;
    int capacidade;
    sem_t sem;
    bar_t* bar;
} garcom_args_t;

#endif