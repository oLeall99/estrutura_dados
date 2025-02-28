#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
  int value;
  struct Celula *next;
}Celula;

typedef struct {
  int qtd;
  Celula *first;
} LDE;

Celula *criar_celula(int value){
  Celula *new = malloc(sizeof(Celula));
  new->next = NULL;
  new->value = value;

  return new;
}


LDE *criar_list(){
  LDE *list = malloc(sizeof(LDE));
  list->first = NULL;
  list->qtd = 0;

  return list;
};

void insert(LDE *list, int value){
  Celula *new = criar_celula(value);
  if( list->first == NULL ){
    list->first = new;
    list->qtd++;
    return;
  }

  Celula *anterior = NULL;
  Celula *current = list->first;
  while(current != NULL && current->value < new->value){
    anterior = current;
    current = current->next;
  }
  
  if(anterior == NULL){
    list->first = new;
    
  }else {
    anterior->next = new;
    new->next = current;
  }

  list->qtd++;
}

void remover(LDE *list, int value){
  if( list->first == NULL ){
    return;
  }
  
  Celula *anterior = NULL;
  Celula *current = list->first;
  while(current != NULL || current->value != value){
    anterior = current;
    current = current->next;
  }

  if(current == list->first && list->qtd == 1){
    list->first = NULL;
  }
  else if(current == list->first){
    list->first = current->next;
  }
  else {
    anterior->next = current->next;
  }
  free(current);
  list->qtd--;
}

void show(LDE *list){
  Celula *current= list->first;
  while (current != NULL){
    printf("%d ", current->value);
    current = current->next; 
  }
  printf("\n");
  
}

int main(){
  LDE *list = criar_list();
  for(int i = 10; i > 0; i--){
    insert(list, i);
    show(list);
  }
  
}