#include <stdio.h>
#include <stdlib.h>
#include "josefo.h"


struct no{
    int info;
    no_t *prox;
};

struct lista{
    no_t *inicio, *fim, *sentinela;
    int tam;
};

lista_t *criar(){
    lista_t *l;
    l = malloc(sizeof(lista_t));
    l->inicio = NULL;
    l->fim = NULL;
    l->sentinela = NULL;
    l->tam = 0;

    return l;
}

void destruir(lista_t *l){
    if(l != NULL){
        no_t *p = l->inicio;
            free(p);
    }
}

void inserir(lista_t *l, int x){
    if(l != NULL){
        no_t *p = malloc(sizeof(no_t));
        p->info = x;
        p->prox = NULL;
        if(l->inicio == NULL){
            l->inicio = p;
            p->prox = l->inicio;
        }
        else{
            // invez de l->fim apontar para NULL indicando fim da fila
            // aponta para o primeiro indice desta
            l->fim->prox = p;
            p->prox = l->inicio;
        }
        l->fim = p;
        l->tam++;
    }
}

void remover(lista_t *l, int x){
    if(l != NULL){
        no_t *p = l->inicio, *ant = NULL;
        // verifica se o numero é o primeiro do vetor, ultimo 
        // ou se esta no meio, ira tratar de forma diferente cada caso
        while(p != NULL){
            if(p->info == x){
                if(ant == NULL){
                    l->inicio = l->inicio->prox;
                    l->fim->prox = l->inicio;
                }
                else if(p == l->fim){
                    l->fim = ant;
                    l->fim->prox = l->inicio;
                }
                else{
                    ant->prox = p->prox;
                }
                l->sentinela = p->prox;
                l->tam--;
                free(p);
                // retorna sentinela, que aponta para o indice a frente 
                // do numero que foi eliminado 
                return;
            }
            else{
                ant = p;
                p = p->prox;
            }
        }
    }

}

int tamanho(lista_t *l){
    return l->tam;
}

void rodar_e_rodar(lista_t *l, int k, int *posicao){
    if(l != NULL){
        int i;
        no_t *p;
        if(l->sentinela == NULL){
            p = l->inicio;
        }
        // comeca a contar o numero a partir do indice 
        // da sentinela obtido na funcao remover, se este nao for nulo
        else {
            p = l->sentinela;
        }

        for(i = 1; i < k; i++){
            p = p->prox;
        }
        // retorna o numero que deve ser retirado
        *posicao = p->info;
        l->sentinela = NULL;
    }
};

void printar(lista_t *l, int x){
    if(l != NULL){
        int i = 0;
        no_t *p;
        p = l->inicio;
        while(i != l->tam){
            printf("Caso %d: %d", x, p->info);
            p = p->prox;
            i++;
        };
        printf("\n");
    }
}