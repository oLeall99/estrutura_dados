#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice{
	int valor;
	struct Vertice* esq;
	struct Vertice* dir;
	struct Vertice* pai;
} Vertice;

typedef struct Arvore{
	Vertice* raiz;
	int qtde;
} Arvore;

void in_ordem(Vertice *raiz) {
    if (raiz != NULL) {
        in_ordem(raiz->esq);
        printf("%d ", raiz->valor);
        in_ordem(raiz->dir);
    }
}

void pre_ordem(Vertice *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->valor);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

void pos_ordem(Vertice *raiz) {
    if (raiz != NULL) {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

Vertice *cria_vertice(int valor){
	Vertice* novo = malloc(sizeof(Vertice));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;
	novo->valor = valor;
	
	return novo;
}

Arvore *cria_arvore(){
	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}

void inserir(Arvore* arvore, int valor){
	Vertice* novo = cria_vertice(valor);

	Vertice* anterior = NULL;
	Vertice* atual = arvore->raiz;

	while(atual != NULL){
		anterior = atual;
		if(valor <= anterior->valor){
			atual = atual->esq;
		}else{
			atual = atual->dir;
		}
	}

	novo->pai = anterior;
	if(anterior != NULL){
		if(valor <= anterior->valor){
			anterior->esq = novo;
		}else{
			anterior->dir = novo;
		}
	}else{
		arvore->raiz = novo;
	}
}

void remover_vertice(Arvore* arvore, Vertice* vertice) {
    int filhos = 0;
    int filho_dir = 0;
    int filho_esq = 0;
    int pai_pos = 0; // 0 : vertice é filho esquerdo, 1 : é filho direito

    if(vertice->esq != NULL){
        filhos++;
        filho_esq = 1;
    }
    if(vertice->dir !=NULL){
        filhos++;
        filho_dir = 1;
    }

    if(vertice->pai->dir == vertice){
        pai_pos = 1;
    }

    if(filhos == 0){
        if(arvore->raiz == vertice) {
            arvore->raiz = NULL;
        }
        else {
            if(vertice->pai->dir != vertice){
                vertice->pai->esq = NULL;
            } 
            else {
                vertice->pai->dir = NULL;
            }
        }
    }
    else if(filhos == 1) {
        if(arvore->raiz == vertice){
            if(filho_dir){
                arvore->raiz = vertice->dir;
            }
            else {
                arvore->raiz = vertice->esq;
            }
        }
        else {
            if(!pai_pos && filho_esq) {
                vertice->pai->esq = vertice->esq;
                vertice->esq->pai = vertice->pai;
            }
            else if(!pai_pos && filho_dir) {
                vertice->pai->esq = vertice->dir;
            vertice->dir->pai = vertice->pai;
            }
            else if(pai_pos && filho_esq) {
                vertice->pai->dir = vertice->esq;
                vertice->esq->pai = vertice->pai;
            }
            else {
                vertice->pai->dir = vertice->dir;
                vertice->dir->pai = vertice->pai;
            }
        }
    }
    else if(filhos == 2) {
        Vertice *anterior = vertice->esq;
        Vertice *atual = vertice->esq->dir; 
        while(atual != NULL){
            anterior = atual;
            atual = atual->dir;
        }
        anterior->pai->esq = NULL;
        anterior->pai = vertice->pai;
        
        if(!pai_pos){
            vertice->pai->esq = anterior; 
        }

        anterior->dir = vertice->dir;
        anterior->esq = vertice->esq;
        anterior->dir->pai = anterior;
        anterior->esq->pai = anterior;
    }
    arvore->qtde--;
    free(vertice);
}





Vertice *buscar_valor(Arvore* arvore, int valor){
	Vertice* atual = arvore->raiz;
	while(atual != NULL){
		if(valor < atual->valor){
			atual = atual->esq;
		}else if(valor > atual->valor){
			atual = atual->dir;
		}else{
			return atual;
		}
	}
	return NULL;
}


int main(void) {
	int dados[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
  	Arvore *arvore = cria_arvore();
  	
	for(int i = 0; i < 10; i++){
		inserir(arvore, dados[i]);
		printf("Inseriu %d mostra em ordem -> ", dados[i]);
		in_ordem(arvore->raiz);
		printf("\n");
		printf("Inseriu %d mostra em pré-ordem -> ", dados[i]);
		pre_ordem(arvore->raiz);
		printf("\n");
		printf("Inseriu %d mostra em pós-ordem -> ", dados[i]);
		pos_ordem(arvore->raiz);
		printf("\n");
	}

	for(int i = 0; i < 10; i++){
		Vertice *vertice = buscar_valor(arvore, dados[i]);
		if(vertice != NULL){
			remover_vertice(arvore, vertice);
		}
		printf("Removeu %d mostra em ordem -> ", dados[i]);
		in_ordem(arvore->raiz);
		printf("\n");
		printf("Removeu %d mostra em pré-ordem -> ", dados[i]);
		pre_ordem(arvore->raiz);
		printf("\n");
		printf("Removeu %d mostra em pós-ordem -> ", dados[i]);
		pos_ordem(arvore->raiz);
		printf("\n");
	}

	free(arvore);
		
    return 0;
}
