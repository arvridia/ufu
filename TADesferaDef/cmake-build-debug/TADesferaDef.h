//
// Created by Arthur on 31/03/2021.
//

typedef struct esfera Esfera;

cria_esfera(Ponto *p1, Ponto *p2);
libera_esfera(Esfera *p);
float raio(Ponto *p1, Ponto *p2);
float area(float raio);
float volume(float raio);
