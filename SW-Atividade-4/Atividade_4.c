#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



struct processWaiting{
        int chegada;
        int tamanho;
        struct processWaiting *next;
    };

struct processRunning{
        int processos;
        int entrouQuando;
        int comeco;
        struct processRunning *next;
    };

struct processRunning *headRu = NULL;
struct processWaiting *headWa = NULL;

void pushWaiting(struct processWaiting *headWa, int chegadaQ, int tamanhoQ);
void pushRunning(struct processRunning *headRu, int v1, int v2);
void transfer(struct processWaiting *headWa, struct processRunning *headRu, int i);
void count(struct processRunning *headRu, int rr, int i);
void pop(struct processRunning **headRu);
void ftl(struct processRunning **headRu);


int main(){
    int quantProcessos = 0, quantum = 0, entrada = 0, termino = 0, tempoTotal = 0;
    scanf("%d %d",&quantProcessos, &quantum);
    getchar();
    for (int i = 0; i < quantProcessos; i++){
        scanf("%d %d", &entrada, &termino);
        getchar();
        if (headWa == NULL){
            headWa = (struct processWaiting *) malloc(sizeof(struct processWaiting));
            headWa -> chegada = entrada;
            headWa -> tamanho = termino;
            headWa -> next = NULL;
        }
        else{
        pushWaiting(headWa, entrada, termino);
        }
        tempoTotal = tempoTotal + termino;
    }
    headRu = (struct processRunning *) malloc(sizeof(struct processRunning));
    int rr = quantum;
    for(int i = 0; i < tempoTotal; i ++ ){
        transfer(headWa, headRu, i);
        count(headRu,rr, i);
        if (headRu -> processos == 0){
            printf("RR %d %d %d\n", i - headRu -> entrouQuando + 1, headRu -> comeco - headRu -> entrouQuando, i - headRu -> comeco + 1);
            pop(&headRu);
        }
        rr--;
        if (rr == 0){
            rr = 2;
            ftl(&headRu);
        }

    }
    return 0;
}

void pushWaiting(struct processWaiting *headWa, int chegadaQ, int tamanhoQ){
    struct processWaiting *novo = headWa;
    while(novo -> next != NULL){
        novo = novo->next;
    }
        
    novo -> next = (struct processWaiting *) malloc(sizeof(struct processWaiting));
    novo -> next -> chegada = chegadaQ;
    novo -> next -> tamanho = tamanhoQ;
    novo -> next -> next = NULL;

}

void transfer(struct processWaiting *headWa, struct processRunning *headRu, int i){
    struct processWaiting *novoWa = headWa;
    struct processRunning *novoRu = headRu;

    while (novoWa != NULL){
        if (novoWa -> chegada == i){
            pushRunning(novoRu, novoWa -> tamanho, i);
        }
        novoWa = novoWa -> next;
    }
}

void pushRunning(struct processRunning *headRu, int v1, int v2){
    struct processRunning *novo = headRu;
    if (novo -> processos == 0){
        novo ->  processos = v1;
        novo ->  entrouQuando = v2;
        novo -> comeco = -1;
        novo ->  next = NULL;
    }
    else{
        while(novo -> next != NULL){
            novo = novo -> next;
        }
        novo -> next = (struct processRunning *) malloc(sizeof(struct processRunning));
        novo -> next -> processos = v1;
        novo -> next -> entrouQuando = v2;
        novo -> next -> comeco = -1;
        novo -> next -> next = NULL;
    }
}

void count(struct processRunning *headRu, int rr, int i){
    struct processRunning *novo = headRu;
    if (novo -> comeco == -1){
        novo -> comeco = i;
    }
    novo -> processos = novo -> processos - 1;
}

void pop(struct processRunning **headRu){
    struct processRunning *temp;
    temp = *headRu;
    *headRu = temp -> next;
    free(temp);
}

void ftl(struct processRunning **headRu){
    struct processRunning *temp, *temp2;
    temp = *headRu;
    if (temp == NULL){
        return;
    }
    if (temp -> next == NULL){
        return;
    }
    while (temp -> next != NULL){
        temp = temp -> next;
    }
    temp2 = *headRu;
    *headRu = temp2 -> next;
    temp -> next = (struct processRunning *) malloc(sizeof(struct processRunning));
    temp -> next -> processos = temp2 -> processos;
    temp -> next -> entrouQuando = temp2 -> entrouQuando;
    temp -> next -> comeco = temp2 -> comeco;
    temp -> next -> next = NULL;
}