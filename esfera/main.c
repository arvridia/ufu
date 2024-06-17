#include <stdio.h>
#include "ponto11.h"
#include "esfera11.h"

int main()
{
    Ponto *p1 = Cria_pto();
    Ponto *p2 = Cria_pto();

    float raio1 = 0;
    float e_area = 0;
    float e_volume = 0;

    printf("Digite as coordenadas para o primeiro ponto: ");
    scanf("%f %f %f", &p1->x, &p1->y, &p1->z);
    printf("\nDigite as coordenadas para o segundo ponto: ");
    scanf("%f %f %f", &p2->x, &p2->y, &p2->z);

    Esfera *p3 = cria_esfera(p1, p2);
    raio1 = raio(p1, p2);
    e_area = area(raio1);
    e_volume = volume(raio1);

    printf("\nA esfera foi criada com sucesso, seu raio eh: %f, sua area eh %f e seu volume %f\n", raio, e_area, e_volume);

    libera_esfera(p3);
    Libera_pto(p1);
    Libera_pto(p2);

    return 0;
}
