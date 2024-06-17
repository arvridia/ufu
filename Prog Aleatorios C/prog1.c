// Amanda Rodrigues Leandro 12311EMC029
#include <stdio.h>
#include <stdlib.h>

int main()
{
    float largura, altura, area, perimetro;

    printf("digite a largura e a altura:");

    scanf("%f %f", &largura, &altura);

    area= largura*altura;
    perimetro= (2*altura)+(2*largura);

    printf("o perimetro eh %.2f e a area eh %.2f.\n",perimetro,area);

    return 0;
}
