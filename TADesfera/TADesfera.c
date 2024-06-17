//
// Created by Arthur on 31/03/2021.
//

#include "TADesfera.h"
#include "TADponto.h"
#include <stdlib.h>




Esfera *cria_esfera(Ponto *p1, Ponto *p2){
    //cria uma esfera e inicia seus valores
    //struct com ponto A e ponto B?
    Esfera *p = (Esfera *) malloc (sizeof(Esfera));
    p->p1 = 0;
    p->p2 = 0;
    return p;
}

libera_esfera(Esfera *p){
    //elimina uma esfera da memória
    free(p);
    p = NULL;
}

float raio(Ponto *p1, Ponto *p2){
    //determina o cumprimento do raio da esfera
    float raio = Distancia_pto(p1, p2);
    return raio;
}

float area(float raio){
    //determina a area da esfera
    // 4.pi.r^2
    float resultado = 0;
    resultado = 4*3.1415*(raio*raio);
    return resultado;
}

float volume(float raio){
    //determina o volume da esfera
    // 4.pi.(r^3)/3
    float resultado = 0;
    resultado = 4*3.1415*((raio*raio*raio)/3);
    return resultado;
}