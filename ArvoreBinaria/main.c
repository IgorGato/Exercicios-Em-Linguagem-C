#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ab_print.h"

int main(){
    arvore_t *arvore = criar();
    preencher_arvore(arvore);
    
    // imprime de forma recursiva todos os nos da arvore
    // necessario enviar a raiz e o pai da raiz 
    // (no caso -1 por nao possuir pai)
    print(arvore->raiz, -1);

    finalizar(arvore->raiz);
    return 0;
}