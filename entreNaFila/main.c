#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "covid.h"

int main(){
    fila_t *covid;
    int num_op, i = 0;
    char *entrada = NULL;
    char **entrada_separada = NULL;
    clientes_t *x;

    num_op = atoi(readline(stdin));
    covid = criar();
        
    while(i != num_op){
        entrada = readline(stdin);

        if(!strcmp(entrada, "SAI")){
            if(remover(covid, x) != 0){
                printar_saida(x);
            }
        }
        else {
            entrada_separada = separar(entrada);
            x = informacoes(entrada_separada);
            inserir(covid, x);
        }
        i++;
    }

    destruir(covid);

    return 0;
}