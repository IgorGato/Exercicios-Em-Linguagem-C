#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubro_negra.h"

int main(){
    arvore_t *arvore = criar();

    int num_operacoes, operacao, numero, res;
    scanf("%d", &num_operacoes);

    for(int i = 0; i < num_operacoes; i++){
        scanf("%d", &operacao);

        switch(operacao){
            case 1:
                scanf("%d", &numero);
                inserir(&arvore->raiz, numero);
                break;
            case 2:
                scanf("%d", &numero);
                buscaPrePro_aux(arvore->raiz, numero, 2);
                break;
            case 3:
                scanf("%d", &numero);
                buscaPrePro_aux(arvore->raiz, numero, 3);
                break;
            case 4:
                printf("%d\n", maior_numero(arvore->raiz));
                break;
            case 5:
                printf("%d\n", menor_numero(arvore->raiz));
                break;
            case 6:
                pre_ordem(arvore->raiz);
                printf("\n");
                break;
            case 7:
                em_ordem(arvore->raiz);
                printf("\n");
                break;
            case 8:
                pos_ordem(arvore->raiz);
                printf("\n");
                break;
            default:
                break;
        }
    }
    
    finalizar(arvore->raiz);
    free(arvore);
    return 0;
}