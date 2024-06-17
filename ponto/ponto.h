struct ponto
{
    float x;
    float y;
    float z;
};

typedef struct ponto ponto;
ponto *generate_ponto();
void free_ponto(ponto *p);
float modulo(ponto *ponto1, ponto *ponto2);
