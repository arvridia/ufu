typedef struct no *lista;

lista cria_lista();
int lista_vazia(lista lista1);
//int lista_cheia(lista lista1);
//int insere_ord(lista *lista1, int elem);
int insere_final(lista *lista1, int elem);
//int remove_ord(lista *lista1, int elem);
int remove_inicio(lista *lista1);
//int get_num(lista lista1, int pos, int *elem);
int obter_valor_elem(lista lista1, int pos, int *nani);
int apaga_lista(lista *lista1);
//int remove_pos(lista *lista1, int pos);
int tamanho(lista lista1);
int get_num(lista lista1, int pos);
