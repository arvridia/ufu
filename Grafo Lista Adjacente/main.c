
/*-- 10/mai/2003 --*/

#include<stdlib.h>
#include<stdio.h>

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

TipoApontador Aux;
int i;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo, Grafot;
TipoValorVertice NVertices;
short NArestas;
short FimListaAdj;

void FGVazio(TipoGrafo *Grafo)
{ short i, j;
  for (i = 0; i <= Grafo->NumVertices; i++)
    { for (j = 0; j <=Grafo->NumVertices; j++) Grafo->Mat[i][j] = 0; }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo)
{ Grafo->Mat[*V1][*V2] = *Peso; }

short ExisteAresta(TipoValorVertice Vertice1,
                   TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ return (Grafo->Mat[Vertice1][Vertice2] > 0); }

/* Operadores para obter a lista de adjacentes */
short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoApontador Aux = 0;  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia)
  { if (Grafo->Mat[*Vertice][Aux] > 0)
    ListaVazia = FALSE;
    else Aux++;
  }
  return (ListaVazia == TRUE);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice,
                               TipoGrafo *Grafo)
{ TipoValorVertice Result;
  TipoApontador Aux = 0;  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia)
    { if (Grafo->Mat[*Vertice][Aux] > 0)
      { Result = Aux; ListaVazia = FALSE; }
      else Aux++;
    }
  if (Aux == Grafo->NumVertices)
    printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
  return Result;
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
             TipoValorVertice *Adj, TipoPeso *Peso,
	     TipoApontador *Prox, short *FimListaAdj)
{ /* Retorna Adj apontado por Prox */
  *Adj = *Prox;  *Peso = Grafo->Mat[*Vertice][*Prox];  (*Prox)++;
  while (*Prox < Grafo->NumVertices &&
          Grafo->Mat[*Vertice][*Prox] == 0) (*Prox)++;
  if (*Prox == Grafo->NumVertices)
  *FimListaAdj = TRUE;
}

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2,
                  TipoPeso *Peso, TipoGrafo *Grafo)
{ if (Grafo->Mat[*V1][*V2] == 0)
  printf("Aresta nao existe\n");
  else { *Peso = Grafo->Mat[*V1][*V2]; Grafo->Mat[*V1][*V2] = 0; }
}

void LiberaGrafo(TipoGrafo *Grafo)
{  /* Nao faz nada no caso de matrizes de adjacencia */ }

void ImprimeGrafo(TipoGrafo *Grafo)
{ short i, j;
  printf("   ");
  for (i = 0; i <= Grafo->NumVertices - 1; i++) printf("%3d", i);
  printf("\n");
  for (i = 0; i <=  Grafo->NumVertices - 1; i++)
    { printf("%3d", i);
      for (j = 0; j <=Grafo->NumVertices - 1; j++)
        printf("%3d", Grafo->Mat[i][j]);
      printf("\n");
    }
}

void GrafoTransposto(TipoGrafo *Grafo, TipoGrafo *GrafoT)
{ TipoValorVertice v, Adj;
  TipoPeso Peso; TipoApontador Aux;
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
}  /* GrafoTransposto */

int main()
{  /*-- Programa principal --*/
  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/
  printf("Leitura do grafo\n");
  printf("No. vertices:"); scanf("%d%*[^\n]", &NVertices); getchar();
  printf("No. arestas:"); scanf("%hd%*[^\n]", &NArestas); getchar();
  Grafo.NumVertices = NVertices; Grafo.NumArestas=0; FGVazio(&Grafo);
  for (i = 0; i <= NArestas - 1; i++)
    { printf("Insere V1 -- V2 -- Peso:");
      scanf("%d%d%d%*[^\n]", &V1, &V2, &Peso);  getchar();
      Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &Peso, &Grafo);   /* 1 chamada g-direcionado    */
      /*InsereAresta(V2, V1, Peso, Grafo);*/   /* 2 chamadas g-naodirecionado*/
    }
  printf ("Imprimindo o grafo\n"); ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  GrafoTransposto(&Grafo, &Grafot);
  printf("Imprimindo o grafo transposto\n");
  ImprimeGrafo(&Grafot);
  scanf("%*[^\n]");
  getchar();
  printf("Incluindo uma nova aresta no grafo\n");
  printf("Insere V1 -- V2 -- Peso:");
  scanf("%d%d%d%*[^\n]", &V1, &V2, &Peso);
  getchar();
  if (ExisteAresta(V1, V2, &Grafo)) printf("Aresta ja existe\n");
  else
  { Grafo.NumArestas++;
    InsereAresta(&V1, &V2, &Peso, &Grafo);
    /*InsereAresta(V2, V1, Peso, Grafo);*/  /* grafo nao direcionado */
  }
  printf("Imprimindo grafo novamente\n");
  ImprimeGrafo(&Grafo);
  scanf("%*[^\n]");
  getchar();
  printf("Lista adjacentes de: ");
  scanf("%d", &V1);
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
  scanf("%d%d%*[^\n]", &V1, &V2);
  getchar();
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
  scanf("%d%d%*[^\n]", &V1, &V2);
  getchar();
  if (ExisteAresta(V1, V2, &Grafo))
  printf(" Sim\n");
  else
  printf(" Nao\n");
  LiberaGrafo(&Grafo);
  ImprimeGrafo(&Grafo);
  return 0;
}



/* End. */
