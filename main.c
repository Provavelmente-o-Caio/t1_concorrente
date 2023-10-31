// Grupo: Caio Ferreira Cardoso, Gabriel Reimann Cervi, Lucas Brand Martins

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "cliente.h"
#include "garcom.h"

int n, g, gn, num_rodadas, max_consumo, max_conversa; // Variáveis para parâmetros da simulação
int fechouBar = 0; // Uma flag para controlar quando o bar fecha
int rodada = 0;    // Acompanha a rodada atual
int iniciouRodada = 0; // Sinaliza se uma rodada começou
int rodada_finalizada = 0; // Sinaliza se a rodada está finalizada
garcom_t** lista_garcons = NULL;  // Array de garçons (waiters)
cliente_t** lista_clientes = NULL; // Array de clientes
pthread_mutex_t mut_rodada; // Mutex para sincronização da variável 'rodada'


void* thread_cliente(void* arg) {
    // Simula as açoes de um cliente
    cliente_t* cliente = (cliente_t*) arg;
    while(!fechouBar) {
        conversaComAmigos(cliente); 
        fazPedido(cliente); 
        esperaPedido(cliente); 
        recebePedido(cliente); 
        consomePedido(cliente); 
        while(!rodada_finalizada); 
        if (rodada == num_rodadas)
            fechouBar = 1; // Fecha o bar após todas as rodadas
    }
    pthread_exit(NULL);
}


void* thread_garcom(void* arg) {
    // Simula as ações de um garçom
    garcom_t* garcom = (garcom_t*) arg;
    while(!fechouBar) {
        pthread_mutex_lock(&mut_rodada);
        if (iniciouRodada == 0) {
            printf("Rodada: %d\n", rodada); // Serve como parâmetro para fechar o bar
            iniciouRodada = 1;
        }
        pthread_mutex_unlock(&mut_rodada);
        recebeMaximoPedidos(garcom);
        registraPedidos(garcom);
        entregaPedidos(garcom);

        rodada_finalizada = verificaSeRodadaTerminou();
        if (rodada_finalizada) {
            rodada++;
            iniciouRodada = 0;
            pthread_mutex_unlock(&mut_rodada);
        }
        if (rodada == num_rodadas)
            fechouBar = 1;
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    // Verifica se foram passados argumentos corretos
    if (argc < 7) {
        printf("Uso: %s [clientes] [garcons] [clientes/garcons] [rodadas] [max_conversa] [max_consumo]\n", argv[0]);
        return 1;
    }
    
    // Verifica se os argumentos são maiores que zero
    for (int i = 1; i <= 6; i++) {
        if(atoi(argv[i]) <= 0) {
            printf("Todos os números precisam ser maior que 0\n");
            fflush(stdout);
            return 1;
        }
    }

    // Lê os valores dos argumentos
    n = atoi(argv[1]); // Número de clientes
    g = atoi(argv[2]); // Número de garçons
    gn = atoi(argv[3]); // Capacidade de atendimento
    num_rodadas = atoi(argv[4]); // Número de rodadas
    max_conversa = atoi(argv[5]); // Tempo máximo antes de fazer um novo pedido
    max_consumo = atoi(argv[6]); // Tempo máximo de consumo de uma bebida

    // Verifica se o número de clientes é compatível com a capacidade de atendimento
    if (n%(gn*g) != 0 || n < (gn*g)) {
        printf("O número de clientes deve ser maior ou igual e múltiplo da capacidade de cada garçom vezes o número de garçons\n");
        fflush(stdout);
        return 1;
    }
    
    // Inicialização de variáveis e estruturas de dados
    pthread_t threads_clientes[n];
    pthread_t threads_garcons[g];

    pthread_mutex_init(&mut_rodada, NULL);

    srand(time(NULL));

    // Inicializa a struct de um garçom e o adiciona na lista
    lista_garcons = (garcom_t**) malloc(g*sizeof(garcom_t));
    for (int i = 0; i < g; i++) {
        garcom_t* garcom = malloc(sizeof(garcom_t));
        garcom->num_pedido = 0;
        garcom->terminou_rodada = 0;
        sem_init(&garcom->sem, 0, 0);
        garcom->fila_clientes = (int*)malloc(gn*sizeof(int));
        lista_garcons[i] = garcom;
    }

    // Inicializa a struct de um cliente e o adiciona na lista
    lista_clientes = (cliente_t**) malloc(n * sizeof(cliente_t));
    for (int i = 0; i < n; i++) {
        cliente_t* cliente = malloc(sizeof(cliente_t));
        lista_clientes[i] = cliente;
        lista_clientes[i]->id = i;
        sem_init(&lista_clientes[i]->sem, 0, 0);
    }

    // Criação de Threads
    for (int i = 0; i < g; i++)
        pthread_create(&threads_garcons[i], NULL, thread_garcom, (void*)lista_garcons[i]);

    for (int i = 0; i < n; i++)
        pthread_create(&threads_clientes[i], NULL, thread_cliente, (void*)lista_clientes[i]);

    // Sincronização das Threads
    for (int i = 0; i < n; i++) {
        pthread_join(threads_clientes[i], NULL);
        sem_destroy(&lista_clientes[i]->sem);
        free(lista_clientes[i]);
    }

    for (int i = 0; i < g; i++) {
        pthread_join(threads_garcons[i], NULL);
        sem_destroy(&lista_garcons[i]->sem);
        free(lista_garcons[i]->fila_clientes);
        free(lista_garcons[i]);
    }

    pthread_mutex_destroy(&mut_rodada);
    free(lista_garcons);
    free(lista_clientes);

    return 0;
}
