#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spot.h"

// cria vetor de struct para salvar todas informacoes do arquivo
spot_info *criar(){
    spot_info *data_base;
    data_base = malloc(sizeof(spot_info));
    data_base->infos = NULL;
    data_base->total_artists = 0;
    data_base->total_music = 0;

    return data_base;
}

// cria vetor de struct que salva os dados do artista
spot_artitas_data *criar_data_artistas(){
    spot_artitas_data *artistas;
    artistas = malloc(sizeof(spot_artitas_data));
    artistas->data_artistas = NULL;
    artistas->total_artists = 0;
    artistas->total_music = 0;

    return artistas;
};

void salvar_dados(spot_info *data_base, char *nome_arq){
    FILE *csv_file;
    csv_file = fopen(nome_arq, "r");

    char line_infos[1024];

    // descarta a primeira linha do arquivo com o nome das colunas 
    fgets(line_infos,sizeof(line_infos), csv_file);

    while(fgets(line_infos,sizeof(line_infos), csv_file)){ 
        char **dados = NULL;
        
        dados = readline(line_infos);
        // aloca uma nova linha e salva a informacao 
        data_base->infos = realloc(data_base->infos, sizeof(spot_info) * (data_base->total_music + 1));
        data_base->infos[data_base->total_music++] = save_on_struct(dados);

    }

    fclose(csv_file);
}

char **readline(char *linha){

    char *letra, *palavra = NULL;
    char **palavras = NULL;
    int tam_palavra = 0, num_palavras = 0;
    char *substitudo = malloc(sizeof(char));
    substitudo = "0";

    for(int i = 0; i < strlen(linha); i++){
        // percorre toda linha passada pra funcao, enquanto nao encontra ';' salva 
        // os caracteres num vetor de char
        if(linha[i] != ';' && i <= strlen(linha)){
            palavra = realloc(palavra, sizeof(char) * tam_palavra+1);
            palavra[tam_palavra++] = linha[i];
        }
        else{
            // quando encontra ';' salva a palavra num vetor de palavras e comeca uma palavra nova
            palavras = realloc(palavras, sizeof(char*) * num_palavras+1);
            
            if(tam_palavra == 0)
                palavras[num_palavras] = substitudo;
            else{
                palavra = realloc(palavra, sizeof(char) * tam_palavra+1);
                palavra[tam_palavra] = '\0';
                palavras[num_palavras] = palavra;
            }
            num_palavras++;
            palavra = NULL;
            tam_palavra = 0;
            i++;
        }
    }

    palavras[num_palavras] = substitudo;

    return palavras;
}

void salvar_dados_artitas(spot_info *data_base, spot_artitas_data *artistas){
    int i = 0, j;

    for(i = 0; i < data_base->total_music; i++){ 

        // verifica se o nome do artista ja se encontra no vetor
        for(j = 0; j < artistas->total_artists; j++){
            if(strcmp(data_base->infos[i]->artist_name, artistas->data_artistas[j]->artist_name) == 0)
                break;
        }
        // se nao possuir o artista, é alocado dinamicamente
        if(j == artistas->total_artists){
            artistas->data_artistas = realloc(artistas->data_artistas, sizeof(spot_art) * artistas->total_artists+1);
            artistas->data_artistas[artistas->total_artists] = save_artist(data_base->infos[i]);
            artistas->total_artists++;
        }
        // salva a popularidade da musica 
        save_popularity(artistas->data_artistas[j], data_base->infos[i]);
    }

    artistas->total_music = data_base->total_music; 
    popularity(artistas);
}

void save_popularity(spot_art *artista, spot_fy *art_info){
    artista->num_musics++;
    artista->artist_popularity += atof(art_info->popularity);
}

void popularity(spot_artitas_data *artistas){
    for(int i = 0; i < artistas->total_artists; i++){
        artistas->data_artistas[i]->artist_popularity /= artistas->data_artistas[i]->num_musics;
    }
};

spot_art *save_artist(spot_fy *art_info){
    spot_art *dados_artista;
    dados_artista = malloc(sizeof(spot_art));
    dados_artista->musicas = NULL;

    dados_artista->artist_name = art_info->artist_name;
    dados_artista->artist_id = art_info->artist_id;
    dados_artista->num_musics = 0;
    dados_artista->artist_popularity = 0;

    return dados_artista;
}

// salva cada informacao da musica na struct
spot_fy *save_on_struct(char **dados){
    spot_fy *music;
    music = malloc(sizeof(spot_fy));

    music->track_name = cpy_content(dados[0]);
    music->track_id = cpy_content(dados[1]);
    music->album_name = cpy_content(dados[2]);
    music->album_id = cpy_content(dados[3]);
    music->artist_name = cpy_content(dados[4]);
    music->artist_id = cpy_content(dados[5]);
    music->release_date = cpy_content(dados[6]);
    music->length = cpy_content(dados[7]);
    music->popularity = cpy_content(dados[8]);
    music->acousticness = cpy_content(dados[9]);
    music->danceability = cpy_content(dados[10]);
    music->energy = cpy_content(dados[11]);
    music->instrumentalness = cpy_content(dados[12]);
    music->liveness = cpy_content(dados[13]);
    music->loudness = cpy_content(dados[14]);
    music->speechiness = cpy_content(dados[15]);
    music->tempo = cpy_content(dados[16]);
    music->time_signature = cpy_content(dados[17]);

    return music;
}

// copia o conteudo da string para uma nova string
char *cpy_content(char *string){
    char *nova_string = NULL;

    nova_string = realloc(nova_string, sizeof(char) * strlen(string)+1);
    strcpy(nova_string, string);

    return nova_string;
}

void imprimir(spot_artitas_data *data_artistas){

    printf("O Dataset contem %d Artistas e %d Musicas\n", data_artistas->total_artists, data_artistas->total_music);
    printf("Os artistas mais populares sao:\n");
    for(int i = 0; i < data_artistas->total_artists; i++){
        printf("(%d) Artista: %s, Musicas: %d musicas, Popularidade: %.2f, Link: https://open.spotify.com/artist/%s\n", 
        i+1, data_artistas->data_artistas[i]->artist_name, data_artistas->data_artistas[i]->num_musics, data_artistas->data_artistas[i]->artist_popularity, data_artistas->data_artistas[i]->artist_id);
    }
}

void auxiliar_mergesort(spot_artitas_data *artistas){
    spot_artitas_data *aux;
    aux = malloc(sizeof(spot_artitas_data));
    aux->data_artistas = malloc(sizeof(spot_artitas_data) * artistas->total_artists);
    for(int i = 0; i < artistas->total_artists; i++){
        aux->data_artistas[i] = artistas->data_artistas[i];
    }

    mergesort(artistas, aux, 0, artistas->total_artists);
}

// mergesort de tres vias para ordenar as structs de acordo com a popularidade do artista
void mergesort(spot_artitas_data *artistas, spot_artitas_data *aux, int inicio, int fim){
    if(fim - inicio < 2) 
        return;

        int meio1 = inicio + (fim - inicio + 1)/3;
        int meio2 = inicio + 2*(fim - inicio + 1)/3;
        // verifica se o numero possui resto 1, se positivo entao acrescenta 1 a 
        // primeira metade para que seja dividido de maneira apropriada
        if((fim-inicio)%3 == 1)
            meio1++;

        mergesort(aux, artistas, inicio, meio1);
        mergesort(aux, artistas, meio1, meio2);
        mergesort(aux, artistas, meio2, fim);
        merge(aux, artistas, inicio, meio1, meio2, fim);
}

void merge(spot_artitas_data *v, spot_artitas_data *temporario1, int inicio, int meio1, int meio2, int fim){
    int p1 = inicio, p2 = meio1, p3 = meio2, i = inicio;

    for(i = inicio; i < fim; i++){
        // compara numero dos tres vetores, o que for 
        // menor é salvo no vetor auxiliar
        if((p1 < meio1) && (p2 < meio2) && (p3 < fim)){
            if(v->data_artistas[p1]->artist_popularity > v->data_artistas[p2]->artist_popularity){
                if(v->data_artistas[p1]->artist_popularity > v->data_artistas[p3]->artist_popularity){
                    temporario1->data_artistas[i] = v->data_artistas[p1++];
                }
                else{
                    temporario1->data_artistas[i] = v->data_artistas[p3++];
                }
            }
            else{
                if(v->data_artistas[p2]->artist_popularity > v->data_artistas[p3]->artist_popularity){
                    temporario1->data_artistas[i] = v->data_artistas[p2++];
                }
                else{
                    temporario1->data_artistas[i] = v->data_artistas[p3++];
                }
            }
            
        }
        else{
            // se um dos vetores ja nao possuir mais nenhum numero
            // compara entao os numeros dos vetores restantes 
            if((p2 < meio2) && (p3 < fim)){
                if(v->data_artistas[p2]->artist_popularity > v->data_artistas[p3]->artist_popularity){
                    temporario1->data_artistas[i] = v->data_artistas[p2++];
                }
                else{
                    temporario1->data_artistas[i] = v->data_artistas[p3++];
                };

            }

            else if((p1 < meio1) && (p3 < fim)){
                if(v->data_artistas[p1]->artist_popularity > v->data_artistas[p3]->artist_popularity){
                    temporario1->data_artistas[i] = v->data_artistas[p1++];
                }
                else{
                    temporario1->data_artistas[i] = v->data_artistas[p3++];
                };

            }

            else if((p1 < meio1) && (p2 < meio2)){
                
                if(v->data_artistas[p1]->artist_popularity > v->data_artistas[p2]->artist_popularity){
                    temporario1->data_artistas[i] = v->data_artistas[p1++];
                }
                else{
                    temporario1->data_artistas[i] = v->data_artistas[p2++];
                };

            }

            else{
                // quanto haver apenas um vetor, os numeros deste 
                // sao apenas copiados para o vetor auxiliar
                if(p3 < fim){
                    temporario1->data_artistas[i] = v->data_artistas[p3++];
                }

                else if(p1 < meio1){
                    temporario1->data_artistas[i] = v->data_artistas[p1++];
                }

                else if(p2 < meio2){
                    temporario1->data_artistas[i] = v->data_artistas[p2++];
                }
            }
        }
    }
}

void destruir_data_base(spot_info *data_base){

    for(int i = 0; i < data_base->total_music;i++)
        free(data_base->infos[i]);
    free(data_base);
}

void destruir_data_artistas(spot_artitas_data *artistas){
    for(int i = 0; i < artistas->total_artists; i++)
        free(artistas->data_artistas[i]);
    free(artistas);
};