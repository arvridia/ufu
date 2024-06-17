struct carro{
    char placa[8];
    char serv;
    int hora;
    int minutos;
};

typedef struct carro func;
typedef struct fila* Fila;

Fila cria_fila();

int insere_fim(Fila p, func A);

int remove_ini(Fila p, func *f);

int fila_vazia(Fila p);

int fila_cheia(Fila p);

void libera_fila (Fila *p);

