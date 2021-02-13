#include <stdio.h>
#include <stdlib.h>
#include "back.h"

lista_t *criar(){
    lista_t *l = malloc(sizeof(lista_t));
    l->inicio = NULL;
    l->fim = NULL;

    return l;
}

int liberar(lista_t *l){
    if(l != NULL){
        no_t *aux = l->inicio;
        while(aux != NULL){
            l->inicio = l->inicio->prox;
            free(aux);
            aux = l->inicio;
        }
        free(l);
    }
};

int remover(lista_t *l, int n){
    remover_back(l, n);
    no_t *p = l->inicio;
    no_t *ant = NULL;

    while(p != NULL && p->chave != n){
        ant = p;
        p = p->prox;
    };

    if(p == NULL) return 0;

    if(ant == NULL){
        // se o elemento for o primeiro da lista a lista 
        // desloca seu inicio 1 posicao para frente 
        l->inicio = l->inicio->prox;
        if(l->inicio != NULL) l->inicio->ant = NULL;
        else l->fim = NULL;
        free(p);
    }
    else{
        // se for o ultimo, faz do elemento anterior o final 
        if(p->prox == NULL){
            l->fim = p->ant;
            ant->prox = NULL;
            free(p);
        }
        // se estiver no meio conecta o elemento anterior
        // a ele e posterior a ele um ao outro 
        else{
            ant->prox = p->prox;
            p->prox->ant = ant;
            free(p);
        }
    }
    return 1;
};

int inserir(lista_t *l, int c, int back, int tempo){
    no_t *p = malloc(sizeof(no_t));
    p->chave = c;
    p->prox = NULL;
    p->ant = NULL;
    p->backward = NULL;
    p->tempo = tempo;

    if(l->inicio == NULL){
        l->inicio = p;
    }
    else{
        p->ant = l->fim;
        l->fim->prox = p;
    }
    l->fim = p;

    if(back != 0)
        l->fim->backward = backward(l, back);
    
    l->tam++;
};

void imprimir(lista_t *l){
    no_t *p;
    int chave = -1;
    p = l->inicio;
    while(p != NULL){
        printf("[%d,%d", p->chave, p->tempo);
        // se backward aponta para alguma posicao imprime sua posicao
        if(p->backward != NULL){
            chave = buscar(l, p->backward->tempo);
            printf(",%d", chave);
        }
        printf("] ");
        p = p->prox;
        chave = 0;
    }
    if(chave == -1) 
        printf("-1");
    
    printf("\n");
};

// busca o elemento de backward e retorna sua posicao 
int buscar(lista_t *l, int tempo){
    no_t *p;
    int pos = 0;

    p = l->inicio;
    while(p != NULL){
        if(p->tempo == tempo){
            return pos;
        }
        else{
            p = p->prox;
            pos++;
        }
    }

    return -1;
}

// se outros elementos possuem um ponteiro 
// para backward removido ira apontar para NULL
void remover_back(lista_t *l, int n){
    no_t *p;
    p = l->inicio;
    while(p != NULL){
        if(p->backward != NULL){
            if(p->backward->chave == n){
                p->backward = NULL;
            }
        }
        p = p->prox;
    }
};

// a partir do elemento, conta ate j para 
// chegar ao elemento que sera o backward 
no_t *backward(lista_t *l, int j){
    no_t *aux = aux = l->fim;

    for(int i = 0; i < j; i++){
        aux = aux->ant;
    }

    return aux;
}
