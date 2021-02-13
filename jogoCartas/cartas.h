
// struct pra guardar o baralho
typedef struct monte{
    int topo;
    int *cartas;
    int num_cartas;
} monte_t;

monte_t *criar(int n_cartas);
int full(monte_t *baralho);
int empty(monte_t *baralho);
int push(monte_t *baralho, int x);
int printar(monte_t *baralho);
void destruir(monte_t *baralho);
int pull(monte_t *baralho, int *x);
int compras(monte_t *compra, monte_t *monte, int n_cartas);

