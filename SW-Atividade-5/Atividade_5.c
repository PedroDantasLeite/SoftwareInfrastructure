#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int tamanho = 0;
int linha = 0;
int valorTotal = 0;
int num = 0;
int **matriz;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *somaMatriz(void *arg);

int main(void)
{
	scanf("%d", &tamanho);

	matriz = (int **) malloc(tamanho* sizeof(int*));
	for (int i = 0; i < tamanho; i++)
	{
		matriz[i] = (int*) malloc(tamanho* sizeof(int));
	}

	for (int i = 0; i < tamanho; i++)
	{
		for (int j = 0; j < tamanho; j++)
		{
			scanf("%d", &num);
			getchar();
			matriz[i][j] = num;
		}
	}

	pthread_t threads[tamanho];
	for (int i = 0; i < tamanho; i++)
	{
		if (pthread_create(&(threads[i]), NULL, somaMatriz, NULL))
		{
			printf("Thread %d not created", i);
			return 1;
		}
	}

	for (int i = 0; i < tamanho; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("%d\n", valorTotal);

	return 0;
}

void *somaMatriz(void *arg)
{
	pthread_mutex_lock(&mutex);
	for (int j = 0; j < tamanho; j++)
	{
		valorTotal += matriz[linha][j];
	}

	linha++;
	pthread_mutex_unlock(&mutex);
	return arg;
}
