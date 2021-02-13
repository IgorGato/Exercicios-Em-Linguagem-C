#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *armazenar();
int **contar();

int main(){
    int *vetor_num = NULL, i = 0, contador = 0;
    int **numeros = NULL;

    vetor_num = armazenar(stdin, &i);
    numeros = contar(vetor_num, i, &contador);

    for(i = 0; i < contador; i++){
        printf("%d (%d)\n", numeros[i][0], numeros[i][1]);
    }

}

int *armazenar(FILE *imput, int *i){
    int *vetor_num = NULL;
        
        // ira alocar de forma dinamica cada valor da entrada
        while(!feof(imput)){
            vetor_num = realloc(vetor_num, sizeof(int) * (*i + 1));
            scanf("%d", &vetor_num[*i]);
            *i = *i + 1;
        }

    return vetor_num;
}
// cria um vetor duplo para se add o numero e quantas vezes ele foi add
int **contar(int *vetor_num, int i, int *contador){
    int **numeros = NULL, j = 0, h = 0, k;

        // enquanto j nao for igual ao numero de numeros do vetor ele continua contanto 
        while (j != i){
            k = 0;
            
            // verifica se o numero atual é igual a um numero ja adicionado 
            for(h = 0; h < *contador; h++){
                // se for igual entao adiciona mais um ao contador de numero de vezes ele foi adicionado 
                if(numeros[h][0] == vetor_num[j]){
                    numeros[h][1]++;
                    k = 1;
                }
            }
            
            // se o numero nao tiver sido adicionado ainda no vetor de numeros entao ele 
            // eh adicionado e o contador de quantas vezes ele foi add é iniciado em 1
            if(k == 0){
            numeros = (int **) realloc(numeros, sizeof(int*) * (*contador + 1));
            numeros[*contador] = calloc(2, sizeof(int));
            numeros[*contador][0] = vetor_num[j];
            numeros[*contador][1] = 1;
            *contador = *contador + 1;
            }

            j++;

        }

    return numeros;
}