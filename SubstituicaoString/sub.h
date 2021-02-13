
// struct que sera usada para armazenar cada frase, seu erro e correcao
typedef struct{
    char palavra[100];
    char erro[20];
    char correcao[20];
} fields;
// struct principal que sera criada pelo programa
typedef struct{
    fields *infos;
    int num_frases;
} palavras_t;


palavras_t *criar();
int subspalavra(palavras_t *word);
int printar(palavras_t *word);
int destruir(palavras_t *word);
