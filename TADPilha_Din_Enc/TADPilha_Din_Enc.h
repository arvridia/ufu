typedef struct no *Pilha;

Pilha cria_pilha();

int pilha_vazia(Pilha p);

int pilha_push(Pilha *p, char elem[]);

int pilha_pop(Pilha *p, char *elem[]);

int get_topo(Pilha *p, char *nome[]);

void esvazia_pilha(Pilha *p);

void libera_pilha(Pilha *p);

int tamanho_pilha(Pilha p);

