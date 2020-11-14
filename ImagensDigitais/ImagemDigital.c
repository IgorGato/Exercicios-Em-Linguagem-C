#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_RAND 256

int **fazer_matriz(int n, int t);
void printar_matriz(int **matriz, int n);
void make_pgm(int **matriz, int n, char *complemento);
void alterar_imagem(int **matriz, int x, int y, int n, int t);
void imagem(int **matriz, int x, int y, int n, int t, int a, int b);

int main(){
    // insira 
    int n, x, y, t, **matriz;

    scanf("%d %d %d %d", &n, &x, &y, &t);

    matriz = fazer_matriz(n, t);

    printar_matriz(matriz, n);
    printf("\n");
    make_pgm(matriz, n, "Aleatoria ");
    
    alterar_imagem(matriz, x, y, n, t);
    
    printar_matriz(matriz, n);
    make_pgm(matriz, n, "Modificada Recursivamente ");

    return 0;
}

void make_pgm(int **matriz, int n, char *complemento){
    FILE *pgm;
    char *nome_arquivo = malloc(sizeof(char) * strlen(complemento)+1);
    strcpy(nome_arquivo, complemento);
    strcat(nome_arquivo, "Imagem.pgm");
    pgm = fopen(nome_arquivo, "wb");

    fprintf(pgm, "P2\n");
    fprintf(pgm, "%d %d\n", n, n);
    fprintf(pgm, "%d\n", MAX_RAND-1);

    // salva cada termo da matriz em sua respectiva posicao na imagem
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int pos = matriz[i][j];
            fprintf(pgm, "%d ", pos);
        }
        fprintf(pgm, "\n");
    }
    fclose(pgm);
    free(nome_arquivo);
}

void alterar_imagem(int **matriz, int x, int y, int n, int t){
    // o primeiro pixel por onde a funcao recursiva ira comecar
    // chamado uma vez para cada posicao posicao 
    imagem(matriz, x, y, n, t, x-1, y);
    imagem(matriz, x, y, n, t, x, y+1);
    imagem(matriz, x, y, n, t, x+1, y);
    imagem(matriz, x, y, n, t, x, y-1);
}

int **fazer_matriz(int n, int t){
    
    // com a semente t, salva um numero aleatorio em cada
    // posicao da matriz criada
    srand(t);
    int **matriz = (int**) malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        matriz[i] = (int*) malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++){
            matriz[i][j] = rand() % MAX_RAND;
        }
    }

    return matriz;
}

void printar_matriz(int **matriz, int n){
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void imagem(int **matriz, int x, int y, int n, int t, int a, int b){
    
    // se chegou em alguma borda da imagem, retorna
    if(a < 0 || a >= n || b < 0 || b >= n)
        return;
    
    int p = matriz[x][y];
    int v = matriz[a][b];

    // se ambas as posicoes forem iguais, retorna 
    if(v == p)
        return;

    int m = abs(p - v);

    // se m é menor q t, como manda o enunciado, entao a posicao adiante 
    // da matriz é atualizada e a posicao de pixel se torna esta posicao 
    if(m <= t){
        matriz[a][b] = p;
        x = a;
        y = b;
    }
    else
        return;

    // chama  a funcao para cada vizinho da posicao atual do pixel
    // se um vizinho nao cumprir os requisitos, ele retorna, e vai para o proximo vizinho
    // ate nao ter mais vizinhos, e retornar para o pixel anterior
    imagem(matriz, x, y, n, t, x-1, y);
    imagem(matriz, x, y, n, t, x, y+1);
    imagem(matriz, x, y, n, t, x+1, y);
    imagem(matriz, x, y, n, t, x, y-1);
        
}