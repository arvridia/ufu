/*

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

//--Entram aqui os operadores do Programa 2.4--
void FLVazia(TipoLista *Lista)
{ Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

short Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem *x, TipoLista *Lista)
{ //-- Insere depois do ultimo item da lista --
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = *x;
  Lista->Ultimo->Prox = NULL;
}

//-- Fim operadores do Programa 2.4 --
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

// Operadores para obter a lista de adjacentes
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
{ // Retorna Adj e Peso do Item apontado por Prox
  *Adj = (*Prox)->Item.Vertice;
  *Peso = (*Prox)->Item.Peso;
  *Prox = (*Prox)->Prox;
  if (*Prox == NULL) *FimListaAdj = TRUE;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ //--Obs.: item a ser retirado e o seguinte ao apontado por p--
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
      free(Grafo->Adj[i].Primeiro);   //Libera celula cabeca
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
{ //-- Programa principal --
  int TEMP;
  int TEMP1;

  // -- NumVertices: definido antes da leitura das arestas --
  // -- NumArestas: inicializado com zero e incrementado a --
  // -- cada chamada de InsereAresta                       --

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
      InsereAresta(&V1, &V2, &Peso, &Grafo);   // 1 chamada g-direcionado
      //InsereAresta(V2, V1, Peso, Grafo);
      // 2 chamadas g-naodirecionado
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
      //InsereAresta(V2, V1, Peso, Grafo);
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
    //RetiraAresta(V2, V1, Peso, Grafo);
  }
  else printf("Aresta nao existe\n");
  ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  printf("Existe aresta V1 -- V2:");
  // scanf("%d%d%*[^\n]", &TEMP, &TEMP1);
  scanf("%d*[^\n]", &TEMP);
  scanf("%d*[^\n]", &TEMP1);
  getchar();
  V1 = TEMP;
  V2 = TEMP1;
  if (ExisteAresta(V1, V2, &Grafo)) printf(" Sim\n");
  else printf(" Nao\n");
  LiberaGrafo(&Grafo);   // Imprime sujeira normalmente
  ImprimeGrafo(&Grafo);
  return 0;
}
*/























/*
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   4500
#define TRUE  1
#define FALSE 0

typedef int TipoValorVertice;
typedef int  TipoPeso;
typedef struct TipoGrafo {
  TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
  int NumVertices;
  int NumArestas;
} TipoGrafo;
typedef int  TipoApontador;

short FimListaAdj;

void FGVazio(TipoGrafo *Grafo);

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo);

short ExisteAresta(TipoValorVertice Vertice1,TipoValorVertice Vertice2, TipoGrafo *Grafo);

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo);

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice,
                               TipoGrafo *Grafo);

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
             TipoValorVertice *Adj, TipoPeso *Peso,
	     TipoApontador *Prox, short *FimListaAdj);

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo);
void LiberaGrafo(TipoGrafo *Grafo);
void ImprimeGrafo(TipoGrafo *Grafo);
void GrafoTransposto(TipoGrafo *Grafo, TipoGrafo *GrafoT);







#define MAX 10
#define MAX2 450
#define I 2
#define J 25

typedef int TipoValorVertice;
typedef float Peso;
typedef int TipoChave;

typedef struct TipoItem
{
    TipoValorVertice Vertice ;
    Peso peso;
    TipoChave Chave;

} TipoItem;

typedef struct TipoCelula *TipoApontador;

struct TipoCelula
{
    TipoItem Item;
    TipoApontador Prox;

}TipoCelula;

typedef struct TipoLista
{
    TipoApontador Primeiro;
    TipoApontador Ultimo;

}TipoLista;

typedef struct TipoGrafo
{
    TipoLista Adj[MAX + 1];
    TipoValorVertice NumVertices;
    short NumArestas;

}TipoGrafo;

//////////////////////////////////
void FGVazio(TipoGrafo *Grafo);

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, Peso *peso, TipoGrafo *Grafo);

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo);

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo);

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo);

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, TipoValorVertice *Adj, Peso *peso, TipoApontador *Prox, short *FimListaAdj);

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2, Peso *peso, TipoGrafo *Grafo);

void LiberaGrafo(TipoGrafo *Grafo);




void FLVazia(TipoLista *Lista);

int Vazia(TipoLista Lista);

void Insere(TipoItem x, TipoLista *Lista);

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item);

void Imprime(TipoLista Lista);
*/
