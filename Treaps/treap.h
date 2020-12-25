typedef struct no no_t;
typedef int elem;
typedef struct no_l no_lista;
typedef struct lista lista_t;

typedef struct arvore{
    no_t *raiz;
}arvore_t;

struct lista{
    no_lista *ini, *fim;
    int tam;
};

arvore_t *criar();
no_t *insere_no(no_t *h, int valor, int prioridade);
int inserir(no_t **raiz, elem x, int prioridade);
no_t *ee(no_t *desb);
no_t *dd(no_t *desb);
void pos_ordem(no_t *raiz);
void em_ordem(no_t *raiz);
void pre_ordem(no_t *raiz);
void em_largura(no_t *raiz);
void inserir_lista(lista_t *l, no_t *x);
void remover_lista(lista_t *l);
lista_t *criar_lista();
int delete(no_t **raiz, int x);
no_t* delete_no(no_t* raiz, int chave);
char *readline(FILE *imput);
int busca(no_t *raiz, elem x);
void verificar_e_inserir(arvore_t *arvore, int numero, int prioridade);

