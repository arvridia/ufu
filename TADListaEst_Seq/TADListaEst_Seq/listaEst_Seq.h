typedef struct lista *lista;

lista cria_lista();
void inicializa_lista(lista lista1);
int lista_vazia(lista lista1);
int lista_cheia(lista lista1);
int insere_frase(lista lista1, char *frase);
int remove_frase(lista lista1, char *frase);
int get_frase(lista lista1, int pos, char *frase);
char get_pos(lista lista1, int pos);
void apaga_lista(lista *p);

