typedef struct aluno aluno;
typedef struct no *lista;

lista inicializar_lista();
int lista_vazia(lista lista1);
int lista_cheia(lista lista1);
int insere_elem(lista *lista1, unsigned int mat, char nome, float media, int faltas);
int remove_elem(lista *lista1, int elem);
int get_pos(lista lista1, int pos, unsigned int *nani, char *nome, float *media, int *faltas);
int apaga_lista(lista *lista1);
int remove_pos(lista *lista1, int pos);
int size_lista(lista *lista1);

