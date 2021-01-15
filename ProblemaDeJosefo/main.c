#include <stdio.h>
#include <stdlib.h>
#include "josefo.h"

int main(){
    int n, i, posicao, t_casos, x = 0, k;

    scanf("%d", &t_casos);

    while(x < t_casos){
        scanf("%d %d", &n, &k);

        lista_t *l = criar();
        for(i = 0; i < n; i++){
            inserir(l, i+1);
        }

        while(tamanho(l) > 1){
            rodar_e_rodar(l, k, &posicao);
            remover(l, posicao);
        }

        printar(l, x+1);
        destruir(l);
        x++;
    }

    return 0;

}