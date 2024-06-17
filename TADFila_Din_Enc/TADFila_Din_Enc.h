typedef struct fila * Fila;

struct bebidas{
    char nome[20];
    int volume;
    float preco;
};
typedef struct bebidas beb;

Fila cria_fila();

int fila_vazia(Fila f);

int insere_fim(Fila f, beb elem);

int remove_ini(Fila f, beb *elem);

void apaga_fila(Fila f);

int esvazia_fila(Fila f);

