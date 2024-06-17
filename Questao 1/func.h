typedef struct pilha *Pilha;

Pilha cria_pilha();
int pilha_vazia(Pilha);
int pilha_push(Pilha *, int, int);
int pilha_pop(Pilha *, int *, int *);
