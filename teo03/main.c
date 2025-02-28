#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    struct Celula *ant;
    struct Celula *prox;
    int valor;
}Celula;

typedef struct {
    Celula *primeiro;
    int qtd;
} LDDE;

Celula *criar_celula(int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->ant = NULL;
    novo->prox = NULL;
    novo->valor = valor;
    
    return novo;
}

LDDE *criar_lista(){
    LDDE *lista = malloc(sizeof(LDDE));
    lista->primeiro = NULL;
    lista->qtd = 0;
    
    return lista;
}

void inserir(LDDE *lista, int valor){
    Celula *novo = criar_celula(valor);
    Celula *anterior = NULL;
    Celula *atual = lista->primeiro;

    while (atual != NULL && atual->valor < novo->valor)
    {
        anterior = atual;
        atual = atual->prox;
    }

    //Add termo em uma lista vazia
    if (lista->qtd == 0)
    {
        lista->primeiro = novo;
    }
    
    //Add termo em uma lista não vazia na primeira posição
    else if(anterior == NULL && atual != NULL)
    {
        lista->primeiro = novo;
        novo->prox = atual;
        atual->ant = novo;
    }

    //Add termo no fim da lista
    else if(anterior != NULL && atual == NULL){
        anterior->prox = novo;
        novo->ant = anterior;
    }

    //Add termo no meio da lista
    else{
        anterior->prox = novo;
        novo->ant = anterior;
        novo->prox = atual;
        atual->ant = novo;

        
    }

    lista->qtd++;
}


void mostrar(LDDE *lista){
    Celula *atual = lista->primeiro;
    printf("Início -> ");
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual= atual->prox;
    }
    printf("<- Final\n");
}

int main(){
    LDDE *lista = criar_lista();

    for(int i = 10; i > 0; i--){
        inserir(lista, i);
        mostrar(lista);
      }

    return 0;
}