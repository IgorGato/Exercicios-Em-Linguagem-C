#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GrandesNumeros.h"

#define NUM_CARACTERS 1

struct no{
    int part_num;
    no_t *ant, *prox;
};

struct lista{
    no_t *ini, *fim;
    int neg;
};

struct conta{
    char *num1, *num2, *op;
};


lista_t *criar(){
    lista_t *l;
    l = malloc(sizeof(lista_t));

    l->ini = NULL;
    l->fim = NULL;
    // mostra se o numero armazenado é negativo ou não
    l->neg = 0;

    return l;
};

conta_t **ler_guardar_input(int num_inputs){
    conta_t **input_contas = malloc(sizeof(conta_t) * num_inputs);

    int i = 0;
    while(i < num_inputs){
        char *palavra;
        palavra = read_line(stdin);

        // armazena os numeros ainda em forma de caracter, em uma struct
        // separadando cada numero e operação
        if(strlen(palavra))
            input_contas[i++] = separar_input(palavra);
    };

    return input_contas;
};

// lê o input dos numeros no teclado 
char *read_line(FILE *input){
    char letra;
    char *palavra = NULL;
    int tam_pal = 0;
        
    do{
        letra = fgetc(input);

        if(letra != '\r'){
        palavra = realloc(palavra, sizeof(char) * tam_pal+1);
        palavra[tam_pal++] = letra;
        }
    }while(letra != '\n' && !feof(stdin)); 
    palavra[tam_pal-1] = '\0';

    return palavra;
}

// separa e armazena cada numero e operação na struct
conta_t *separar_input(char *inputs){
    conta_t *input_conta;
    input_conta = malloc(sizeof(conta_t));
    
        char *tok;
        tok = strtok(inputs, " ");
        input_conta->op = tok;
        tok = strtok(NULL, " ");
        input_conta->num1 = tok;
        tok = strtok(NULL, " ");
        input_conta->num2 = tok;

    return input_conta;
}


void insert_number(lista_t *numero1, lista_t *numero2, conta_t **num, int position){

    inser_number_part(numero1, num[position]->num1);
    inser_number_part(numero2, num[position]->num2); 

}

// converte os numeros earmazena cada um em uma lista 
void inser_number_part(lista_t *num, char *char_num){
    char number[NUM_CARACTERS];
    int number_number = 0;

    int i = 0;
    // se o numero for negativo, guarda a informacao na sua respectiva lista
    if(char_num[0] == '-'){
        i++;
        num->neg = 1;
    }

    // converte cada char que forma o numero e armazena em um nó na struct
    while(i < strlen(char_num)){
        int j = 0;

        while(j < NUM_CARACTERS)
            number[j++] = char_num[i++];
    
        number_number = atoi(number);
        
        if(num->neg)
            number_number = number_number * -1;

        inserir(num, number_number);
    }

}

// insere um novo elemento na lista 
void inserir(lista_t *l, int x){
    if(l != NULL){
        no_t *p = malloc(sizeof(no_t));
        p->part_num = x;
        p->prox = NULL;
        p->ant = NULL;

        if(l->ini == NULL){
            l->ini = p;
        } else{
            p->ant = l->fim;
            l->fim->prox = p;
            p->prox = NULL;
        }
        l->fim = p;
    }
};

void imprimir(lista_t *l){
    if(l != NULL){
        no_t *aux = l->fim;
        while(aux != NULL){
            printf("%d", aux->part_num);
            aux = aux->ant;
        }
    }
    printf("\n");
};


void destruir(lista_t *l){
    if(l != NULL){
        no_t *aux = l->ini;
        while(aux != NULL){
            l->ini = l->ini->prox;
            free(aux);
            aux = l->ini;
        }
        free(l);
    }
};

// soma os numeros e armazena em uma nova lista
lista_t *sum(lista_t *num1, lista_t *num2){
    lista_t *result;
    no_t *r1, *r2;
    result = criar();
    r1 = num1->fim;
    r2 = num2->fim;
    
    int soma = 0;

    while(r1 != NULL || r2 != NULL){
        int resto = 0;

        if(r1 == NULL){
            soma += r2->part_num;
            r2 = r2->ant;
        }
            
        else if(r2 == NULL){
            soma += r1->part_num;
            r1 = r1->ant;
        }
            
        else{
            soma += r1->part_num+r2->part_num;
            r1 = r1->ant;
            r2 = r2->ant;
        }

        
        resto = soma / 10;
        soma = soma % 10; 
         
        inserir(result, soma);
        soma = resto;
    }
        if(soma)
            inserir(result, soma);

        // remove os zeros a esquerda
        while(result->fim->part_num == 0 && result->fim != result->ini)
            remover(result);

    return result;
}

void remover(lista_t *l){
    l->fim = l->fim->ant;
    l->fim->prox;
};

int maior_menor_igual(lista_t *num1, lista_t *num2){
    lista_t *result;
    no_t *aux;

    if(num1->neg == num2->neg){
            aux = num2->ini;
            
            // soma o primeiro numero, com o negativo do segundo numero
            // o resultado mostra qual é positivo, ou negativo ou se são iguais
            while(aux != NULL){
                aux->part_num = aux->part_num * -1;
                aux = aux->prox;
            }

            result = sum(num1, num2);

        if(result->fim->part_num < 0){
            return 0;
        }
            
        else if (result->fim->part_num == 0){ 
            return 1;
        }
        else{ 
            return 1;
        }
    }
    // 
    // verifica se um numero é maior que o outro
    // atraves da presença, ou não, do sinal de negativo
    else if(num1->neg == 0 && num2->neg == 1){
        return 1;
    }
    else{
        return 0;
    }      
}

void escolher_operacao(conta_t **inputs, int num_op){

    // verifica a operacao e imprime todos os imputs 
    for(int i = 0; i < num_op; i++){
        lista_t *num1, *num2, *result;
        num1 = criar();
        num2 = criar();
        insert_number(num1, num2, inputs, i);
        printf("Resultado %i: ", i+1);
        if(!strcmp(inputs[i]->op, "sum")){
        
            result = sum(num1, num2);

            imprimir(result);
            destruir(result);
        } else{

            int res = maior_menor_igual(num1, num2);

            if(!strcmp(inputs[i]->op, "sml"))
                res == 0 ? res++ : res--;

            printf("%d\n", res);
        }

        destruir(num1);
        destruir(num2);
    }  

    for(int i = 0; i < num_op; i++)
        free(inputs[i]);
    free(inputs);
}



