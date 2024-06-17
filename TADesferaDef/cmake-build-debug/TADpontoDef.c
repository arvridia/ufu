//
// Created by Arthur on 31/03/2021.
//

#include "TADpontoDef.h"
#include <stdlib.h>
#include <math.h>


struct ponto
{
    float x;
    float y;
    float z;
};

Ponto *Cria_pto()
{
    Ponto *P = malloc(sizeof(Ponto));
    P->x = 0;
    P->y = 0;
    P->z = 0;
    return P;
}

void Libera_pto(Ponto *P)
{
    free(P)
    P = NULL;
}

float Distancia_pto(Ponto *p1, Ponto *p2)
{
    float distancia = sqrt(pow(p1->x - p2->x,2) + pow(p1->y - p2->y,2) + pow(p1->z - p2->z,2));
    return distancia;
}
