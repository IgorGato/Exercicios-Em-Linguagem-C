#include <stdio.h>
#include <stdlib.h>

#include "sub.h"

int main(){
    palavras_t *word;

        word = criar();
        subspalavra(word);
        printar(word);
        destruir(word);

    return 0;
}