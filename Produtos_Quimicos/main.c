#include <stdlib.h>
#include <string.h>

struct grafo{
  int numVert;
  int numArco;
  int numCor;
  struct noVert *vertices;
};

typedef struct grafo * Grafo;

struct noVert{
  char vertice[50];
  int cor;
  struct noVert *prox;
  struct noAdj *ladj;
};

struct noAdj{
  char vertice[50];
  struct noAdj *prox;
};

Grafo criaGrafo(){
  Grafo g;
  g = (Grafo) malloc(sizeof(struct grafo));
  g->numArco = 0;
  g->numVert = 0;
  g->numCor = 0;
  return g;
}

struct noVert *inserirVertice(struct noVert *ini, char name[]){
  struct noVert *novoVertice;
  novoVertice = (struct noVert *) malloc(sizeof(struct noVert));
  strcpy(novoVertice->vertice, name);
  novoVertice->cor = -1;
  novoVertice->prox = ini;
  novoVertice->ladj = NULL;
  return novoVertice;
}

void inserindoArco(Grafo g, char v1[], char v2[]){
  struct noVert *v;
  struct noAdj *z;

  if(g == NULL)
    return;

  if(verticePresente(g,v1) == 0){
    g->vertices = inserirVertice(g->vertices,v1);
    g->numVert++;
  }

  if(verticePresente(g,v2) == 0){
    g->vertices = inserirVertice(g->vertices,v2);
    g->numVert++;
  }

  for(v = g->vertices; v != NULL; v = v->prox){
    if(strcmp(v->vertice, v1) == 0){
      v->ladj = inserirAdjacencia(v2,v->ladj);
      g->numArco++;
    }
    else if(strcmp(v->vertice, v2) == 0){
      v->ladj = inserirAdjacencia(v1,v->ladj);
    }
  }
}

struct noAdj *inserirAdjacencia(char vdest[], struct noAdj *l){
  struct noAdj *novo = (struct noAdj *) malloc(sizeof(struct noAdj));
  strcpy(novo->vertice,vdest);
  novo->prox = l;
  return novo;
}

int verticePresente(Grafo g, char v[]){
  struct noVert *nv;
  for(nv = g->vertices; nv != NULL; nv = nv->prox){
    if(strcmp(nv->vertice, v) == 0)
      return 1;
  }

  return 0;
}

void imprimirListaAdj(Grafo g){
  struct noVert *nv;
  struct noAdj *na;

  if(g == NULL)
    return;

  printf("\n\nProdutos quimicos e restricoes");
  for(nv = g->vertices; nv != NULL; nv = nv->prox){
    printf("\n%s:", nv->vertice);
    for(na = nv->ladj; na != NULL; na = na->prox){
      printf(" %s", na->vertice);
    }
  }
  printf("\n");
}

void definirCor(Grafo g, char vert[]){
  struct noVert *elem;
  struct noVert *aux;
  struct noAdj *adj;

  int cor[50];
  int i;

  for(i = 0; i < 50; i++){
    cor[i] = 1;
  }

  for(elem = g->vertices; elem != NULL; elem = elem->prox){
    if(strcmp(elem->vertice,vert) == 0)
      break;
  }

  if(elem == NULL)
    return;

  for(adj = elem->ladj; adj != NULL; adj = adj->prox){
    for(aux = g->vertices; aux != NULL; aux = aux->prox)
      if(strcmp(aux->vertice,adj->vertice) == 0)
        break;

    if(aux->cor < 0)
      continue;

    cor[aux->cor] = 0;
  }

  for(i = 0; i < 50; i++){
    if(cor[i] != 0){
      elem->cor = i;
      break;
    }
  }

  if(elem->cor+1 > g->numCor)
    g->numCor = elem->cor+1;
}

void coloracao_gulosa(Grafo g){
  struct noVert *aux;

  for(aux = g->vertices; aux != NULL; aux = aux->prox){
    definirCor(g,aux->vertice);
  }

  printf("\nSera necessario %d containers", g->numCor);
  for(aux = g->vertices; aux != NULL; aux = aux->prox){
    printf("\n%s: container %d",aux->vertice,aux->cor);
  }

  printf("\n");
}

int not_colored_neighbours(Grafo g,char vert[]){
  struct noVert *aux;
  struct noVert *vertice;
  struct noAdj *adj;
  int i;

  for(vertice = g->vertices; vertice != NULL; vertice = vertice->prox){
    if(strcmp(vertice->vertice,vert) == 0)
      break;
  }

  for(adj = vertice->ladj; adj != NULL; adj = adj->prox){
    i = 0;
    for(aux = g->vertices; aux != NULL; aux = aux->prox){
      if(strcmp(aux->vertice,adj->vertice) == 0){
        if(aux->cor == -1)
          return i;
        break;
      }
      i++;
    }
  }

  return -1;
}

int canColorWith(Grafo g, char vert[], int cor){
  struct noVert *aux;
  struct noVert *vertice;
  struct noAdj *adj;

  for(vertice = g->vertices; vertice != NULL; vertice = vertice->prox){
    if(strcmp(vertice->vertice,vert) == 0)
      break;
  }

  for(adj = vertice->ladj; adj != NULL; adj = adj->prox){
    for(aux = g->vertices; aux != NULL; aux = aux->prox){
      if(strcmp(aux->vertice,adj->vertice) == 0){
        if(aux->cor == cor)
          return 0;
      }
    }
  }

  return 1;
}

int setColor(Grafo g, int vert, int *colorCount, int totalColors){
  int i, uncolored;
  struct noVert *vertice;

  i = 0;
  for(vertice = g->vertices; vertice != NULL; vertice = vertice->prox){
    if(i == vert)
      break;
    i++;
  }

  for(i = 0; i < colorCount; i++){
    if(canColorWith(g, vertice->vertice, i) == 0)
      continue;

    vertice->cor = i;
    *colorCount++;

    if(*colorCount == g->numVert+1){
      if(g->numCor < vertice->cor+1)
        g->numCor = vertice->cor+1;
      return 1;
    }

    while((uncolored = not_colored_neighbours(g, vertice->vertice)) != -1){
      if(setColor(g, uncolored, colorCount,totalColors) == 1){
        if(g->numCor < vertice->cor+1)
          g->numCor = vertice->cor+1;
      }
      else
        break;
    }
    if(uncolored == -1){
      if(g->numCor < vertice->cor+1)
        g->numCor = vertice->cor+1;
      return 1;
    }
  }

  vertice->cor = -1;
  *colorCount--;
  return 0;
}

void backtracking(Grafo g){
  struct noVert *aux;
  struct noAdj *adj;
  int i;
  int qtdCor = 0;
  int maxCor = 0;

  for(aux = g->vertices; aux != NULL; aux = aux->prox){
    i = 0;
    for(adj = aux->ladj; adj != NULL; adj = adj->prox){
      i++;
    }
    if(maxCor<i)
      maxCor = i;
  }

  setColor(g, 0, &qtdCor, maxCor);

  printf("\nSera necessario %d containers", g->numCor);
  for(aux = g->vertices; aux != NULL; aux = aux->prox){
    printf("\n%s: container %d",aux->vertice,aux->cor);
  }

  printf("\n");
}

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
