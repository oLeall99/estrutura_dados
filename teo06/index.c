#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int valor;
    struct item *proximo;
    struct item *anterior;
} Item;

typedef struct Queue {
    Item *head;
    Item *tail;
    int qtde;
} Queue;

Queue *criar_queue(){
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->qtde = 0;

    return q;
}

Item *criar_item(int valor){
    Item *novo_item = malloc(sizeof(Item));
    novo_item->valor = valor;
    novo_item->anterior = NULL;
    novo_item->proximo = NULL;
    
    return novo_item;
}

int is_empty(Queue *q){
    return q->qtde == 0;
}

void enqueue(Queue *queue, int valor){
    Item *novo = criar_item(valor);
    if(is_empty(queue)){
        queue->head = novo;
        queue->tail = novo;
        queue->qtde++;
        return;
    }

    queue->tail->proximo = novo;
    novo->anterior = queue->tail;

    queue->tail = novo;
    queue->qtde++;
}

int dequeue(Queue *queue){
    if(is_empty(queue)){
        return 0;
    }

    Item *item;
    if(queue->qtde == 1){
        item = queue->head; 
        queue->head = NULL;
    }
    else {
        item = queue->tail;
        queue->tail = item->anterior;
        queue->tail->proximo = NULL;
    }
    int valor = item->valor;
    queue->qtde--;
    free(item);
    return valor;
}

void show(Queue *q){
    Item *item = q->head;
    while(item != NULL){
        printf("%d ", item->valor);
        item = item->proximo;
    }
    printf("\n");
}


int main(){
    Queue *q = criar_queue();

    for(int i = 0; i < 15; i++){
        enqueue(q, i);
        show(q);
    }
    
    for(int j = 0; j < 15; j++){
        printf("Valor removido: %d\n", dequeue(q));
        show(q);
    }
}