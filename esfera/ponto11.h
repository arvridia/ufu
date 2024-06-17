//
// Created by Arthur on 31/03/2021.
//



struct ponto
{
    float x;
    float y;
    float z;
};
typedef struct ponto Ponto;

Ponto *Cria_pto();
void Libera_pto(Ponto *P);
float Distancia_pto(Ponto *p1, Ponto *p2);