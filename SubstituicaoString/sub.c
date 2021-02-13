#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sub.h"


palavras_t *criar(){
    palavras_t *word;
    int j = 0, contador = 0;

    word = (palavras_t*) malloc(sizeof(palavras_t));

    // enquanto nao for o fim do arquivo continua salvando o conteudo de cada linha em seu respectivo espaco na struct
    // de forma dinamica a struct de armazenamento do texto eh criada ate o fim do arquivo
    while(!feof(stdin)){
        word->infos = realloc(word->infos, sizeof(fields) * (contador + 1));
        fgets(word->infos[contador].palavra, 100, stdin);
        fgets(word->infos[contador].erro, 20, stdin);
        fgets(word->infos[contador].correcao, 20, stdin);
        contador++;
        j++;
    };
    // é salvo na struct principal tambem a quantidade de frases havia no arquivo
    // para poder ser utilizado posteriormente 
    word->num_frases = contador;

    return word;
}

int subspalavra(palavras_t *word){
    int i, j, k = 0, m = 0;
    char subvetor[100];

        for(i = 0; i < word->num_frases; i++){
            for(j = 0; j < strlen(word->infos[i].palavra); j++){
                m = j;
                // verifica se os caracteres de certa posicao da string sao equivalentes aos 
                // mesmo caracteres que devem ser substituidos 
                while (word->infos[i].palavra[m] == word->infos[i].erro[k]){
                    k++;
                    m++;
                }
                // se forem equivalentes entram nesta condicional
                if(k == strlen(word->infos[i].erro) - 1){
                    // da posicao dos caracteres a serem substituidos, ate o final da frase
                    // é armazenado num vetor auxiliar
                    strcpy (subvetor, &word->infos[i].palavra[m]);
                    m = m - k;
                    k = 0;
                        // a correcao então é copiada para o vetor da frase original
                        while(word->infos[i].correcao[k] != '\0'){
                            if(word->infos[i].correcao[k] != '\n'){
                                word->infos[i].palavra[m] = word->infos[i].correcao[k];
                                m++;
                            }
                            k++;
                        }
                        // o resto da frase que foi salvo no vetor auxiliar é copiado novamente para a frase original
                        for(k = 0; k < strlen(subvetor); k++, m++){
                            word->infos[i].palavra[m] = subvetor[k];
                        }
                    // adiciona um finalizador de string
                    word->infos[i].palavra[m] = '\0';
                }

                if(word->infos[i].palavra[j] != word->infos[i].erro[k]) {
                    k = 0;
                };
            }
        }
};

int printar(palavras_t *word){
        // printa as frases corrigidas
        for(int i = 0; i < word->num_frases; i++){
            printf("%s", word->infos[i].palavra);
        }
    return 1;
};

int destruir(palavras_t *word){
        // desaloca a struct das palavras
        free(word->infos);
        free(word);
    return 1;
}