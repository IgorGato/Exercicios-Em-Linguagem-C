#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treap.h"

int main(){
    arvore_t *arvore;
    arvore = criar();
    char *acao;
    int numero, prioridade, num_operacoes;

    scanf("%d", &num_operacoes);

    for(int i = 0; i < num_operacoes; i++){
        
        do{
            acao = readline(stdin);
        }while(strlen(acao) < 2);

        //verifica qual opcao foi escrita na entrada e faz a ação de acordo
        if(!strcmp(acao, "insercao")){
            scanf("%d %d", &numero, &prioridade);
            verificar_e_inserir(arvore, numero, prioridade);
        }else if(!strcmp(acao, "buscar")){
            scanf("%d", &numero);
            printf("%d\n", busca(arvore->raiz, numero));
        }else if(!strcmp(acao, "remocao")){
            scanf("%d", &numero);
            delete(&arvore->raiz, numero);
        }else if(!strcmp(acao, "impressao")){
            acao = readline(stdin);
            if(!strcmp(acao, "preordem")){
                pre_ordem(arvore->raiz);
                printf("\n");
            }else if(!strcmp(acao, "largura")){
                em_largura(arvore->raiz);
                printf("\n");
            }else if(!strcmp(acao, "ordem")){
                em_ordem(arvore->raiz);
                printf("\n");    
            }else if(!strcmp(acao, "posordem")){
                pos_ordem(arvore->raiz);
                printf("\n");    
            }
        }
    }

    free(acao);
    return 0;
}