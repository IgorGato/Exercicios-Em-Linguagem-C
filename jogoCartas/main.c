#include <stdio.h>
#include <stdlib.h>

#include "cartas.h"

int main(){
    monte_t *compra, *descarte, *morto;
    int i, x, j, n_cartas, num_rodadas;

    scanf("%d", &n_cartas);

    int *vetor;

    vetor = malloc(sizeof(int) * n_cartas);

    compra = criar(n_cartas);
    morto = criar(n_cartas);

    for(i = (n_cartas - 1); i >= 0; i--){
        scanf("%d", &vetor[i]);
    }
    // inverte a ordem de entrada das cartas para colocar no baralho
    for(i = 0; i < compra->num_cartas; i++){
            push(compra, vetor[i]);
    }

    num_rodadas = compras(compra, morto, n_cartas);
    printf("%d\n", num_rodadas);

    destruir(compra);
    destruir(morto);
}
