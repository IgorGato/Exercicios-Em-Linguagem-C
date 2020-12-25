#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubro_negra.h"

#define RED 1
#define BLACK 0

//adicionado o campo cor a struct
struct no{
    elem info;
    int cor;
    no_t *esq, *dir;
};

arvore_t *criar(){
    arvore_t *arvore;
    arvore = malloc(sizeof(arvore_t));
    arvore->raiz = NULL;

    return arvore;
};

int vazia(arvore_t *a){
    //verifica se a raiz é NULL, se for a arvore esta vazia 
    if(a->raiz == NULL)
        return 1;
    return 0;
};

//de forma recursiva libera toda memoria alocada para a arvore 
//começa a desalocar e retorna fazendo o mesmo ate a raiz
void finalizar(no_t *raiz){
    if(raiz != NULL){
        finalizar(raiz->esq);
        finalizar(raiz->dir);
        free(raiz); 
    }
};

//imprime todos os numeros salvos na arvore em ordem
//de forma recursiva
void imprimir(no_t *raiz){
    if(raiz != NULL){
        printf("%d(", raiz->info);
        imprimir(raiz->esq);
        printf(",");
        imprimir(raiz->dir);
        printf(")");
    } else
        printf("null");
};

// busca se um elemento se encontra na arvore, 
// se positivo retorna seu nó
no_t *busca(no_t *raiz, elem x){
    if(raiz == NULL)
        return NULL;
    else if(raiz->info == x)
        return raiz;
    else if(x < raiz->info)
        return busca(raiz->esq, x);
    else
        return busca(raiz->dir, x);
};

//faz rotacao para a esquerda
//subindo o no esquerdo para o lugar original da raiz
no_t *ee(no_t *desb){
    no_t *aux = desb->dir;
    desb->dir = aux->esq;
    aux->esq = desb;
    aux->cor = desb->cor;
    //faz sua cor ser vermeha
    desb->cor = RED;
    return aux;
}

//faz rotacao para a esquerda
//subindo o no esquerdo para o lugar original da raiz
no_t *dd(no_t *desb){
    no_t *aux = desb->esq;
    desb->esq = aux->dir;
    aux->dir = desb;
    aux->cor = desb->cor;
    desb->cor = RED;
    return aux;
}

//verifica qual a cor do no
int cor(no_t *h){
    if(h == NULL)
        return BLACK;
    else 
        return h->cor;
}

//inverta a cor do nó pai e seus filhos
void troca_cor(no_t *h){
    h->cor = !h->cor;
    if(h->esq != NULL){
        h->esq->cor = !h->esq->cor;
    }
    if(h->dir != NULL){
        h->dir->cor = !h->dir->cor;
    }
}

no_t *insere_avl(no_t *h, int valor){
    //se a arvore estiver vazia cria um novo nó e o insere
    //ou se o pai que chamou recursivamente nao possui mais filhos,
    //insere a chave como um nó folha deste pai
    if(h == NULL){
        no_t *novo;
        novo = malloc(sizeof(no_t));
        if(novo == NULL){
            return NULL;
        }
        novo->info = valor;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }

    //se a chave ja existir na arvore nao é inserido
    if(valor != h->info){
        //verifica recursivamente onde inserir a chave dependendo se ela é
        //menor ou maior que a informacao do no
        if(valor < h->info){
            h->esq = insere_avl(h->esq, valor);
        }else{
            h->dir = insere_avl(h->dir, valor);
        }
    }

    //verifica as tres regras, se elas foram quebradas,
    //se positivo, entao se rotaciona a arvore e troca cor de seus nos e necessario
    if(cor(h->dir) == RED && cor(h->esq) == BLACK)
        h = ee(h);

    if(cor(h->esq) == RED && cor(h->esq->esq) == RED)
        h = dd(h);

    if(cor(h->esq) == RED && cor(h->dir) == RED)
        troca_cor(h);

    return h;
}

void inserir(no_t **raiz, elem x){
    *raiz = insere_avl(*raiz, x);
    if((*raiz) != NULL)
        (*raiz)->cor = BLACK;

}

//imprime em pre ordem todos os nos
void pre_ordem(no_t *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->info);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

//imprime em ordem numerica todos os nos
void em_ordem(no_t *raiz){
    if(raiz != NULL){
        em_ordem(raiz->esq);
        printf("%d ", raiz->info);
        em_ordem(raiz->dir);
    }
};

//imprime em pos ordem todos os nos
void pos_ordem(no_t *raiz){
    if(raiz != NULL){
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d ", raiz->info);
    }  
};

//segue para a direita da arvore, onde estao os maiores numeros
//ate encontrar um nó direito nulo, entao retornando seu pai
int maior_numero(no_t *raiz){
    if(raiz->dir == NULL)
        return raiz->info;
    else
        maior_numero(raiz->dir);
}

//segue para a esquerda da arvore, onde estao os menores numeros
//ate encontrar um no esquerdo nulo, entao retornando seu pai
int menor_numero(no_t *raiz){
    if(raiz->esq == NULL)
        return raiz->info;
    else
        menor_numero(raiz->esq);
}

void buscaPrePro_aux(no_t *raiz, int key, int opcao){ 
    no_t *num = NULL; 
  
    //escolhe se sera buscado o predecessor ou o numero sucessor
    if(opcao == 2)
        num = buscaPos(raiz, num, key);
    else if(opcao == 3)
        num = buscaPre(raiz, num, key);
    //se a busca retornar NULL significa que nao ha
    //predecessor/sucessor para o numero buscado 
    if (num != NULL) 
        printf("%d\n", num->info); 
    else
        printf("erro\n"); 
    
} 

no_t *buscaPre(no_t *raiz, no_t *pre, int chave){ 
    if (raiz == NULL)  
        return NULL; 

    //se a chave existir na arvore 
    if (raiz->info == chave) 
    { 
        //primeiro vai para o nó a esquerda da atual raiz
        //O maior valor da sub arvore a esquerda sera o predecessor
        if (raiz->esq != NULL) 
        { 
            pre = raiz->esq; 
            while (pre->dir != NULL) 
                pre = pre->dir; 
            
        } 
        return pre; 
    } 

    // se a chave for menor do que o valor ta raiz, desce pela esquerda
    if (chave < raiz->info)
        buscaPre(raiz->esq, pre, chave); 
    else{ // se a chave for maior do que o valor ta raiz, desce pela direita
        pre = raiz; //se for maior, entao o valor da raiz é armazenado 
        buscaPre(raiz->dir, pre, chave); 
    } 
}

no_t *buscaPos(no_t *raiz, no_t *pos, int chave){ 
    if (raiz == NULL)  
        return NULL; 

    //se a chave existir na arvore 
    if (raiz->info == chave) 
    { 
        //primeiro vai para o nó a direita da atual raiz
        //entao o menor valor da sub arvore a esquerda sera o predecessor
        if (raiz->dir != NULL) 
        { 
            pos = raiz->dir; 
            while (pos->esq != NULL) 
                pos = pos->esq; 
        } 
        return pos; 
    } 

    // se a chave for menor do que o valor ta raiz, desce pela esquerda
    if (chave < raiz->info){
        pos = raiz;   //se for menor, entao o valor da raiz é armazenado 
        buscaPos(raiz->esq, pos, chave); 
    }else
        buscaPos(raiz->dir, pos, chave); 
}


