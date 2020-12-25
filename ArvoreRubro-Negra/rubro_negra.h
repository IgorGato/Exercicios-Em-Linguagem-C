typedef int elem;
typedef struct no no_t;


typedef struct arvore{
    no_t *raiz;
}arvore_t;


arvore_t *criar();
int vazia(arvore_t *a);
void finalizar(no_t *raiz);
void imprimir(no_t *raiz);
void pre_ordem(no_t *raiz);
void em_ordem(no_t *raiz);
void pos_ordem(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
void  inserir(no_t **raiz, elem x);
int cor(no_t *h);
void troca_cor(no_t *h);
no_t *insere_avl(no_t *h, int valor);
void troca_cor(no_t *h);
int cor(no_t *h);
no_t *dd(no_t *desb);
no_t *ee(no_t *desb);
int maior_numero(no_t *raiz);
int menor_numero(no_t *raiz);
void buscaPrePro_aux(no_t *root, int key, int opcao);
no_t *buscaPre(no_t *raiz, no_t *pre, int chave);
no_t *buscaPos(no_t *raiz, no_t *pos, int chave);


