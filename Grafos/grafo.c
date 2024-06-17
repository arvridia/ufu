#include "grafo.h"
#include "pilha.h"
#include "fila.h"
#include <stdlib.h>
#include <stdio.h>


struct noVert* inserirVertice(struct noVert *ini, int num){
  struct noVert* novoVertice;
  novoVertice = (struct noVert*) malloc (sizeof(struct noVert));
  novoVertice->vert = num;
  novoVertice->prox = ini;
  novoVertice->ladj = NULL;
  return novoVertice;
}

void inserirNovoVertice(Grafo G, int nv){
   G->vertices = inserirVertice(G->vertices,nv);
   G->NumVert++;
}


Grafo criarGrafo(int nVert) {
   int v;
   Grafo G;
   G = (Grafo) malloc(sizeof (Grafo));
   G->NumArco = 0;
   G->NumVert = 0;
   G->vertices = NULL;
   for (v = nVert-1; v >= 0; v--) {
      G->vertices = inserirVertice(G->vertices,v);
      G->NumVert++;
   }
   return G;
}


struct noAdj* inserirAdjacencia(int vdest, struct noAdj *l){
   struct noAdj *novo = (struct noAdj*) malloc(sizeof (struct noAdj));
   novo->vert = vdest;
   novo->prox = l;
   return novo;
}


void inserirArco(Grafo G, int v1, int v2) {
   struct noVert *v;
   struct noAdj *z;
   if (G == NULL) return;
   for (v = G->vertices; v != NULL; v = v->prox)
      if (v->vert == v1) { // achou o vértice para inserir a adjacência
         for(z = v->ladj; z!= NULL; z = z->prox)
             if (z->vert == v2) return;  // o arco já existe, retornar!
         v->ladj = inserirAdjacencia(v2,v->ladj);
         G->NumArco++;
      }
}

void imprimirListaAdj(Grafo G) {
   struct noVert *nv;
   struct noAdj *na;
   if (G == NULL) return;
   printf("\n\nLista de Adjacencias:");
   for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      printf("\nVertice %d:",nv->vert);
      for (na = nv->ladj; na != NULL; na = na->prox)
          printf("(%d)",na->vert);
   }
}


void imprimirListaAdjRec(struct noVert *nv) {
   struct noAdj *na;
   if (nv == NULL) return;
   printf("\nVertice %d:",nv->vert);
   for (na = nv->ladj; na != NULL; na = na->prox)
          printf("(%d)",na->vert);
   imprimirListaAdjRec(nv->prox);
}


int grauVertice(Grafo G, int v) {
   struct noVert *nv;
   struct noAdj *na;
   int cont = 0;
   if (G == NULL) return 0;
   for (nv = G->vertices; nv!=NULL; nv = nv->prox) {
      if(v == nv->vert){
         for (na = nv->ladj; na != NULL; na = na->prox)
             cont = cont + 1;  // grau de saída
      }
      else{
         for (na = nv->ladj; na != NULL; na = na->prox)
             if(v == na->vert)
               cont = cont + 1; // grau de entrada
      }
   }
   return cont;
}




int FoiVisitado(int vert, int *vet, int tam){
  int i;
  for (i = 0; i<=tam; i++){
    if(vet[i] == vert)
       return 1;
  }
  return 0;
}

int imprimeVisita(int *vet, int tam){
  int i;
  printf("\nOrdem da visita: ");
  for (i = 0; i<=tam; i++){
     printf("(%d) ", vet[i]);
  }
  return 0;
}


void BuscaEmLargura(Grafo G, int v){
   struct noVert *nv;
   struct noAdj *na;
   int *visitados;
   TipoFila *fila;
   int i=0, cont = 0, vt;
   //Iniciar o vetor de visitados com -1 para todos os vértices

  visitados = (int *) malloc (G->NumVert * sizeof (int));
   for (i=0; i<G->NumVert; i++){
      visitados[i] = -1;
   }

   // anotar como visitado o vértice de origem (busca)
   visitados[cont]=v;

   //Iniciar a fila e inserir o vértice de origem
   fila = (TipoFila *) malloc (sizeof(TipoFila));
   IniciaFila(fila);
   Enfileira(v,fila);

   while(!Vazia(fila)){
       vt = Desenfileira(fila);
       for (nv = G->vertices; nv!=NULL; nv = nv->prox)
            if(vt == nv->vert)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitado(na->vert,visitados,cont)==0){
                           Enfileira(na->vert,fila);
                           cont++;
                           visitados[cont]=na->vert;
                      }
   }
   imprimeVisita(visitados,cont);
   free(fila);
}


void BuscaEmProfundidade (Grafo G, int v) {
   struct noVert *nv;
   struct noAdj *na;
   int *visitados;
   TipoPilha *pilha;
   int i=0, cont = 0, vt;

   //Iniciar o vetor de visitados com -1 para todos os vértices
   visitados = (int *) malloc (G->NumVert * sizeof (int));
   for (i=0; i<G->NumVert; i++){
      visitados[i] = -1;
   }
   //Iniciar a fila e inserir o vértice de origem
   pilha = (TipoPilha *) malloc (sizeof(TipoPilha));
   IniciaPilha(pilha);
   Empilha(v,pilha);

   while(!VaziaPilha(pilha)){
       vt = Desempilha(pilha);
       if (FoiVisitado(vt,visitados,cont)==0){
          visitados[cont]=vt;
          cont++;
          for (nv = G->vertices; nv!=NULL; nv = nv->prox)
              if(vt == nv->vert)
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitado(na->vert,visitados,cont)==0){
                           Empilha(na->vert,pilha);
                      }
       }
   }
   imprimeVisita(visitados,cont-1);
   free(pilha);
}



int MarcaVisitaTempo(int vt, int pos, char tipo, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if(vet[i].vert == vt){
         if (tipo == 'D'){
             vet[i].tempoDescoberta = pos;
             return 1;
         }
         else{
             if (vet[i].tempoFinalizacao == -1){
                 vet[i].tempoFinalizacao = pos;
                 return 1;
             }
             else return 0;
         }
    }
  }
  return 0;
}

int FoiVisitadoTempo(int vert, struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
    if((vet[i].vert == vert) && (vet[i].tempoDescoberta != -1))
       return 1;
  }
  return 0;
}

int imprimeVisitaTempo(struct visitaTempo *vet, int tam){
  int i;
  for (i = 0; i<tam; i++){
     printf("\n(%d) Descoberta: %d, Finalizacao: %d",
         vet[i].vert, vet[i].tempoDescoberta, vet[i].tempoFinalizacao);
  }
  return 0;
}


void PercursoProfundidadeTempo (Grafo G, int v) {
   struct noVert *nv;
   struct noAdj *na;
   struct visitaTempo *visitados;
   TipoPilha *pilha;
   int tam=0, cont = 0, vt, finaliza, r;

   //Iniciar o vetor de visitados com -1 para todos os vértices
   visitados = (struct visitaTempo *) malloc (G->NumVert * sizeof (struct visitaTempo));
   for (nv=G->vertices; nv!=NULL; nv=nv->prox){
      visitados[tam].vert = nv->vert;
      visitados[tam].tempoDescoberta = -1;
      visitados[tam].tempoFinalizacao = -1;
      tam++;
   }
   //Iniciar a fila e inserir o vértice de origem
   pilha = (TipoPilha *) malloc (sizeof(TipoPilha));
   IniciaPilha(pilha);
   Empilha(v,pilha);

   while(!VaziaPilha(pilha)){
       vt = Topo(pilha);
       if (FoiVisitadoTempo(vt,visitados,tam)==0){
          MarcaVisitaTempo(vt, cont++, 'D', visitados,tam);
          //cont++;
          for (nv = G->vertices; nv!=NULL; nv = nv->prox)
              if(vt == nv->vert){
                 finaliza = 1;
                 for (na = nv->ladj; na != NULL; na = na->prox)
                      if (FoiVisitadoTempo(na->vert,visitados,tam)==0){
                           Empilha(na->vert,pilha);
                           finaliza = 0;
                      }
                 if (finaliza == 1){
                     r = MarcaVisitaTempo(vt,cont,'F',visitados,tam);
                     if (r == 1) cont++;
                     vt = Desempilha(pilha);
                 }
              }
       }
       else {
           r = MarcaVisitaTempo(vt,cont,'F',visitados,tam);
           if (r == 1) cont++;
           vt = Desempilha(pilha);
       }
   }
   imprimeVisitaTempo(visitados,tam);
   free(pilha);
}
