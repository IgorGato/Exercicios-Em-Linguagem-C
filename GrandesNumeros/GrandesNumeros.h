
typedef struct lista lista_t;
typedef struct no no_t;
typedef struct conta conta_t;

lista_t *criar();
void inserir(lista_t *l, int x);
int tamanho(lista_t *l);
void imprimir(lista_t *l);
void destruir(lista_t *l);
void remover(lista_t *l);
conta_t **ler_guardar_input(int num_inputs);
char *read_line(FILE *input);
conta_t *separar_input(char *inputs);
void insert_number(lista_t *num1, lista_t *num2, conta_t **num, int position);
void printar(conta_t **inputs);
lista_t *sum(lista_t *num1, lista_t *num2);
void inser_number_part(lista_t *num, char *char_num);
int maior_menor_igual(lista_t *num1, lista_t *num2);
void escolher_operacao(conta_t **inputs, int num_op);
