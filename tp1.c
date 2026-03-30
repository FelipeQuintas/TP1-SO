#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define limite 100

int total_impressoes = 0;
int vencedor = -1;

pthread_mutex_t mutex;
pthread_barrier_t barreira;

typedef struct {
    int id;
} ThreadData;

void* funcao_thread(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int id = data->id;

    // Barreira
    pthread_barrier_wait(&barreira);
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);

        // Quando der os 100 numeros, acaba
        if (total_impressoes >= limite) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        printf("Thread %d: %d\n", id, i);
        total_impressoes++;

        // Diz quem ganhou
        if (total_impressoes == limite && vencedor == -1) {
            vencedor = id;
        }
        pthread_mutex_unlock(&mutex);
        sched_yield();
    }
    pthread_exit(NULL);
}

int main() {
    int num_threads;
    printf("Digite a quantidade de threads: ");
    scanf("%d", &num_threads);

    //Alocação
    pthread_t* threads = malloc(sizeof(pthread_t) * num_threads);
    ThreadData* dados = malloc(sizeof(ThreadData) * num_threads);
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barreira, NULL, num_threads);

    //Criação das threads
    for (int i = 0; i < num_threads; i++) {
        dados[i].id = i;
        pthread_create(&threads[i], NULL, funcao_thread, &dados[i]);
    }
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Resultado 
    printf("\nThread vencedora: %d\n", vencedor);

    // Libera
    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barreira);
    free(threads);
    free(dados);
    return 0;
}