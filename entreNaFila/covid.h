
#define tam_fila 20
typedef struct fila fila_t;
typedef struct clientes clientes_t;

fila_t *criar();
int empty(fila_t *c);
int full(fila_t *c);
int inserir(fila_t *c, clientes_t *x);
int remover(fila_t *c, clientes_t *x);
void destruir(fila_t *c);
char *readline();
char **separar(char *frase);
clientes_t *informacoes(char** x);
void printar_saida(clientes_t *c);