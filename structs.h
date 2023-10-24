#ifndef STRUCTS_H
#define STRUCTS_H

#include <semaphore.h>

typedef struct {
    int id;
    sem_t sem;
} cliente_t;

typedef struct {
    int id;
    sem_t sem;
} garcom_t;

#endif