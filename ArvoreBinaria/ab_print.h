typedef int elem;
typedef struct no no_t;
typedef struct arvore{
    no_t *raiz;
}arvore_t;


arvore_t *criar();
void preencher_arvore(arvore_t *arvore);
int vazia(arvore_t *a);
void finalizar(no_t *raiz);
int altura(no_t *raiz);
no_t *busca(no_t *raiz, elem x);
int inserir_esq(arvore_t *a, elem x, elem pai);
int inserir_dir(arvore_t *a, elem x, elem pai);
void print(no_t *raiz, elem pai);
int print_filho(no_t *filho);
char *print_tipo(no_t *raiz, elem pai);
int print_grau(no_t *raiz);