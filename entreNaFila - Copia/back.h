typedef struct lista lista_t;
typedef struct no no_t;

struct no{
    int chave, tempo, back;
    no_t *ant, *prox, *backward;
};

struct lista{
    no_t *inicio, *fim;
    int tam;
};

lista_t *criar();
int liberar(lista_t *l);
int remover(lista_t *l, int n);
int inserir(lista_t *l, int c, int back, int inserir);
void imprimir(lista_t *l);
no_t *backward(lista_t *l, int j);
void remover_back(lista_t *l, int n);
int buscar(lista_t *l, int chave);