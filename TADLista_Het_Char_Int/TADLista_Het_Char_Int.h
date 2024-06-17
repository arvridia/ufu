typedef struct no * lista;

lista cria_lista();

int lista_vazia(lista lst);

int insere_elem (lista *lst, int num, char elem, int type);

int remove_elem (lista *lst, int num, char elem, int type);

int get_elem(lista lst, int pos, int *num, char *elem, int *type);

void limpa_lista(lista *lst);

