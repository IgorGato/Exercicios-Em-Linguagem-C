#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spot.h"

int main(){
    spot_info *data_base;
    spot_artitas_data *artistas;
    char nome_arq[255];

    scanf("%s", nome_arq);
    data_base = criar();
    salvar_dados(data_base, nome_arq);
    artistas = criar_data_artistas();

    salvar_dados_artitas(data_base, artistas);
    auxiliar_mergesort(artistas);

    imprimir(artistas);
    destruir_data_base(data_base);
    destruir_data_artistas(artistas);

    return 0;
}