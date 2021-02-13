#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char **fazer_labirinto();
void movimento();
void verificar();
int pessoas();
int caminhos();
int visitados();
float porcentagem_exploracao();

int main(){

    FILE *arquivo;
    char *nome_arquivo = NULL, **labirinto;
    int m, n, x, y, i, j = 0, **caminhos_possiveis = NULL;
    int num_caminhos = 0, n_pessoas, n_caminhos, n_visitados;
    float exploracao;

    nome_arquivo = readline(stdin);
    arquivo = fopen(nome_arquivo, "r");

    // le o tamanho do labirinto e possicao inicial 
    fscanf(arquivo,"%d %d\n", &m, &n);
    fscanf(arquivo,"%d %d\n", &x, &y);


        labirinto = fazer_labirinto(arquivo, m, n);

        n_pessoas = pessoas(labirinto, m, n);
        n_caminhos = caminhos(labirinto, m, n);

        movimento(labirinto, x, y, m, n, caminhos_possiveis, &num_caminhos);

        n_visitados = visitados(labirinto, m, n);
        exploracao = porcentagem_exploracao(n_caminhos, n_visitados);

        // printa o labirinto e o caminho percorrido para sair dele 
        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                printf("%c", labirinto[i][j]);
            }
            printf("\n");
        }

    printf("\nVoce escapou de todos! Ninguem conseguiu te segurar!\n");
    printf("Veja abaixo os detalhes da sua fuga:\n");
    printf("----Pessoas te procurando: %d\n", n_pessoas);
    printf("----Numero total de caminhos validos:   %d\n", n_caminhos);
    printf("----Numero total de caminhos visitados: %d\n", n_visitados);
    printf("----Exploracao total do labirinto: %.1lf%%\n", exploracao);

    for(i = 0; i < m; i++){
        free(labirinto[i]);
    }
        free(labirinto);
        free(nome_arquivo);

    return 0;
}
// le o nome do arquivo que possui o nome do arquivo de labirinto
char *readline(FILE *imput){
    char letra, *frase = NULL;
    int contador = 0;

    do{
        letra = fgetc(imput);
        frase = realloc(frase, sizeof(char) * (contador + 1));
        frase[contador] = letra;
        contador++;
    } while (letra != '\n' && !feof(imput));

    frase[contador - 1] = '\0';

    return frase;
}

// aloca dinamicamente um vetor duplo que sera o labirinto 
// de acordo com o tamanho de m e n contidos no documento
char **fazer_labirinto(FILE *arquivo, int m, int n){
    
    char **labirinto = NULL, letra;
    int i, j;

    labirinto = (char**) malloc(sizeof(char*) * m);
    for(i = 0; i < m; i++){
        labirinto[i] = (char*) malloc(sizeof(char) * n);
        for(j = 0; j <= n; j++){
            letra = fgetc(arquivo);
            labirinto[i][j] = letra;
        }
    }

    return labirinto;
}

void movimento(char **labirinto, int x, int y, int m, int n, int **caminhos_possiveis, int *num_caminhos){
    
    int caminho = 0, novox = x, novoy = y;
    labirinto[x][y] = '*';

    // se o ultimo asterisco estiver na borda da matriz, o programa retorna pois significa que saiu do labirinto 
    if (x == 0 || x == m - 1 || y == 0 || y == n - 1){
        return;
    }

    //aloca todas as posicoes que estao sendo exploradas 
    caminhos_possiveis = realloc(caminhos_possiveis, sizeof(int*) * (*num_caminhos + 1));
    caminhos_possiveis[*num_caminhos] = calloc(3, sizeof(int));
    caminhos_possiveis[*num_caminhos][0] = x;
    caminhos_possiveis[*num_caminhos][1] = y;

    // marca se a posicao possui mais de um caminho diferente para percorrer
    // alem de movimentar o asterisco para um caminho possivel 
    if (labirinto[x - 1][y] == '.'){
        caminhos_possiveis[*num_caminhos][2]++;
        caminho++;
        novox--;
    }
    
    if (labirinto[x][y + 1] == '.'){
        caminhos_possiveis[*num_caminhos][2]++;
        if(caminho == 0){
            caminho++;
            novoy++;
        }
    }

    if (labirinto[x + 1][y] == '.'){
        caminhos_possiveis[*num_caminhos][2]++;
        
        if(caminho == 0){
            caminho++;
            novox++;
        }
    }

    if (labirinto[x][y - 1] == '.'){
        caminhos_possiveis[*num_caminhos][2]++;
        
        if(caminho == 0){
            caminho++;
            novoy--;
        }
    };

    (*num_caminhos)++;

    // retorna para esta mesma função com a nova posicao de x e y 
    if (caminho == 1){
        return movimento(labirinto, novox, novoy, m, n, caminhos_possiveis, num_caminhos);
    }

    // se entrou em um beco sem saida sem caminhos mais disponiveis o laço verifica 
    // qual foi a ultima bifurcacao visitada para retornar àquela posicao 
    else {
        int i, j = 0;
        for(i = (*num_caminhos - 1); i > 0; i--){
            if(caminhos_possiveis[i][2] > j){
                j = i;
            }
        }
        caminhos_possiveis[j][2]--;
        return movimento(labirinto, caminhos_possiveis[j][0], caminhos_possiveis[j][1], m, n, caminhos_possiveis, num_caminhos);
    }

}

// retorna o numero de pessoas que cercam o jogador 
int pessoas(char **labirinto, int m, int n){
    int i, j, n_pessoas = 0;

        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                if(labirinto[i][j] == '#'){
                    n_pessoas++;
                }
            }
        }

    return n_pessoas;
}

// retorna quais os espaços livres possiveis de serem visitados
int caminhos(char **labirinto, int m, int n){
    int i, j, n_caminhos = 0;

        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                if(labirinto[i][j] == '.'){
                    n_caminhos++;
                }
            }
        }

    return n_caminhos;
}

// retorna os caminhos visitados ate encontrar a saida
int visitados(char **labirinto, int m, int n){
    int i, j, n_visitados = 0;

        for(i = 0; i < m; i++){
            for(j = 0; j < n; j++){
                if(labirinto[i][j] == '*'){
                    n_visitados++;
                }
            }
        }
    
    return n_visitados;
}

// retorna a porcentagem do labirinto que foi explorado
float porcentagem_exploracao(int n_caminhos, int n_visitados){
    return (100 * n_visitados) / n_caminhos;
}


