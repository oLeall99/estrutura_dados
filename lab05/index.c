#include <stdio.h>

#define LEN 100

typedef struct {
	char data[LEN];
	int head;
	int tail;
	int qtde;
} Queue;

int is_full(Queue *q){
    return q->qtde == LEN;
}

int is_empty(Queue *q){
    return q->qtde == 0;
}

void enqueue(Queue *queue, char caracter) {
    if(is_full(queue)){
        return;
    }
    queue->data[queue->tail % LEN] = caracter;
    queue->tail++;
    queue->qtde++;
}

char dequeue(Queue *queue) {
    if(is_empty(queue)){
        return 0;
    }
    char value = queue->data[queue->head];
    queue->head++;
    queue->qtde--;

    return value;
}

void show(Queue *queue) {
    for(int i = queue->head; i < queue->tail; i++){
        printf("%c", queue->data[i % LEN]);
    }
}

void start_queue(Queue *queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->qtde = 0;
}

int verify_expression(Queue *queue) {
    int flag = 1;
    if(is_empty(queue)){
        return 0;
    }

    Queue q;
    start_queue(&q);
    Queue *pq = &q;

    while(1){
        char current_item = dequeue(queue);
        if(current_item == 0){
            break;
        }

        if(current_item == '('){
            enqueue(pq, current_item);
        }
        else if(current_item == ')'){
            if( dequeue(pq) == 0){
                flag = 0;
                return flag;
            }
        
        }
        show(queue);
    }

    if(pq->qtde != 0){
        flag = 0;
        return flag;
    }

    return flag;
}


int main(void) {
    char s[LEN];
    fgets(s, sizeof(s), stdin);
    Queue queue;
    
    start_queue(&queue);

    for (int i = 0; s[i] != '\0'; i++) {
        enqueue(&queue, s[i]);
    }


    if(verify_expression(&queue) == 0){
        printf("incorreto\n");
    }
    else{
        printf("correto\n");
    }
    
    return 0;
}
