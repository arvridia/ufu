typedef struct fila * Fila;

Fila cria_fila();

int fila_vazia(Fila f);

int insere_ord(Fila f, int elem);

int remove_ini(Fila f, int *elem);

void apaga_fila(Fila f);

int esvazia_fila(Fila f);

