

typedef struct lista lista_t;
typedef struct no no_t;

lista_t *criar();
void destruir(lista_t *l);
void inserir(lista_t *l, int x);
void printar(lista_t *l, int x); 
void remover(lista_t *l, int x);
int tamanho(lista_t *l);
void rodar_e_rodar(lista_t *l, int k, int *posicao);