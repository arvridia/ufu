#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdint.h>

#define SUCESSO            0
#define FALHA             -1
#define PONTEIRO_INVALIDO -2
#define SEM_MEMORIA       -3

struct no_lista {
  int64_t elemento;
  struct no_lista *proximo;
};

typedef struct no_lista No_lista;

struct lista {
  int32_t nro_elementos;
  struct no_lista *cabeca;
};

typedef struct lista Lista;

Lista *criar_lista();
int tamanho_lista(Lista *lista);
int existe_elemento(Lista *lista, int64_t elemento);
int encontrar_elemento(Lista *lista, int pos, int64_t *elemento);
int encontrar_posicao(Lista *lista, int *pos, int64_t elemento);
int inserir_lista(Lista *lista, int pos, int64_t elemento);
int atualizar_lista(Lista *lista, int pos, int64_t elemento);
int remover_lista(Lista *lista, int pos);
int imprimir_lista(Lista *lista);
int esvaziar_lista(Lista *lista);
int destruir_lista(Lista *lista);

#endif // LISTA_H_INCLUDED

