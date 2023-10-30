#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

#define MAX_SIZE 100 // Tamanho máximo da fila

// Estrutura para representar a fila
typedef struct {
    cliente_t array[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Função para inicializar a fila
void initialize(Queue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Função para verificar se a fila está vazia
int isEmpty(Queue* queue) {
    return (queue->front == -1);
}

// Função para verificar se a fila está cheia
int isFull(Queue* queue) {
    return (queue->rear == MAX_SIZE - 1);
}

// Função para enfileirar (inserir) um elemento na fila
void enqueue(Queue* queue, cliente_t item) {
    if (isFull(queue)) {
        printf("A fila está cheia. Não é possível enfileirar o elemento %d\n", item);
        return;
    }
    
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    
    queue->rear++;
    queue->array[queue->rear] = item;
}

// Função para desenfileirar (remover) um elemento da fila
cliente_t dequeue(Queue* queue) {
    cliente_t item;
    
    if (isEmpty(queue)) {
        printf("A fila está vazia. Não é possível desenfileirar.\n");
        return -1; // Valor especial para indicar erro
    }
    
    item = queue->array[queue->front];
    
    if (queue->front == queue->rear) {
        // Último elemento na fila, resetamos os índices.
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    
    return item;
}