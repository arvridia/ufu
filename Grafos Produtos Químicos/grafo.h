typedef struct grafo * Grafo;

Grafo criaGrafo();
struct noVert *inserirVertice(struct noVert *ini, char name[]);
void inserindoArco(Grafo g, char v1[], char v2[]);
struct noAdj *inserirAdjacencia(char vdest[], struct noAdj *l);
int verticePresente(Grafo g, char v[]);
void imprimirListaAdj(Grafo g);
void definirCor(Grafo g, char vert[]);
void coloracao_gulosa(Grafo g);
int not_colored_neighbours(Grafo g,char vert[]);
int canColorWith(Grafo g, char vert[], int cor);
int setColor(Grafo g, int vert, int *colorCount, int totalColors);
void backtracking(Grafo g);
