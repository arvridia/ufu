struct aluno{
    int mat;
    char nome[50];
    int faltas;
    float media;
};

typedef struct aluno func;
typedef struct fila* Fila;

Fila cria_fila();

int insere_fim(Fila p, func A);

int remove_ini(Fila p, func *f);

int fila_vazia(Fila p);

int fila_cheia(Fila p);

void libera_fila (Fila *p);
