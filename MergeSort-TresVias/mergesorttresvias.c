
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livros{
    char *nome;
    float preco;
} livros_t;

void merge();
char *readline(); 
void mergesort();
void printar();
void inserir_livros();
void destruir();

int main(){
    livros_t *livros, *aux;
    int n = atoi(readline(stdin));

    livros = malloc(sizeof(livros_t) * n);
    aux = malloc(sizeof(livros_t) * n);

    inserir_livros(livros, aux, n);
    mergesort(livros, aux, 0, n);
    printar(livros, n);
    
    return 0;
}

void printar(livros_t *livros, int n){
    printf("\n");
    for(int i = 0; i < n; i++){
        printf("%s, R$%.2f\n", livros[i].nome, livros[i].preco);
    }
}

// ler a entrada do teclado
char *readline(FILE *imput){
    char *vetor = NULL, letra;
    int tamanho = 0;

    do {
        letra = fgetc(imput);
        vetor = realloc(vetor, sizeof(char) * (tamanho + 1));
        if(letra != '\r'){
        vetor[tamanho++] = letra;
        }
    } while (letra != '\n' && !feof(imput));

        vetor[tamanho - 1] = '\0';

        return vetor;

}


void inserir_livros(livros_t *livros, livros_t *aux, int n){
    char *livro, *preco;
    int k = 0;
    int j = 0;

    while(j < n){
        livro = readline(stdin);
        // separa o nome e o preço, a partir da virgula, de cada livro 
        // e salva cada informacao num campo da struct livro 
        livro = strtok(livro, ",");
        preco = strtok(NULL, "");
        livros[j].nome = livro;
        livros[j].preco = atof(preco);
        aux[j].nome = NULL;
        for(k = 0; k <= strlen(livros[j].nome); k++){
            aux[j].nome = realloc(aux[j].nome, sizeof(char) * (k+1));
            aux[j].nome[k] = livros[j].nome[k];
        }
        aux[j].nome[k-1] = '\0';
        aux[j].preco = livros[j].preco;
        j++;
    };
}

// divide os vetores ate chegar no caso base = 1
void mergesort(livros_t *v, livros_t *aux, int inicio, int fim){
    
    for(int l = inicio; l < fim; l++){
        printf("%.2f ", v[l].preco);
    }   
    if(inicio < fim) printf("\n"); 

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

void merge(livros_t *v, livros_t *temporario1, int inicio, int meio1, int meio2, int fim){
    int p1 = inicio, p2 = meio1, p3 = meio2, i = inicio;

    for(i = inicio; i < fim; i++){
        // compara numero dos tres vetores, o que for 
        // menor é salvo no vetor auxiliar
        if((p1 < meio1) && (p2 < meio2) && (p3 < fim)){
            if(v[p1].preco < v[p2].preco){
                if(v[p1].preco < v[p3].preco){
                    temporario1[i] = v[p1++];
                }
                else{
                    temporario1[i] = v[p3++];
                }
            }
            else{
                if(v[p2].preco < v[p3].preco){
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
                if(v[p2].preco < v[p3].preco){
                    temporario1[i] = v[p2++];
                }
                else{
                    temporario1[i] = v[p3++];
                };

            }

            else if((p1 < meio1) && (p3 < fim)){
                if(v[p1].preco < v[p3].preco){
                    temporario1[i] = v[p1++];
                }
                else{
                    temporario1[i] = v[p3++];
                };

            }

            else if((p1 < meio1) && (p2 < meio2)){
                
                if(v[p1].preco < v[p2].preco){
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

void destruir(livros_t *livros, int n){
    for(int i = 0; i < n; i++)   
        free(livros[i].nome);

    free(livros);
};