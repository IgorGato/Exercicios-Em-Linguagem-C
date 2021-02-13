#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "covid.h"

struct clientes{
    char nome[100];
    int idade;
    int saude;
    int prioridade;
};

struct fila {
    int inicio, fim, total;
    clientes_t infos[tam_fila];
};

fila_t *criar(){
    fila_t *c;
    c = (fila_t*) malloc(sizeof(fila_t));
    c->inicio = 0;
    c->fim = 0;
    c->total = 0;

    return c;
}

int empty(fila_t *c){
    if(c->total == 0)
        return 1;
    return 0;
}

int full(fila_t *c){
    if(c->total == tam_fila)
        return 1;
    return 0;
};
//atribui uma prioridade a cada cliente
clientes_t *informacoes(char** x){
    clientes_t *tipo_cliente = NULL;

    tipo_cliente = (clientes_t*) malloc(sizeof(clientes_t));
    strcpy(tipo_cliente->nome, x[1]);
    tipo_cliente->idade = atoi(x[2]);
    tipo_cliente->saude = atoi(x[3]);

    if(tipo_cliente->idade >= 60 && tipo_cliente->saude == 1){
        tipo_cliente->prioridade = 1;
    }
    else if(tipo_cliente->saude == 1){
        tipo_cliente->prioridade = 2;
    }
    else if(tipo_cliente->idade >= 60){
        tipo_cliente->prioridade = 3;
    }
    else{
        tipo_cliente->prioridade = 4;
    }
    return tipo_cliente;
}

void printar_saida(clientes_t *c){
    printf("%s %d %d\n", c->nome, c->idade, c->saude);
}

int inserir(fila_t *c, clientes_t *x){
    int i, j = 0;
    clientes_t aux;
    if(full(c)){
        printf("FILA CHEIA\n");
        return 0;
    }   
    else{
        i = c->fim;
        c->infos[i] = *x;
        aux = c->infos[i - 1];
	//insere e verifica se o cliente a frente possui uma prioridade inferior
	//se positivo, passa a sua frente 
        while (c->infos[i].prioridade < c->infos[i - 1].prioridade && i > c->inicio){
            aux = c->infos[i - 1];
            c->infos[i - 1] = c->infos[i];
            c->infos[i] = aux;
            i = i - 1;
        }

            c->fim = (c->fim + 1) % tam_fila;
            c->total++;
    }
 
    return 1;
};

int remover(fila_t *c, clientes_t *x){

    if(empty(c)){
        printf("FILA VAZIA\n");
        return 0;
    }
    else{
        *x = c->infos[c->inicio];
        c->inicio = (c->inicio + 1) % tam_fila;
        c->total--;
    }
    return 1;
};

void destruir(fila_t *f){
    if(f != NULL)
        free(f);

};
//le o que foi digitado na entrada 
char *readline(FILE *imput){
    char *frase = NULL, letra;
    int tamanho = 0;

    do{
        letra = fgetc(imput);
        frase = (char*) realloc(frase, sizeof(char) * tamanho+1);
        if(letra != '\r'){
        frase[tamanho++] = letra;
        }
    }while (letra != '\n' && !feof(imput));

    frase[tamanho - 1] = '\0';

    return frase;
};
// separa a frase na entrada em um vetor de palavras
char **separar(char *frase){
    char **pal_soltas = NULL;
    char *token = NULL;
    int contador = 0;
    token = strtok(frase, " ");

    while (token != NULL){
        pal_soltas = realloc(pal_soltas, sizeof(char*) * contador+1);
        pal_soltas[contador++] = token;
        token = strtok(NULL, " ");
    }

    return pal_soltas;
}