#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura para representar um cliente
typedef struct {
    int id;
    int tempoConversa;
    int tempoConsumo;
} Cliente;

// Estrutura para representar um garçom
typedef struct {
    int capacidade;
    int clientesAtendidos;
} Garcom;

int main() {
    srand(time(NULL));
    
    int N = 100; // Número de clientes
    int G = 3;   // Número de garçons
    int Gn = 5;  // Capacidade de cada garçom
    int R = 10;  // Número de rodadas
    
    Cliente clientes[N];
    Garcom garcons[G];
    
    // Inicializa os garçons
    for (int i = 0; i < G; i++) {
        garcons[i].capacidade = Gn;
        garcons[i].clientesAtendidos = 0;
    }
    
    // Inicializa os clientes
    for (int i = 0; i < N; i++) {
        clientes[i].id = i;
        clientes[i].tempoConversa = rand() % 10 + 1;
        clientes[i].tempoConsumo = rand() % 15 + 1;
    }
    
    for (int rodada = 1; rodada <= R; rodada++) {
        printf("Rodada %d\n", rodada);
        
        for (int i = 0; i < N; i++) {
            // Simula o tempo de conversa
            sleep(clientes[i].tempoConversa);
            
            // Verifica se o cliente pode fazer um pedido
            for (int j = 0; j < G; j++) {
                if (garcons[j].capacidade > 0) {
                    printf("Cliente %d fez um pedido.\n", clientes[i].id);
                    garcons[j].capacidade--;
                    garcons[j].clientesAtendidos++;
                }
            }
            
            // Simula o tempo de consumo
            sleep(clientes[i].tempoConsumo);
        }
        
        // Verifica se todos os garçons atenderam seus clientes
        int todosAtendidos = 1;
        for (int j = 0; j < G; j++) {
            if (garcons[j].clientesAtendidos < Gn) {
                todosAtendidos = 0;
                break;
            }
        }
        
        if (todosAtendidos) {
            printf("Todos os clientes foram atendidos. Próxima rodada!\n");
            // Reinicializa os garçons
            for (int j = 0; j < G; j++) {
                garcons[j].capacidade = Gn;
                garcons[j].clientesAtendidos = 0;
            }
        } else {
            printf("Aguardando os garçons atenderem todos os clientes...\n");
        }
    }
    
    return 0;
}