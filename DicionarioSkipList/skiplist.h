typedef struct skiplist skip_t;
typedef struct no no_t;
typedef struct input_dic input_dic;



skip_t *criar();
no_t *vetor_nos(char *chave, char *definicao, int max_level);
void inserir(skip_t *l, input_dic *chave);
int random_nivel(skip_t *l);
char *readline(FILE *input);
input_dic *separar(char *palavra);
void escolher_acao(skip_t *l, input_dic *palavra);
void destruir(skip_t *l);
void remover(skip_t *l, char *chave);
no_t *buscar(skip_t *l, input_dic *chave);
void alteracao(skip_t *l, input_dic *palavra);
void print_busca(skip_t *l, input_dic *palavra);
void impressao(skip_t *l, input_dic *palavra);