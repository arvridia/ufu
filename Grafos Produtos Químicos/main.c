#include <stdio.h>
#include "grafo.h"

int main(void) {
  Grafo g;
  g = criaGrafo();

  inserindoArco(g,"Acetileno","Cloro");
  inserindoArco(g,"Acetileno","Bromo");
  inserindoArco(g,"Cloro","Amonia");
  inserindoArco(g,"Amonia","Mercurio");
  inserindoArco(g,"Bromo","Cloro");
  inserindoArco(g,"Acetileno","Metano");

  imprimirListaAdj(g);
  //coloracao_gulosa(g);
  backtracking(g);
  return 0;
}
