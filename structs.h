#ifndef STRUCTS_H
#define STRUCTS_H

#include <semaphore.h>

typedef struct {
    int id;
    sem_t sem;
} cliente_t;

typedef struct {
    int id;
    int num_pedido;
    int terminou_rodada;
    sem_t sem;
    int* fila_clientes;
} garcom_t;

#endif
