#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>

void *produzir(void*);
void *consumir(void*);
int searchPro();
int searchCon();
int *buffer;
int tamanho = 0;
int *xis;
int limite = 0;
sem_t mutex;

int main(){
    int produtoresTam = 0;
    int consumidoresTam = 0;
    sem_init(&mutex, 0, 1);

    scanf("%d %d %d %d", &produtoresTam, &consumidoresTam, &limite, &tamanho);

    pthread_t consumidores[consumidoresTam];
    pthread_t produtores[produtoresTam];

    int conId[consumidoresTam];
    int proId[produtoresTam];
    buffer = (int*) malloc(tamanho *sizeof(int));
    xis = (int*) malloc(produtoresTam *sizeof(int));
    
    for (int i = 0; i < produtoresTam; i++){
        xis[i] = 0;
    }

    for (int i = 0; i < tamanho; i++){
        buffer[i] = 0;
    }
    
    for (int i = 0; i < consumidoresTam; i++){
        conId[i] = i;
    }

    for (int i = 0; i < produtoresTam; i++){
        proId[i] = i;
    }

    for (int i = 0; i < produtoresTam; i++){
        pthread_create(&produtores[i], NULL, produzir, &proId[i]);
    }

    for (int i = 0; i < consumidoresTam; i++){
        pthread_create(&consumidores[i], NULL, consumir, &conId[i]);
    }

    for (int i = 0; i < produtoresTam; i++)
	pthread_join(produtores[i], NULL);

    for (int i = 0; i < consumidoresTam; i++)
	pthread_join(consumidores[i], NULL);

    return 0;   
}

void *produzir(void* id){
    while(1){
        int *i = id;
        int temp = 2*xis[*i]+1;
        if (temp > limite){
            xis[*i] = 0;
        }
        else{
            xis[*i] = temp;
        }
        while(1){
            int j = searchPro();
            if (j != -1){
                sem_wait(&mutex);
                buffer[j] = temp;
                printf("Produtor %d produzindo %d na posição %d\n", *i, temp, j);
                sem_post(&mutex);
                break;
            }
        }
    }
}

void *consumir(void* id){
    int *i = id;
    while(1){
        while(1){
            int j = searchCon();
            if(j != -1){
                sem_wait(&mutex);
                printf("Consumidor %d consumindo %d da posição %d\n", *i, buffer[j], j);
                buffer[j] = 0;
                sem_post(&mutex);
                break;
            }
        }
    }
}

int searchPro (){
    for (int i = 0; i < tamanho; i++){
        if (buffer[i] == 0){
            return i;
        }
    }
    return -1;
}

int searchCon (){
    for (int i = 0; i < tamanho; i++){
        if (buffer[i] != 0){
            return i;
        }
    }
    return -1;
}