#include<stdlib.h>
#include<stdio.h>
#include "grafo.h"
/*
void imprime_G(TipoGrafo *Grafo)
{
    int i;
    TipoApontador Aux;
    for(i = 0; i < Grafo->NumVertices; i++)
    {
        printf("Vertice %2d: ", i);
        if(!Vazia(Grafo->Adj[i]))
        {
            Aux = Grafo->Adj[i].Primeiro->Prox;
            while(Aux != NULL)
            {
                printf("%3d(%d)", Aux->Item.Vertice, Aux->Item.peso);
                Aux = Aux->Prox;
            }
        }
    }
    printf("\n");
}
*/
/*-- 10/mai/2003 --*/



#include <stdio.h>
#include <stdlib.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define FALSE           0
#define TRUE            1

typedef int TipoValorVertice;
typedef int TipoPeso;
typedef struct TipoItem {
  TipoValorVertice Vertice;
  TipoPeso Peso;
} TipoItem;
typedef struct TipoCelula *TipoApontador;
struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;
typedef struct TipoLista {
  TipoApontador Primeiro, Ultimo;
} TipoLista;
typedef struct TipoGrafo {
  TipoLista Adj[MAXNUMVERTICES + 1];
  TipoValorVertice NumVertices;
  short NumArestas;
} TipoGrafo;

TipoApontador Aux;
long i; short FimListaAdj;
int  NArestas;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo, GrafoT;
TipoValorVertice NVertices;

/*--Entram aqui os operadores do Programa 2.4--*/
void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista)
{ /*-- Insere depois do ultimo item da lista --*/
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}

/*-- Fim operadores do Programa 2.4 --*/
void FGVazio(TipoGrafo *Grafo)
{ long i;
  for (i = 0; i < Grafo->NumVertices; i++) FLVazia(&Grafo->Adj[i]);
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo)
{ TipoItem x;
  x.Vertice = *V2;
  x.Peso = *Peso;
  Insere(&x, &Grafo->Adj[*V1]);
}

short ExisteAresta(TipoValorVertice Vertice1,
                   TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ TipoApontador Aux;
  short EncontrouAresta = FALSE;
  Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE)
    { if (Vertice2 == Aux->Item.Vertice) EncontrouAresta = TRUE;
      Aux = Aux->Prox;
    }
  return EncontrouAresta;
}

/* Operadores para obter a lista de adjacentes */
short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro ==
          Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice,
                               TipoGrafo *Grafo)
{ return (Grafo->Adj[*Vertice].Primeiro->Prox); }

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
             TipoValorVertice *Adj, TipoPeso *Peso,
             TipoApontador *Prox, short *FimListaAdj)
{ /* Retorna Adj e Peso do Item apontado por Prox */
  *Adj = (*Prox)->Item.Vertice;
  *Peso = (*Prox)->Item.Peso;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL) *FimListaAdj = TRUE;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*--Obs.: item a ser retirado e o seguinte ao apontado por p--*/
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p->Prox == NULL)
  { printf("Erro: Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->Prox;
  *Item = q->Item;
  p->Prox = q->Prox;
  if (p->Prox == NULL) Lista->Ultimo = p;
  free(q);
}

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo)
{ TipoApontador AuxAnterior, Aux;
  short EncontrouAresta = FALSE;
  TipoItem x;
  AuxAnterior = Grafo->Adj[*V1].Primeiro;
  Aux = Grafo->Adj[*V1].Primeiro->Prox;
  while (Aux != NULL && EncontrouAresta == FALSE)
    { if (*V2 == Aux->Item.Vertice)
      { Retira(AuxAnterior, &Grafo->Adj[*V1], &x);
        Grafo->NumArestas--;
        EncontrouAresta = TRUE;
      }
      AuxAnterior = Aux;
      Aux = Aux->Prox;
    }
}

void LiberaGrafo(TipoGrafo *Grafo)
{ TipoApontador AuxAnterior, Aux;
  for (i = 0; i < Grafo->NumVertices; i++)
    { Aux = Grafo->Adj[i].Primeiro->Prox;
      free(Grafo->Adj[i].Primeiro);   /*Libera celula cabeca*/
      Grafo->Adj[i].Primeiro=NULL;
      while (Aux != NULL)
        { AuxAnterior = Aux;
          Aux = Aux->Prox;
          free(AuxAnterior);
        }
    }
  Grafo->NumVertices = 0;
}

void ImprimeGrafo(TipoGrafo *Grafo)
{ int i;
  TipoApontador Aux;
  for (i = 0; i < Grafo->NumVertices; i++)
    { printf("Vertice%2d:", i);
      if (!Vazia(Grafo->Adj[i]))
      { Aux = Grafo->Adj[i].Primeiro->Prox;
        while (Aux != NULL)
          { printf("%3d (%d)", Aux->Item.Vertice, Aux->Item.Peso);
            Aux = Aux->Prox;
          }
      }
      putchar('\n');
    }
}

void ImprimeLista(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro->Prox;
  while (Aux != NULL)
    { printf("%3d (%12d)", Aux->Item.Vertice, Aux->Item.Peso);
      Aux = Aux->Prox;
    }
}

void GrafoTransposto(TipoGrafo *Grafo, TipoGrafo *GrafoT)
{ TipoValorVertice v, Adj;
  TipoPeso Peso;
  TipoApontador Aux;
  FGVazio(GrafoT);
  GrafoT->NumVertices = Grafo->NumVertices;
  GrafoT->NumArestas = Grafo->NumArestas;
  for (v = 0; v <= Grafo->NumVertices - 1; v++)
  { if (!ListaAdjVazia(&v, Grafo))
    { Aux = PrimeiroListaAdj(&v, Grafo);
      FimListaAdj = FALSE;
      while (!FimListaAdj)
      { ProxAdj(&v, Grafo, &Adj, &Peso, &Aux, &FimListaAdj);
        InsereAresta(&Adj, &v, &Peso, GrafoT);
      }
    }
  }
}

int main(int argc, char *argv[])
{ /*-- Programa principal --*/
  int TEMP;
  int TEMP1;

  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/

  printf("No. vertices:");
  scanf("%d%*[^\n]", &TEMP);
  getchar();
  NVertices = TEMP;
  printf("No. arestas:");
  scanf("%d%*[^\n]", &NArestas);
  getchar();
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);

  for (i = 0; i < NArestas; i++)
    { printf("Insere V1 -- V2 -- Peso:");
      scanf("%d%d%d%*[^\n]", &TEMP, &TEMP1, &Peso);
      getchar();
      V1 = TEMP;
      V2 = TEMP1;
      Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &Peso, &Grafo);   /* 1 chamada g-direcionado    */
      /*InsereAresta(V2, V1, Peso, Grafo);*/
      /* 2 chamadas g-naodirecionado*/
    }
  ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  printf("Grafo transposto:\n");
  GrafoTransposto(&Grafo, &GrafoT);
  ImprimeGrafo(&GrafoT);
  scanf("%*[^\n]");
  getchar();
  printf("Insere V1 -- V2 -- Peso:");
  scanf("%d%d%d%*[^\n]", &V1, &V2, &Peso);
  if (ExisteAresta(V1, V2, &Grafo))
  printf("Aresta ja existe\n");
  else
    { Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &Peso, &Grafo);
      /*InsereAresta(V2, V1, Peso, Grafo);*/
    }
  ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  printf("Lista adjacentes de: ");
  scanf("%d*[^\n]", &TEMP);
  V1 = TEMP;
  if (!ListaAdjVazia(&V1, &Grafo))
  { Aux = PrimeiroListaAdj(&V1, &Grafo);
    FimListaAdj = FALSE;
    while (!FimListaAdj)
      { ProxAdj(&V1, &Grafo, &Adj, &Peso, &Aux, &FimListaAdj);
        printf("%2d (%d)", Adj, Peso);
      }
    putchar('\n');
    scanf("%*[^\n]");
    getchar();
  }
  printf("Retira aresta V1 -- V2:");
  scanf ("%d %d", &V1, &V2);
  if (ExisteAresta(V1, V2, &Grafo))
  { Grafo.NumArestas--;
    RetiraAresta(&V1, &V2, &Peso, &Grafo);
    /*RetiraAresta(V2, V1, Peso, Grafo);*/
  }
  else printf("Aresta nao existe\n");
  ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  printf("Existe aresta V1 -- V2:");
  /* scanf("%d%d%*[^\n]", &TEMP, &TEMP1); */
  scanf("%d*[^\n]", &TEMP);
  scanf("%d*[^\n]", &TEMP1);
  getchar();
  V1 = TEMP;
  V2 = TEMP1;
  if (ExisteAresta(V1, V2, &Grafo)) printf(" Sim\n");
  else printf(" Nao\n");
  LiberaGrafo(&Grafo);   /* Imprime sujeira normalmente */
  ImprimeGrafo(&Grafo);
  return 0;
}


/*short ExisteAresta_fst_chegada(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo){
    TipoApontador Aux;
    short EncontrouAresta = -1;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && EncontrouAresta == -1){
        if (Vertice2 == Aux->Item.Vertice)
            EncontrouAresta = Aux->Item.Peso[1][0];
        Aux = Aux->Prox;
    }
    return EncontrouAresta;
}
MAX=2 MAX2=24
Peso[MAX][MAX2]

0 1 0
0 1 1
0 1 2

short ExisteAresta_lst_saida(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo, int j){
    TipoApontador Aux;
    short EncontrouAresta = -1;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && EncontrouAresta == -1){
        if (Vertice2 == Aux->Item.Vertice)
            EncontrouAresta = Aux->Item.Peso[0][j];
        Aux = Aux->Prox;
    }
    return EncontrouAresta;
}

short ExisteAresta_curta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo, int j){
    TipoApontador Aux;
    float aux[] = {-1,0}
    int count = 0;
    int med = 0;
    int med1 = 0;
    int i = 0;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while (Aux != NULL && aux[0] == -1){
        if (Vertice2 == Aux->Item.Vertice){
            while(count < j){
                if(count == 0)
                    med = Aux->Item.Peso[i+1][count] - Aux->Item.Peso[i][count];
                else{
                    if((Aux->Item.Peso[i+1][count] - Aux->Item.Peso[i][count]) < med){
                        med = Aux->Item.Peso[i+1][count] - Aux->Item.Peso[i][count];
                        med1 = count;
                    }
                }
                i = 0;
                count++;
            }
            aux[0] = Aux->Item.Peso[0][med1];
            aux[1] = Aux->Item.Peso[1][med1];
        }
        Aux = Aux->Prox;
    }
    return aux;
}
*/
