#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ab_print.h"
#include <assert.h>

struct no{
    elem info;
    no_t *esq, *dir;
};

arvore_t *criar(){
    arvore_t *arvore;
    arvore = malloc(sizeof(arvore_t));
    arvore->raiz = NULL;

    return arvore;
};

void preencher_arvore(arvore_t *arvore){
    int num_nos, id_no, id_esq_no, id_dir_no, posicao;
    scanf("%d", &num_nos);

    for(int i = 0; i < num_nos; i++){
        scanf("%d %d %d", &id_no, &id_esq_no, &id_dir_no);
        
        if(id_no == 0) //significa ser o primeiro no, entao salva como raiz
            inserir_esq(arvore, id_no, -1);

        if(id_esq_no != -1) //aloca cada id em seu no se esse id nao for igual -1
            inserir_esq(arvore,id_esq_no,id_no);
        if(id_dir_no != -1)
            inserir_dir(arvore,id_dir_no,id_no);
    }
}

void finalizar(no_t *raiz){
    if(raiz != NULL){
        finalizar(raiz->esq);
        finalizar(raiz->dir);
        free(raiz); 
    }
};

// retorna de forma recursiva a altura a partir da raiz verificada
int altura(no_t *raiz){
    if(raiz == NULL)
        return 0;
    int alt_esq = 1 + altura(raiz->esq);
    int alt_dir = 1 + altura(raiz->dir);
    if(alt_esq > alt_dir) 
        return alt_esq;
    return alt_dir;
};
// busca se um elemento se encontra na arvore, 
// se positivo retorna seu no
no_t *busca(no_t *raiz, elem x){
    if(raiz == NULL)
        return NULL;

    if(raiz->info == x)
        return raiz;

    no_t *p = busca(raiz->esq, x);
    if(p == NULL)
        p = busca(raiz->dir, x);

    return p;
};

// busca se um elemento se encontra na arvore, 
// se positivo retorna seu no pai

int inserir_esq(arvore_t *a, elem x, elem pai){
    no_t *p = malloc(sizeof(no_t));
    p->esq = NULL;
    p->dir = NULL;
    p->info = x;

    // verifica se deve salvar como raiz
    if(pai == -1){
        if(a->raiz == NULL){
            a->raiz = p;
        }else{
            free(p);
            return 0;
        }
    } else{
        // procura o no onde deve ser inserido esta nova informacao
        no_t *aux = busca(a->raiz, pai);
        if(aux != NULL && aux->esq == NULL){
            // se ja tiver informacao filho desse no, entao nao salva 
            aux->esq = p;
        }else{
            free(p);
            return 0;
        }
    }

    return 1;
};
int inserir_dir(arvore_t *a, elem x, elem pai){
    no_t *p = malloc(sizeof(no_t));
    p->esq = NULL;
    p->dir = NULL;
    p->info = x;

    if(pai == -1){
        if(a->raiz == NULL){
            a->raiz = p;
        }else{
            free(p);
            return 0;
        }
    } else{
        no_t *aux = busca(a->raiz, pai);
        if(aux != NULL && aux->dir == NULL){
            aux->dir = p;
        }else{
            free(p);
            return 0;
        }
    }

    return 1;
};

int print_filho(no_t *filho){
    if(filho == NULL)
        return -1;
    return filho->info;
}

char *print_tipo(no_t *raiz, int pai){
    // verifica se possui filhos ou nao 
    if(pai == -1)
        return "raiz";
    else if(raiz->esq == NULL && raiz->dir == NULL)
        return "folha";
    else
        return "interno";
}

// verifica se todos os filhos de um pai estao alocados
int print_grau(no_t *raiz){
    int grau = 2;
    if(raiz->esq == NULL) 
        grau--;
    if(raiz->dir == NULL) 
        grau--;

    return grau;
}

void print(no_t *raiz, int pai){

    printf("no %d: pai = %d, altura = %d, grau = %d, filhos = (%d,%d), tipo = %s\n", 
        raiz->info, pai, altura(raiz), print_grau(raiz),print_filho(raiz->esq), print_filho(raiz->dir), print_tipo(raiz, pai));

    // chama de forma recursiva a funcao print para inprimir a 
    // informacao de todos os nos ate chegar a um no folha
    if(raiz->esq != NULL)
        print(raiz->esq, raiz->info);
    if(raiz->dir != NULL)
        print(raiz->dir, raiz->info);
}