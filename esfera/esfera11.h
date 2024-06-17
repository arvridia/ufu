//
// Created by Arthur on 31/03/2021.
//
#include "ponto11.h"
struct esfera{
    Ponto p1;
    Ponto p2;
};
typedef struct esfera Esfera;

Esfera *cria_esfera(Ponto *p1, Ponto *p2);
void libera_esfera(Esfera *p);
float raio(Ponto *p1, Ponto *p2);
float area(float raio);
float volume(float raio);