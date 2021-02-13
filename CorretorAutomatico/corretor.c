#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **readtxt();
int stopWords(char letra);
char *readline();
char **readlinetxt();
void mergesort_aux();
void mergesort();
void merge();
void corretor();
char *toLowerWold();
char **database_sem_repeticao();
int busca_binaria();
void read_json();

int main(){

    FILE *arquivo_book, *arquivo_json;
    int num_palavras_corretor = 0;
    char nome_arquivo[225], **corretor_database, **novo_corretor_database;

    scanf("%s", nome_arquivo);
    arquivo_book = fopen(nome_arquivo, "r");
    scanf("%s", nome_arquivo);
    arquivo_json = fopen(nome_arquivo, "r");
    
    //retorna uma matriz de palavras
    corretor_database = readtxt(arquivo_book, &num_palavras_corretor);
    //organiza esta matriz de forma alfabetica
    mergesort_aux(corretor_database, num_palavras_corretor, num_palavras_corretor);
    //retorna uma matriz de palavras sem as palavras repetidas da matriz anterior
    novo_corretor_database = database_sem_repeticao(corretor_database, &num_palavras_corretor);
    //le o arquivo json em busca dos twittes e imprime as palavras nao encontradas no dicionario do corretor
    read_json(arquivo_json, novo_corretor_database, num_palavras_corretor);

    return 0;
}

void read_json(FILE *arquivo_json, char **novo_corretor_database, int num_palavras_corretor){
    char *palavra, **twitWordVector = NULL, conteudo[1024];
    int num_palavras_twitt = 0;
    
    while(!feof(arquivo_json)){

        palavra = readline(arquivo_json);
        //verifica se a palavra extraida do arquivo json é uma mensagem de erro
        if(!strcmp(palavra, "errors")){
            printf("No tweets to check\n");
            break;
        }
        //verifica se a mensagem é um twitt
        else if(!strcmp(palavra, "text")){
            //salva em um vetor toda a linha do json que possui o twiit 
            fgets(conteudo, sizeof(conteudo), arquivo_json);
            if(conteudo[0] ==':'){
                //se for um twitt entao separa todas as palavras deste twitt e salva numa matriz de palavras
                twitWordVector = readlinetxt(conteudo, &num_palavras_twitt);
                //verifica se as palavrasestao presentes no dicionario do corretor
                corretor(twitWordVector, novo_corretor_database, num_palavras_twitt, num_palavras_corretor);
            }

            num_palavras_twitt = 0;
        }  
    }
    fclose(arquivo_json);
}

//busca binaria recursiva, separando sempre o vetor pela metade ate
//chegar no caso base tamanho 1 onde a palavra existe ou nao 
int busca_binaria(char *chave, char **corretor_database, int inicio, int fim){
    //verifica onde a metade da regiao do vetor
    int metade = (inicio + fim)/2;
    //se a palavra procurada (chave) for igual a palavra da posicao metade do vetor retorna 1
    if(!strcmp(corretor_database[metade], chave))
        return 1;
    //se o valor do inicio ultrapassar o valor final significa que a palavra nao existe no dicionario
    if(inicio >= fim)
        return 0;

    //como o vetor esta ordenado, ele e dividido sempre pela metade, verificando
    //se a palavra é maior do que a metade atual o menor que a metade
    if(strcmp(chave, corretor_database[metade]) < 0)
        return busca_binaria(chave, corretor_database, inicio, metade-1);
    else
        return busca_binaria(chave, corretor_database, metade+1, fim);
}

char *toLowerWold(char *palavra){
    char *nova_palavra = malloc(sizeof(char)*strlen(palavra));
    strcpy(nova_palavra, palavra);
        //faz uma copia com letras em minusculo para poder procurar
        //no dicionario, sem alterar a palavra original
        for(int i = 0; i < strlen(nova_palavra); i++){
            nova_palavra[i] = tolower(nova_palavra[i]);
        }

    return nova_palavra;
}

char **database_sem_repeticao(char **corretor_database, int *num_palavras_corretor){
    char **novo_data_base = NULL;
    int numero_palavras = 0;

    for(int i = 0; i < *num_palavras_corretor; i++){
        //verifica se a palavra atual do vetor de palavras ja ordenado, esta presente no novo vetor
        //se nao estiver presente, entao aloca de forma dinamica um espaço no novo vetor para armazena-la
        if(numero_palavras == 0 || strcmp(novo_data_base[numero_palavras-1], corretor_database[i])){
            novo_data_base = realloc(novo_data_base, sizeof(char *) * numero_palavras+1);
            novo_data_base[numero_palavras++] = corretor_database[i];
        }else{
            //se ja existir, entao a palavra do vetor original é desalocada
            free(corretor_database[i]);
        }
    }

    *num_palavras_corretor = numero_palavras;
    return novo_data_base;
}

void corretor(char **twitWordVector, char **corretor_database, int num_palavras_twitt, int num_palavras_corretor){
    
    for(int i = 0; i < num_palavras_twitt; i++){
        //faz uma copia da palavra em caixa baixa, 
        //para letras em caixa alta nao interferirem na correcao
        char *lower_word = toLowerWold(twitWordVector[i]);
        //retornando 0 significa que a palavra nao foi 
        //encontrada no vetor do corretor entao a palavra é impressa
        if(!busca_binaria(lower_word, corretor_database, 0, num_palavras_corretor))
            printf("%s ", twitWordVector[i]);
        
    }
    
    printf("\n");

}

char *readline(FILE *imput){
    char letra, *frase = NULL;
    int num_letras = 0;
    //salva cada caracter em um vetor de palavra ate encontrar 
    //um char que nao seja uma letra alfbetica ou com o fim do arquivo
    do{
        letra = fgetc(imput);
        letra = tolower(letra);
        frase = realloc(frase, sizeof(char) * (num_letras+1));
        frase[num_letras] = letra;
        num_letras++;
    }while(!feof(imput) && !stopWords(letra));

    frase[num_letras-1] = '\0';

    return frase;
}

char **readlinetxt(char *imput, int *num_palavras){
    char letra, **twitFrase = NULL, *frase = NULL;
    int n_letras = 0, i = 0;

    //le a string da linha do arquivo json que possui o twitt, salva todas as palavras ate
    //encontrar um char que nao seja uma letra alfbetica ou com o fim do arquivo
    do{
        n_letras = 0;
        do{
            letra = imput[i];
            frase = realloc(frase, sizeof(char) * (n_letras+1));
            frase[n_letras++] = letra;
            i++;
        }while(imput[i-1] != '\n' && !stopWords(imput[i-1]));
        
        frase[n_letras-1] = '\0';

        //se for uma palavra mesmo, com ao menos uma letra, salva no vetor de palavras
        if(strlen(frase)){
            twitFrase = realloc(twitFrase, sizeof(char*) * (*num_palavras)+1);
            twitFrase[(*num_palavras)] = malloc(sizeof(char) * strlen(frase));
            strcpy(twitFrase[(*num_palavras)++], frase);
        }
        
    }while(i < strlen(imput));
    
    return twitFrase;
}

char **readtxt(FILE *arquivo, int *num_palavras){
    char **corretor_database = NULL, *palavra = NULL;

    while(!feof(arquivo)){
        //retorna cada palavra do arquivo para ser salvo em um vetor de palavras
        //enquanto nao for fim do arquivo
        palavra = readline(arquivo);
        if(strlen(palavra)){
            corretor_database = realloc(corretor_database, sizeof(char*)* (*num_palavras)+1);
            corretor_database[(*num_palavras)++] = palavra;
        }
    };

    fclose(arquivo);
    return corretor_database;
}

int stopWords(char letra){
    //verifica se o char é uma letra alfabetica
    if(!isalpha(letra))
        return 1;

    return 0;
}

void mergesort_aux(char **corretor_database, int fim, int num_palavras){
    char **aux;
    //cria matriz auxiliar para ser usada na ordenacao mergesort
    aux = malloc(sizeof(char*) * num_palavras);
    for(int i = 0; i < num_palavras; i++)
        aux[i] = corretor_database[i];

    mergesort(corretor_database, aux, 0, fim);
}

void mergesort(char **v, char **aux, int inicio, int fim){

    if(fim - inicio < 2) 
        return;

        int meio1 = inicio + (fim - inicio + 1)/3;
        int meio2 = inicio + 2*(fim - inicio + 1)/3;
        // verifica se o numero possui resto 1, se positivo entao acrescenta 1 a 
        // primeira metade para que seja dividido de maneira apropriada
        if((fim-inicio)%3 == 1)
            meio1++;

        mergesort(aux, v, inicio, meio1);
        mergesort(aux, v, meio1, meio2);
        mergesort(aux, v, meio2, fim);
        merge(aux, v, inicio, meio1, meio2, fim);
}

void merge(char **v, char **temporario1, int inicio, int meio1, int meio2, int fim){
    int p1 = inicio, p2 = meio1, p3 = meio2, i = inicio;

    for(i = inicio; i < fim; i++){
        // compara numero dos tres vetores, o que for 
        // menor é salvo no vetor auxiliar
        if((p1 < meio1) && (p2 < meio2) && (p3 < fim)){
            if(strcmp(v[p1], v[p2]) < 0){
                if(strcmp(v[p1], v[p3]) < 0){
                    temporario1[i] = v[p1++];
                }
                else{
                    temporario1[i] = v[p3++];
                }
            }
            else{
                if(strcmp(v[p2], v[p3]) < 0){
                    temporario1[i] = v[p2++];
                }
                else{
                    temporario1[i] = v[p3++];
                }
            }
            
        }
        else{
            // se um dos vetores ja nao possuir mais nenhum numero
            // compara entao os numeros dos vetores restantes 
            if((p2 < meio2) && (p3 < fim)){
                if(strcmp(v[p2], v[p3]) < 0){
                    temporario1[i] = v[p2++];
                }
                else{
                    temporario1[i] = v[p3++];
                };

            }

            else if((p1 < meio1) && (p3 < fim)){
                if(strcmp(v[p1], v[p3]) < 0){
                    temporario1[i] = v[p1++];
                }
                else{
                    temporario1[i] = v[p3++];
                };

            }

            else if((p1 < meio1) && (p2 < meio2)){
                
                if(strcmp(v[p1], v[p2]) < 0){
                    temporario1[i] = v[p1++];
                }
                else{
                    temporario1[i] = v[p2++];
                };

            }

            else{
                // quanto haver apenas um vetor, os numeros deste 
                // sao apenas copiados para o vetor auxiliar
                if(p3 < fim){
                    temporario1[i] = v[p3++];
                }

                else if(p1 < meio1){
                    temporario1[i] = v[p1++];
                }

                else if(p2 < meio2){
                    temporario1[i] = v[p2++];
                }
            }
        }
    }
}

void free_vector(char *vector, int tamanho_vector){
    
}
