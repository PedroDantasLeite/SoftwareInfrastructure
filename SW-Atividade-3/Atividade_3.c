#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int i;
int min = 9999999;
int max = 0;
float media = 0;
int lista[500];
int total;

void* mediaFunc(){

	for (i = 0; i < total; i++){
		media = media + lista[i];
	}
	media = media/total;
}
void* minFunc(){
	for (i = 0; i < total; i++){
		if(lista[i] < min){
			min = lista[i];
		}
	}
}
void* maxFunc(){
        for (i = 0; i < total; i++){
                if(lista[i] > max){
                        max = lista[i];
                }
	}
}


int main (void) {
	int  num;
	scanf("%d",&total);
	getchar();
	for(i = 0; i < total; i++){
		scanf("%d",&num);
		getchar();
		lista[i] = num;
	}
	int res;
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	pthread_create(&t1,NULL, &mediaFunc, NULL);
	pthread_join(t1,NULL);
	pthread_create(&t2,NULL, &maxFunc, NULL);
	pthread_join(t2,NULL);
	pthread_create(&t3,NULL, &minFunc, NULL);
	pthread_join(t3,NULL);
	printf("The average value is %f\n",media);
	printf("The minimun value is %d\n",min);
	printf("The maximum value is %d\n",max);
        
	return 0;

}
