#include "ponto.h"
#include <stdio.h>

int main()
{
    ponto *ponto1 = generate_ponto();
    ponto *ponto2 = generate_ponto();
    ponto *ponto3 = generate_ponto();

    printf("\nInforme as coordenadas do ponto 1:\n");
    scanf("%f %f %f", &ponto1->x, &ponto1->y, &ponto1->z);
    printf("\nInforme as coordenadas do ponto 2:\n");
    scanf("%f %f %f", &ponto2->x, &ponto2->y, &ponto2->z);
    printf("\nInforme as coordenadas do ponto 3:\n");
    scanf("%f %f %f", &ponto3->x, &ponto3->y, &ponto3->z);

    printf("O modulo(distancia) eh igual a = %f",modulo(ponto1, ponto2));

    free_ponto(ponto1);
    free_ponto(ponto2);
    free_ponto(ponto3);

    return 0;

}
