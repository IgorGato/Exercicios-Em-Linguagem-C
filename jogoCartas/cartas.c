#include <stdio.h>
#include <stdlib.h>


#include "cartas.h"

// cria o baralho
monte_t *criar(int n_cartas){
    monte_t *baralho;
        baralho =(monte_t*) malloc(sizeof(monte_t));

        baralho->num_cartas = n_cartas;
        baralho->cartas = (int *) malloc(sizeof(int) * baralho->num_cartas);
        baralho->topo = -1;

        return baralho;
}

int full(monte_t *baralho){
        
    if(baralho->topo == baralho->num_cartas - 1){
        return 1;
    }

    else return 0;
}

int empty(monte_t *baralho){
        
    if(baralho->topo == -1){
        return 1;
    }

    return 0;
}

int push(monte_t *baralho, int x){
        if(full(baralho)){
            return -1;
        }
            baralho->topo++;
            baralho->cartas[baralho->topo] = x;
    return 1;
}

int pull(monte_t *baralho, int *x){
    if(empty(baralho)){
        return -1;
    }
        *x = baralho->cartas[baralho->topo];
        baralho->topo--;
    
}

int printar(monte_t *baralho){

    for(int i = baralho->topo; i >= 0; i--){
        printf("%d\t", baralho->cartas[i]);
    }
    printf("\n");
    return 1;
}

void destruir(monte_t *baralho){
    if(baralho != NULL)

        free(baralho);
}

int *inverter(int *vetor){
    int *v_invertido;


};

int compras(monte_t *compra, monte_t *morto, int n_cartas){
    int i = 0, j = 1, x, num_rodadas = 0, vetor[n_cartas];
    monte_t *descarte;
    // enquanto todas as cartas nao tiverem ido para o baralho "morto" o programa continua rodando
    while(morto->topo < n_cartas - 1){
        // cria um baralho descarte do tamanho do numero de cartas ainda presente no jogo
        descarte = criar(compra->topo + 1);

            while(compra->topo > -1){
                pull(compra, &x);

                // se a carta pega do topo do baralho for igual a sequencia de numeros 
                // entao j aumenta em 1 e a carta vai para o baralho morto
                if(x == j){
                    push(morto, x);
                    j++;
                }
                // se nao a carta vai para um vetor auxiliar para ir para o baralho descarte
                else{
                    vetor[i] = x;
                    i++;
                }
            }
            
            // inverte a ordem de entrada das cartas para colocar no baralho
            for(x = i - 1; x >= 0; x--){
                push(descarte, vetor[x]);
            }
            i = 0;
            compra = descarte;
            num_rodadas++;
    }

    destruir(descarte);

    return num_rodadas ;
}
