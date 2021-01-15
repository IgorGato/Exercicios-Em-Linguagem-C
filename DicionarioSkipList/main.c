#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

int main(){
    skip_t *lista;
    lista = criar();
    
    while(!feof(stdin)){
        char *palavra = readline(stdin);  
        if(strlen(palavra)){
            input_dic *dic = separar(palavra);
            escolher_acao(lista, dic); 
            free(dic);
        }
        free(palavra);
    }

    destruir(lista);
}
