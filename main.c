// Grupo: Caio Ferreira Cardoso, Gabriel Reimann Cervi, Lucas Brand Martins

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct {
    int fechouBar;
    int rodada;
    int maxRodadas;
} bar_t;

typedef struct {
    int tempoMaxConversa;
    int tempoMaxConsumo;
    bar_t* bar;
} cliente_args_t;

typedef struct {
    int id;
    int capacidade;
    int clientesAtendidos;
    bar_t* bar;
} garcom_args_t;

void* thread_cliente(void* arg) {
    while(!fechouBar) {
        conversaComAmigos(); // tempo variavel
        fazPedido();
        esperaPedido();
        recebePedido();
        consomePedido(); // tempo variavel
    }
}

void* thread_garcom(void* arg) {
    while(!fechouBar) {
        recebeMaximoPedidos();
        registraPedidos();
        entregaPedidos();
        rodada++; // serve como parâmetro para fechar o bar
    }
}

int main(int argc, char* argv[]) {

    if (argc < 7) {
        printf("Uso: %s [clientes] [garcons] [clientes/garcons] [rodadas] [max_conversa] [max_consumo]", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // numero clientes
    int g = atoi(argv[2]); // numero garcons
    int gn = atoi(argv[3]); // capacidade de atendimento
    int rodadas = atoi(argv[4]); // numero de rodadas
    int max_conversa = atoi(argv[5]); // tempo maximo antes de fazer um novo pedido
    int max_consumo = atoi(argv[6]); // tempo maximo de consumo de uma bebida

    pthread_t threads_clientes[n];
    pthread_t threads_garcons[g];

    bar_t* bar = malloc(sizeof(bar_t));
    bar->rodada = 0;
    bar->maxRodadas = rodadas;
    bar->fechouBar = 0;

    cliente_args_t clientes;
    clientes.tempoMaxConsumo = max_consumo;
    clientes.tempoMaxConversa = max_conversa;
    clientes.bar = bar;

    garcom_args_t garcons[g];

    for (int i = 0; i < g; i++) {
        garcons[i].id = i;
        garcons[i].capacidade = gn;
        garcons[i].clientesAtendidos = 0;
        garcons[i].bar = bar;
    }

    // Criação de Threads
    for (int i = 0; i < n; i++)
        pthread_create(&threads_clientes[i], NULL, thread_cliente, (void*)&clientes);

    for (int i = 0; i < g; i++)
        pthread_create(&threads_garcons[g], NULL, thread_garcom, (void*)&garcons[i]);

    // Sincronização das Threads
    for (int i = 0; i < n; i++)
        pthread_join(threads_clientes[i], NULL);

    for (int i = 0; i < g; i++)
        pthread_join(threads_garcons[i], NULL);
    
    free(bar);

    return 0;
}