#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_t threads[4];
pthread_mutex_t mutex;
int vencedor = -1;
int terminou = 0;

void* soma_individual(void* arg) {
    int id = *(int*)arg;  
    free(arg);
    
    int soma_local = 0;

    while (1) {
        if (terminou) break; //caso alguma das threads já tenha vencido
        int numero = rand() % 11 + 1;  //random de 1 a 11
        sleep(1);
        soma_local += numero;
        printf("Thread %d somou %d, total na mao: %d\n", id, numero, soma_local);

        if (soma_local == 21) {  //verifica se a soma é exatamente 21
            pthread_mutex_lock(&mutex);
            if (!terminou) {
                terminou = 1;
                vencedor = id;
            }
            pthread_mutex_unlock(&mutex);
            break;
        } else if (soma_local > 21) {  //verifica se a soma passou de 21
            printf("\nThread %d estourou, passou de 21\n\n", id);
            break;
        }
    }
    return NULL;
}

int main(void) {
    srand(time(NULL));                
    pthread_mutex_init(&mutex, NULL);
    printf("Inicio\n");

    for (int i = 0; i < 4; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;                  
        pthread_create(&threads[i], NULL, soma_individual, id);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    if (vencedor != -1) {
        printf("\nFim, a Thread %d fez 21 primeiro\n\n", vencedor);
    } else {
        printf("\nNenhuma thread atingiu exatamente 21\n");
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
