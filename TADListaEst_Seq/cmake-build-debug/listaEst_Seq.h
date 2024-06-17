typedef struct lista *Lista;

Lista cria_lista();
int lista_vazia(Lista);
int lista_cheia(Lista);
int insere_elem(Lista, int);
int remove_elem(Lista, int);
void libera_lista(Lista *);
void inicializa_lista(Lista);
int get_elem(Lista, int, int *);