#include <stdio.h>
#include <stdlib.h>
#include "treap.h"


struct no_l{
    no_t *copia;
    no_lista *prox;
};

struct no{
    elem info;
    int prioridade;
    no_t *esq, *dir;
};

arvore_t *criar(){
    arvore_t *arvore;
    arvore = malloc(sizeof(arvore_t));
    arvore->raiz = NULL;

    return arvore;
};

lista_t *criar_lista(){
    lista_t *l;
    l = malloc(sizeof(lista_t));

    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

int inserir(no_t **raiz, elem x, int prioridade){
    *raiz = insere_no(*raiz, x, prioridade);

    return 1;
}

no_t *insere_no(no_t *h, int valor, int prioridade){

    //qunado o filho de um pai for NULL o item é inserido na arvore
    //assim, ele é inserido como um  nó folha desta
    if(h == NULL){
        no_t *novo;
        novo = malloc(sizeof(no_t));
        if(novo == NULL)
            return NULL;
        novo->info = valor;
        novo->prioridade = prioridade;
        novo->dir = NULL;
        novo->esq = NULL;
        return novo;
    }

    //de forma recursiva encontra qual o local que o item deve ser inserido a 
    //partir da varificacao se ele é maior ou menor que o item da raiz atual
    if(valor < h->info){
        inserir(&h->esq, valor, prioridade);
        
        //qual retornar da recursividade verifica se as prioridades estao corretas
        //se nao estiverem a arvore é rotacionada subindo o item  
        if(h->esq != NULL && h->esq->prioridade > h->prioridade)
            h = dd(h);

    }else{
        inserir(&h->dir, valor, prioridade);

        if(h->dir != NULL && h->dir->prioridade > h->prioridade)
            h = ee(h);
    }

    return h;
}

//verificando se a chave é maior ou menor que o item presente na raiz atual
//de forma recursiva verifica que a chave esta presente na arvore
int busca(no_t *raiz, elem x){
    if(raiz == NULL)
        return 0;
    if(raiz->info == x)
        return 1;
    if(x < raiz->info)
        busca(raiz->esq, x);
    else
        busca(raiz->dir, x);
}

//se o item ja existir na arvore, entao nao é inserido 
void verificar_e_inserir(arvore_t *arvore, int numero, int prioridade){
    if(!busca(arvore->raiz, numero))
        inserir(&arvore->raiz, numero, prioridade);
    else
        printf("Elemento ja existente\n");
}

//faz rotacao para a esquerda mudando o filho direito para ser o pai
//e descendo o antigo pai 
no_t *ee(no_t *desb){
    no_t *aux = desb->dir;
    desb->dir = aux->esq;
    aux->esq = desb;
    return aux;
}

//faz rotacao para a direita mudando o filho esquerdo para ser o pai
//e descendo o antigo pai 
no_t *dd(no_t *desb){
    no_t *aux = desb->esq;
    desb->esq = aux->dir;
    aux->dir = desb;
    return aux;
}

//imprime em pre ordem
void pre_ordem(no_t *raiz){
    if(raiz != NULL){
        printf("(%d, %d) ", raiz->info, raiz->prioridade);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

//imprime em ordem numerica
void em_ordem(no_t *raiz){
    if(raiz != NULL){
        em_ordem(raiz->esq);
        printf("(%d, %d) ", raiz->info, raiz->prioridade);
        em_ordem(raiz->dir);
    }
};

//imprime em pos ordem
void pos_ordem(no_t *raiz){
    if(raiz != NULL){
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("(%d, %d) ", raiz->info, raiz->prioridade);
    }  
};

//imprime em largura, utilizando listas 
void em_largura(no_t *raiz){
    lista_t *lista = criar_lista();

    //insere o no raiz da arvore na lista para que a funcao de remocao possa agir 
    inserir_lista(lista, raiz);

    //remove o item da lista ate que ela esteja vazia 
    do{
        remover_lista(lista);
    }while(lista->ini != NULL);

    free(lista);
}


void inserir_lista(lista_t *l, no_t *x){

    //cria um ponteiro que ira armazenar uma copia de um item da arvore
    no_lista *p = malloc(sizeof(no_lista));
    p->copia = x;

    //se a arvore estiver vazia, insere o item como o primeiro da lista
    p->prox = NULL;
    if(l->ini ==  NULL){
        l->ini = p;
    }
    else{
        //se nao insere em fila como o ultimo
        l->fim->prox = p;
    }
    l->fim = p;
    l->tam++;
}

void remover_lista(lista_t *l){
    no_lista *p = l->ini;

    //imprime o primeiro item da lista e sua prioridade
    printf("(%d, %d) ", p->copia->info, p->copia->prioridade);
    if(p->copia->esq != NULL) //verifica se o item possui filhos 
                              //se possuir, os insere na lista tambem (em ultimo lugar)
        inserir_lista(l, p->copia->esq);
    if(l->ini->copia->dir != NULL)
        inserir_lista(l, p->copia->dir);

    //o segundo item da lista passa a ser o primeiro
    l->ini = l->ini->prox;
    //o primeiro item da lista é liberado
    free(p);
}

int delete(no_t **raiz, int x){
    *raiz = delete_no(*raiz, x);

    return 1;
}


no_t* delete_no(no_t* raiz, int chave) { 
    // Se for NULL significa que a chave nao existe nesta arvore
    if (raiz == NULL) {
        printf("Chave nao localizada\n");
        return raiz; 
    }
        
    //de forma recursiva desce a arvore a partir da esquerda ou direita
    //dependendo do tamanho da chave comparado ao valor salvo no nó
    if (chave < raiz->info) 
        raiz->esq = delete_no(raiz->esq, chave); 
    else if (chave > raiz->info) 
        raiz->dir= delete_no(raiz->dir, chave); 
  
  
    //se apenas tiver um filho, faz dele a raiz e exclui a raiz atual
    else if (raiz->esq == NULL) 
    { 
        no_t *temp = raiz->dir; 
        free(raiz); 
        raiz = temp;
    } 

    else if (raiz->dir == NULL) 
    {   //salva o filho da raiz atual em uma variavel temporaria
        no_t *temp = raiz->esq; 
        free(raiz); //libera a memoria
        raiz = temp; //o filho agora passa para o lugar onde estava o pai
    } 
  
    //se a raiz tiver dois filhos, entao rotaciona para a esquerda ate
    //que se torne uma semi folha q possa deleta-lo entao propriamente 
    else { 
        raiz = ee(raiz); 
        raiz->esq = delete_no(raiz->esq, chave); 
    } 
  
    return raiz; 
}

//se as palavras do teclado para saber qualacao é necessaria ser realizada
char *readline(FILE *imput){
    char letra, *palavra = NULL;
    int tamanho = 0;

    //de forma dinamica aloga a palavra que esta sendo digitada
    do{
        letra = getc(imput);
        if(letra != '\n'){
        palavra = realloc(palavra, sizeof(char) * tamanho+1);
        palavra[tamanho++] = letra;
        }//ate encontrar um espaco, pulo de linha ou fim do arquivo
    }while(letra != ' ' && letra != '\n' && !feof(imput));

    palavra[tamanho-1] = '\0';

    return palavra;
}
