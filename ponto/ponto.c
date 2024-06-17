#include <math.h>
#include "ponto.h"
#include <stdlib.h>

ponto *generate_ponto()
{
    ponto *P = malloc(sizeof(ponto));
    P->x = 0;
    P->y = 0;
    P->z = 0;
    return P;
}

void free_ponto(ponto *p)
{
    free(p);
}

float modulo(ponto *p1, ponto *p2)
{
    float distancia = sqrt(pow(p1->x - p2->x,2) + pow(p1->y - p2->y,2) + pow(p1->z - p2->z,2));
    return distancia;
}
