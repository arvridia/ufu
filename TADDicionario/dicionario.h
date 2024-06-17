typedef struct NO* ArvAVL;
typedef struct no* lista;
typedef struct vocabulo VOCAB;

ArvAVL* cria_ArvAVL();

void libera_ArvAVL(ArvAVL *raiz);

int insere_ArvAVL(ArvAVL *raiz, int data);

int estaVazia_ArvAVL(ArvAVL *raiz);

int altura_ArvAVL(ArvAVL *raiz);

int totalNO_ArvAVL(ArvAVL *raiz);

int consulta_ArvAVL(ArvAVL *raiz, int valor);

void emOrdem_ArvAVL(ArvAVL *raiz);

int remove_ArvAVL(ArvAVL *raiz, int valor);

int remove_Menores_ArvAVL(ArvAVL *raiz, int valor);

int iguais_ArvAVL(ArvAVL *r1, ArvAVL *r2);

int remover(lista lista1, char palavra[40]);
