#include <stdio.h>
#include <stdlib.h>
#include "back.h"

int main(){
    lista_t *l;
    l = criar();
    char op;
    int n, j, tempo = 0;

    scanf("%c", &op);
    
    // continua ate entrarem com f 
    while(op != 'f'){
        if(op == 'i'){
            scanf("%d %d", &n, &j);
            inserir(l, n, j, tempo);
            tempo++;
        }
        else if(op == 'r'){
            scanf("%d", &n);
            remover(l, n);
            tempo++;
        }
        scanf("%c", &op);
    };

    imprimir(l);

    return 0;
}