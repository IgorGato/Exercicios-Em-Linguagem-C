

typedef struct spotify_information spot_fy;
struct spotify_information{
    char *track_name;
    char *track_id;
    char *album_name;
    char *album_id;
    char *artist_name;
    char *artist_id;
    char *release_date;
    char *length;
    char *popularity;
    char *acousticness;
    char *danceability;
    char *energy;
    char *instrumentalness;
    char *liveness;
    char *loudness;
    char *speechiness;
    char *tempo;
    char *time_signature;

};

typedef struct total_info{
    spot_fy **infos;
    int total_music;
    int total_artists;
}spot_info;

typedef struct musica_info{
    char *track_name;
} musica_info;

typedef struct spot_art{
    char *artist_name;
    char *artist_id;
    int num_musics;
    float artist_popularity;
    musica_info **musicas;
}spot_art;

typedef struct spot_artitas_data{
    spot_art **data_artistas;
    int total_music;
    int total_artists;
}spot_artitas_data;


spot_info *criar();
void salvar_dados(spot_info *data_base, char *nome_arq);
char *cpy_content(char *string);
spot_fy *save_on_struct(char **dados);
void imprimir(spot_artitas_data *data_artistas);
spot_artitas_data *criar_data_artistas();
spot_art *save_artist(spot_fy *art_info);
void salvar_dados_artitas(spot_info *data_base, spot_artitas_data *data_artistas);
void save_popularity(spot_art *artista, spot_fy *art_info);
void popularity(spot_artitas_data *artistas);
void merge(spot_artitas_data *v, spot_artitas_data *temporario1, int inicio, int meio1, int meio2, int fim);
void mergesort(spot_artitas_data *artistas, spot_artitas_data *aux, int inicio, int fim);
void auxiliar_mergesort(spot_artitas_data *artistas);
char **readline(char *linha);
void destruir_data_base(spot_info *data_base);
void destruir_data_artistas(spot_artitas_data *artistas);