#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"
#include <ctype.h>

#define MAX_LEVEL 20;
#define MAX 0.5

struct no{
    char palavra[50];
    char definicao[150];
    no_t **prox;
};

struct skiplist{
    int max_level;
    int nivel;
    no_t *inicio;
};

struct input_dic{
    char comando[15];
    char palavra[50];
    char definicao[150];
};

skip_t *criar(){
    skip_t *l;
    l = malloc(sizeof(skip_t));
    if(l != NULL){
        l->max_level = MAX_LEVEL;
        l->nivel = 0;
        // cria o cabecalho inicial da estrutura
        l->inicio = vetor_nos("", "", l->max_level);
    }

    return l;
};

// aloca o vetor de nos da informacao que vao ser usados para pular de info em info
no_t *vetor_nos(char *palavra, char *definicao, int max_level){
    no_t *novo_no;
    novo_no = malloc(sizeof(no_t));
    if(novo_no != NULL){
        strcpy(novo_no->palavra, palavra);
        strcpy(novo_no->definicao, definicao);

        novo_no->prox = malloc((max_level+1) * sizeof(no_t));
        for(int i = 0; i < max_level+1; i++)
            novo_no->prox[i] = NULL;
    }

    return novo_no;
};

// sorteia de forma aleatoria quantos niveis a informacao tera
int random_nivel(skip_t *l){
    int nivel = 1;

    while (nivel < l->max_level && (random() > RAND_MAX / 2))
        nivel++;

    return nivel;
}

no_t *busca(skip_t *l, input_dic *palavra){
    if(l != NULL){
        no_t *atual = l->inicio;

        // enquanto a informacao do no da frente for maior que a palavra, vai pulando para frente
        // se nao for maior, se desce um nivel no vetor de ponteiros. ate chegar no nivel 0
        for(int i = l->nivel; i >= 0; i--){
            while(atual->prox[i] != NULL && strcmp(palavra->palavra, atual->prox[i]->palavra) > 0)
                atual = atual->prox[i];
        }

        // a informacao a frente do nivel atual devera ser a que estamos procurando
        atual = atual->prox[0];
        return atual; 
    }
};

// le entrada do teclado ate encontrar um "\n" ou fim do arquivo
char *readline(FILE *input){
    char letra;
    char *palavra = NULL;
    int num_letras = 0;

    do{
        letra = fgetc(input);
        // aloca dinamicamente um vetor de char com o tamanho do input
        palavra = realloc(palavra, sizeof(char)*num_letras+1);
        palavra[num_letras++] = letra;
    }while(letra != '\n' && !feof(input));

    palavra[num_letras-1] = '\0';

    return palavra;
};

// separa, com strtok o input entre comando pra decidir o que sera realizado com o dicionario
// palavra, e seu definicao
input_dic *separar(char *palavra){
    input_dic *palavras = malloc(sizeof(input_dic));
    
    char *tok = strtok(palavra, " ");
    strcpy(palavras->comando, tok);

    tok = strtok(NULL, " ");
    
    strcpy(palavras->palavra, tok);
    
    if(!strcmp(palavras->comando, "busca") || !strcmp(palavras->comando, "remocao") || !strcmp(palavras->comando, "impressao"))
        palavras->palavra[strlen(palavras->palavra)-1] = '\0';

    if(!strcmp(palavras->comando, "insercao") || !strcmp(palavras->comando, "alteracao")){
        tok = strtok(NULL, "");
        strcpy(palavras->definicao, tok);
    }

    return palavras;
}

// escolhe a acao a ser realizada com o dicionario
void escolher_acao(skip_t *l, input_dic *inputs){
    if(!strcmp(inputs->comando, "insercao"))
        inserir(l, inputs);

    else if(!strcmp(inputs->comando, "alteracao"))
        alteracao(l, inputs);

    else if(!strcmp(inputs->comando, "busca"))
        print_busca(l, inputs);

    else if(!strcmp(inputs->comando, "remocao"))
        remover(l, inputs->palavra);

    else if(!strcmp(inputs->comando, "impressao"))
        impressao(l, inputs);
};

void impressao(skip_t *l, input_dic *inputs){
    no_t *atual = busca(l, inputs);
    if(atual != NULL)
        // enquando a primeira letra da palavra for igual a letra procurada
        // imprime a palavra e seu significiado
        while(atual != NULL && atual->palavra[0] == inputs->palavra[0]){
            if(atual != NULL)
            printf("%s %s\n", atual->palavra, atual->definicao);    
            atual = atual->prox[0];
        } 
    else 
        printf("OPERACAO INVALIDA\n");
}

void inserir(skip_t *l, input_dic *inputs){
    if(l != NULL){
        int i;
        // posicao inicial da lista 
        no_t *atual = l->inicio;
        // vetor de ponteiros que ira armazenar a posicao dos niveis anteriores a info que sera inserida
        no_t **aux;
        aux = malloc((l->max_level+1) * sizeof(no_t*));
        for(i = 0; i <= l->max_level; i++)
            aux[i] = NULL;

        // caminha pela lista e armazena os ponteiros das infos na posicao anterior a info
        //  que sera inserida na lista, em cada linha da lista, ate chegar a primeira linha (linha 0)
        for(i = l->nivel; i>= 0; i--){
            while(atual->prox[i] != NULL && strcmp(inputs->palavra, atual->prox[i]->palavra) > 0)
                atual = atual->prox[i];
            aux[i] = atual;
        }

        atual = atual->prox[0];

        // se a palavra nao existir na lista, ira ser inserida
        if(atual == NULL || strcmp(atual->palavra, inputs->palavra)){

            // de forma randomica, o numero de niveis dessa nov informacao na lista, sera escolhida
            int novo_nivel = random_nivel(l);
            // cria um novo no, com as infos e numero de niveis previamente escolhido
            no_t *novo = vetor_nos(inputs->palavra, inputs->definicao, novo_nivel);
            if(novo == NULL){
                free(aux);
                return;
            }
                
            // se o numero de niveis da nova informacao for maior que o numero de neveis maximo da lista
            // entao é adicionado um novo nivel a lista 
            if(novo_nivel > l->nivel){
                for(i = l->nivel+1; i <= novo_nivel; i++)
                    aux[i] = l->inicio;
                l->nivel = novo_nivel;
            }

            // liga o novo no a lista encadeada em todos os seus niveis 
            for(i = 0; i <= novo_nivel; i++){
                novo->prox[i] = aux[i]->prox[i];
                aux[i]->prox[i] = novo;
            }

            free(aux);
            return;
        }
        else 
            printf("OPERACAO INVALIDA\n");
    }
};

void alteracao(skip_t *l, input_dic *inputs){
    no_t *atual = busca(l, inputs);
    // se a palavra retornada for igual a palavra 
    // altera seu significado 
    if(atual != NULL && !strcmp(atual->palavra, inputs->palavra))
        strcpy(atual->definicao, inputs->definicao);
    else
        printf("OPERACAO INVALIDA\n");
}

void print_busca(skip_t *l, input_dic *inputs){
    no_t *atual = busca(l, inputs);
    // se a palavra retornada for igual a palavra 
    // procurada printa ela na tela
    if(atual != NULL && !strcmp(atual->palavra, inputs->palavra))
        printf("%s %s\n", atual->palavra, atual->definicao);
    else
        printf("OPERACAO INVALIDA\n");
}

//remove um item do dicionario e todos seus ponteiros 
void remover(skip_t *l, char *inputs){
    if(l != NULL){
        int i;
        no_t *atual, **aux;
        atual = l->inicio;
        // assim como em incluir é preciso varrer todo vetor e seus niveis 
        // para verificar onde está os ponteiros que devem ser desalocados
        aux = malloc(sizeof(no_t) * l->max_level+1);
        for (i = 0; i <= l->max_level; i++)  
            aux[i] = NULL;
        for(i = l->nivel; i >= 0; i--){
            while(atual->prox[i] != NULL && strcmp(inputs, atual->prox[i]->palavra) > 0)
                atual = atual->prox[i];
            aux[i] = atual;
        }

        atual = atual->prox[0];

        // os ponteiros do item anterior ao item desalocado passa a apontar
        // para o item posterior ao item desalocado
        if(atual != NULL && !strcmp(atual->palavra, inputs)){
            for(i = 0; i <= l->nivel; i++){
                if(aux[i]->prox[i] != atual)
                    break;
                aux[i]->prox[i] = atual->prox[i];
            }
                
            while(l->nivel > 0 && l->inicio->prox[l->nivel] == NULL)
                l->nivel--;
            
            free(atual->prox);
            free(atual);
        }else
            printf("OPERACAO INVALIDA\n");

        free(aux);
    }
}

// libera toda estrutura alocada pelo dicionario
void destruir(skip_t *l){
    if(l != NULL){
        no_t *no, *atual;
        atual = l->inicio->prox[0];
        while(atual != NULL){
            no = atual;
            atual = atual->prox[0];
            free(no->prox);
            free(no);
        }
        free(l->inicio);
        free(l);
    }
}

