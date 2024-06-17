#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main(void) {
  int rgrau;
  Grafo g;
  g = criarGrafo(6);
  inserirArco(g,0,5);
  inserirArco(g,0,2);
  inserirArco(g,0,1);
  inserirArco(g,0,5);
  inserirArco(g,1,4);
  inserirArco(g,1,3);
  inserirArco(g,2,5);
  inserirArco(g,5,2);
  inserirArco(g,5,1);

  imprimirListaAdj(g);
  rgrau = grauVertice(g,0);
  printf("\nBusca em Largura");
  BuscaEmLargura(g, 0);
  printf("\nBusca em Profundidade");
  BuscaEmProfundidade (g,0);
  printf("\n");
  PercursoProfundidadeTempo (g,0);




}
