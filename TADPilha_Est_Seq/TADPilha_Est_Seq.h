struct funcionario{
    long int mat;
    char nome[30];
    char setor;
    float salario;
};

typedef struct funcionario func;
typedef struct pilha* Pilha;

Pilha cria_pilha();

int pilha_push (Pilha p, func A);

int pilha_pop (Pilha p, func *f);

int pilha_vazia (Pilha p);

int pilha_cheia(Pilha p);

int get_topo(Pilha p, func *f);

void libera_pilha (Pilha *p);

int tamanho (Pilha p);

int esvazia_pilha(Pilha p);
