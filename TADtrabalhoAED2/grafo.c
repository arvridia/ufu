/*
#include<stdlib.h>
#include<stdio.h>
#include "grafo.h"

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

// Operadores para obter a lista de adjacentes
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
{ // Retorna Adj apontado por Prox
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
{  // Nao faz nada no caso de matrizes de adjacencia  }

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

































// Entram aqui os operadores FLVazia, Vazia, Insere, Retira e Imprime
// do TAD Lista de Apontadores do Programa 3.4
/*
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void FGVazio(TipoGrafo *Grafo)
{
    long i;
    for(i = 0; i < Grafo->NumVertices; i++)
        FLVazia(&Grafo->Adj[i]);
}

///////////////////////////////////////////
void FLVazia(TipoLista *Lista)
{
    Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista)
{
    return(Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Item = x;
    Lista->Ultimo->Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{
// O item a ser rertirado e o seguinte apontado por p
    TipoApontador q;
    if(Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {
        printf("Erro: Lista vazia ou posicao nao existe\n");
        return;
    }

    q = p->Prox;
    *Item = q->Item;
    p->Prox = q->Prox;

    if(p->Prox == NULL)
        Lista->Ultimo = p;

    free(p);
}

void Imprime(TipoLista Lista)
{
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox;
    while(Aux != NULL)
    {
        printf("%d \n", Aux->Item.Chave);
        Aux = Aux->Prox;
    }
}
////////////////////////////////////////////////////
void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2, Peso *peso, TipoGrafo *Grafo)
{
    TipoItem x;
    x.Vertice = *V2;
    x.peso = *peso;
    Insere(x, &Grafo->Adj[*V1]);
}

short ExisteAresta(TipoValorVertice Vertice1, TipoValorVertice Vertice2, TipoGrafo *Grafo)
{
    TipoApontador Aux;
    short EncontrouAresta = 0;
    Aux = Grafo->Adj[Vertice1].Primeiro->Prox;
    while(Aux != NULL && EncontrouAresta == 0)
    {
        if(Vertice2 == Aux->Item.Vertice)
            EncontrouAresta = 1;

        Aux = Aux->Prox;
    }
    return EncontrouAresta;
}

// Operadores para obter a lista de adjacentes

short ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{
    return (Grafo->Adj[*Vertice].Primeiro == Grafo->Adj[*Vertice].Ultimo);
}

TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{
    return (Grafo->Adj[*Vertice].Primeiro->Prox);
}

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo, TipoValorVertice *Adj, Peso *peso, TipoApontador *Prox, short *FimListaAdj)
{
 // retorna ADJ e Peso do item apontado por PROX
    *Adj = (*Prox)->Item.Vertice;
    *peso = (*Prox)->Item.peso;
    *Prox = (*Prox)->Prox;
    if(*Prox == NULL)
        *FimListaAdj = 1;
}

void RetiraAresta(TipoValorVertice *V1, TipoValorVertice *V2, Peso *peso, TipoGrafo *Grafo)
{
    TipoApontador AuxAnterior, Aux;
    int EncontrouAresta = 0;
    TipoItem x;
    AuxAnterior = Grafo->Adj[*V1].Primeiro;
    Aux = Grafo->Adj[*V1].Primeiro->Prox;
    while(Aux != NULL && EncontrouAresta == 0)
    {
        if(*V2 == Aux->Item.Vertice)
        {
            Retira(AuxAnterior, &Grafo->Adj[*V1], &x);
            Grafo->NumArestas--;
            EncontrouAresta = 1;
        }
        AuxAnterior = Aux;
        Aux = Aux->Prox;
    }
}

void LiberaGrafo(TipoGrafo *Grafo)
{
    TipoApontador AuxAnterior, Aux;
    for(int i = 0; i < Grafo->NumVertices; i++)
    {
        Aux = Grafo->Adj[i].Primeiro->Prox;
        free(Grafo->Adj[i].Primeiro); // Libera celula cabeça
        Grafo->Adj[i].Primeiro = NULL;
        while(Aux != NULL)
        {
            AuxAnterior = Aux;
            Aux = Aux->Prox;
            free(AuxAnterior);
        }
    }
    Grafo->NumVertices = 0;
}

*/




