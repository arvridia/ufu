typedef struct no *lista;

lista cria_lista();
void inicializa_lista(lista lista1);
int lista_vazia(lista lista1);
int lista_cheia(lista lista1);
int insere_ord(lista *lista1, char elem);
int remove_ord(lista *lista1, char elem);
int get_carac(lista lista1, int pos, char elem);
char get_pos(lista lista1, int pos);
void apaga_lista(lista *p);
