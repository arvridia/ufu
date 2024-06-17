typedef struct fila* Fila;

Fila cria_fila();

int insere_fim(Fila p, char A[]);

int remove_ini(Fila p, char *f[]);

int fila_vazia(Fila p);

int fila_cheia(Fila p);

void libera_fila (Fila *p);
