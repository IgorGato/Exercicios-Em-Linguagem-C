#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// struct que sera utilizada para guardar cada nome e cidade de cada cidadao
typedef struct nomes_cidades {
    char *nomes;
    char *cidades;
} nomes_cidades_t;

// struct de structs com todas as pessoas inseridas e suas cidades 
typedef struct infos {
    nomes_cidades_t *pessoas_nomes;
} infos_t;

// struct que guarda o nome da pessoa pesquisada e se ela mora em Sao Carlos 
typedef struct pesquisados {
    char **nomes_pesquisados;
    int *mora_sc;
} pesquisados_t;

char *readline();
void cocktailsort();
int comparar();
char *add_ponto();
void printar();
int comparacao();
char *lower();
void destruir();

int main(){
    char *nome = NULL, *nome_separado = NULL, *cidade = NULL;
    int num_nomes, num_pesquisados, i;
    num_nomes = atoi(readline(stdin));
    
    infos_t *pessoas;
    pessoas = malloc(sizeof(infos_t)); 
    pessoas->pessoas_nomes = malloc (sizeof(nomes_cidades_t) * num_nomes);

    // separa o nome e a cidade da pessoa, cada um entao eh colocado
    // no campo correspondente de um struct 
    for(i = 0; i < num_nomes; i++){
        nome = readline(stdin);
        nome_separado = strtok(nome, ".");
        nome_separado = add_ponto(nome_separado);
        cidade = strtok(NULL, "");
        cidade = cidade+1;
        pessoas->pessoas_nomes[i].nomes = nome_separado;
        pessoas->pessoas_nomes[i].cidades = cidade;
    }

    // as structs sao entao ordenadas de forma alfabetica
    cocktailsort(pessoas, num_nomes);

    num_pesquisados = atoi(readline(stdin));
    pesquisados_t *pessoas_pesquisadas;
    pessoas_pesquisadas = malloc(num_pesquisados * sizeof(pesquisados_t));

    pessoas_pesquisadas->nomes_pesquisados = malloc(num_pesquisados * sizeof(char*));
    pessoas_pesquisadas->mora_sc = malloc(num_pesquisados * sizeof(int));

    // salva numa struct o nome dos pesquisados 
    // verifica se tal nome mora em Sao Carlos ou nao 
    for(i = 0; i < num_pesquisados; i++){
        pessoas_pesquisadas->nomes_pesquisados[i] = readline(stdin);
        pessoas_pesquisadas->mora_sc[i] = comparar(pessoas_pesquisadas->nomes_pesquisados[i], num_nomes, pessoas);
    }

    printar(pessoas, num_nomes, pessoas_pesquisadas, num_pesquisados);

    destruir(pessoas, pessoas_pesquisadas, num_nomes, num_pesquisados);
    
    return 0;
}

void destruir(infos_t *pessoas, pesquisados_t *pessoas_pesquisadas, int num_nomes, int num_pesquisados){
    free(pessoas_pesquisadas);
    free(pessoas->pessoas_nomes);
    free(pessoas);

};

// le a entrada do teclado
char *readline(FILE *imput){
    char letra, *frase = NULL;
    int num_letras = 0;

    do{
        letra = fgetc(imput);
        frase = realloc(frase, sizeof(char) * (num_letras+1));
        if(letra != '\r'){
        frase[num_letras] = letra;
        num_letras++;
        }
    }while(letra != '\n' && !feof(imput));

    frase[num_letras-1] = '\0';

    return frase;
}

void cocktailsort(infos_t *pessoas, int n_nomes){
    int j, limite_superior = n_nomes-1, limite_inferior = 0;
    nomes_cidades_t *aux;
    aux = malloc(sizeof(nomes_cidades_t));

    while(limite_inferior < limite_superior){
        //ate o limite superior ira comparar todos os nomes do vetor
        // para ordena-los de forma alfabetica, shiftando nomes se esses
        // forem maiores, e mandando para o final da matriz
        for(j = limite_inferior; j < limite_superior; j++){
            if(comparacao(pessoas->pessoas_nomes[j].nomes, pessoas->pessoas_nomes[j+1].nomes) > 0){
                *aux = pessoas->pessoas_nomes[j];
                pessoas->pessoas_nomes[j] = pessoas->pessoas_nomes[j+1];
                pessoas->pessoas_nomes[j+1] = *aux;
            }
        }
        limite_superior--;
        //faz o mesmo, mas carregando o nome menor, alfabeticamente, 
        // do final do vetor, para o comeco deste  
        for(j = limite_superior; j > limite_inferior; j--){
            if(comparacao(pessoas->pessoas_nomes[j].nomes, pessoas->pessoas_nomes[j-1].nomes) < 1){
                *aux = pessoas->pessoas_nomes[j];
                pessoas->pessoas_nomes[j] = pessoas->pessoas_nomes[j-1];
                pessoas->pessoas_nomes[j-1] = *aux;
            }
        }
        limite_inferior++;
    }
}

int comparar(char *nome, int num_nomes, infos_t *pessoas){
    int i;
    for (i = 0; i < num_nomes; i++){
        if (strcmp(pessoas->pessoas_nomes[i].nomes, nome) == 0){
            // verifica se a cidade da pessoa eh Sao Carlos, se for retorna 1
            if (strcmp(pessoas->pessoas_nomes[i].cidades, "Sao Carlos.") == 0){
                return 1;
            }  
            else{
                return 0;
            };   
        };
    }
    return 0;
}

char *add_ponto(char *frase){
    char *nova_frase = NULL;

    // adiciona o ponto final que foi consumido pelo strtok quando separou as frases
    nova_frase = realloc(nova_frase, sizeof(char) * strlen(frase) + 2);
    strcpy(nova_frase, frase);
    strcat(nova_frase, ".");

    return nova_frase;
}

void printar(infos_t *pessoas, int num_nomes, pesquisados_t *pessoas_pesquisadas, int num_pesquisados){
    int i;
    for (i = 0; i < num_nomes; i++){
        printf("%s\n", pessoas->pessoas_nomes[i].nomes);
    }
    for(i = 0; i < num_pesquisados; i++){
        printf("%d\n", pessoas_pesquisadas->mora_sc[i]);
    }
}

int comparacao(char *palavra1, char*palavra2){
    char *lower_palavra1, *lower_palavra2;
    lower_palavra1 = lower(palavra1);
    lower_palavra2 = lower(palavra2);
    // verifica qual palavra eh maior alfabeticamente 
    return strcmp(lower_palavra1, lower_palavra2);
}

char *lower(char *palavra){
    char *nova_palavra = NULL;
    int i = 0; 
    nova_palavra = malloc(sizeof(char) *strlen(palavra)+1);
    strcpy(nova_palavra, palavra);
    // torna todos os caracteres da palavra minusculos para poder fazer uma comparacao justa
    while(nova_palavra[i]){
        nova_palavra[i] = tolower(nova_palavra[i]);
        i++;
    }

    return nova_palavra;
}