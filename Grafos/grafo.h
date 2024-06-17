struct grafo {
   int NumVert;
   int NumArco;
   struct noVert *vertices;
};
typedef struct grafo *Grafo;

struct noVert {
   int vert;
   struct noVert *prox;
   struct noAdj *ladj;
};

struct noAdj {
   int vert;
   struct noAdj *prox;
};

struct visitaTempo{
  int vert;
  int tempoDescoberta;
  int tempoFinalizacao;
};


/* A lista de adjac�ncia de um v�rtice v � composta por n�s. Cada n� da  corresponde a um arco e cont�m um vizinho w de v e o endere�o do n� seguinte da lista. */

Grafo criarGrafo(int nVert);
void inserirArco(Grafo G, int v1, int v2);
void inserirNovoVertice(Grafo G, int nv);
int grauVertice(Grafo G, int v);
void imprimirListaAdj(Grafo G);
void imprimirListaAdjRec(struct noVert *nv);

void BuscaEmLargura(Grafo G, int v);
void BuscaEmProfundidade (Grafo G, int v);
void PercursoProfundidadeTempo (Grafo G, int v);
