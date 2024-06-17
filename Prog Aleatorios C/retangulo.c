/* Este programa coleta as coordenadas de dois pontos, calcula e 
retorna a área do retângulo resultante.
Criado por Arthur Resende Santos, 12011BCC020 */
#include <stdio.h>
struct ponto{
	int x, y;
};
struct retangulo {
	struct ponto inicio, fim;
};
int 
main()
{
	int area;
	struct retangulo r;
	printf("Digite a coordenada x do primeiro ponto:\n");
	scanf("%d", &r.inicio.x);
	printf("Digite a coordenada y do primeiro ponto:\n");
	scanf("%d", &r.inicio.y);
	printf("Digite a coordenada x do segundo ponto:\n");
	scanf("%d", &r.fim.x);
	printf("Digite a coordenada y do segundo ponto:\n");
	scanf("%d", &r.fim.y);
	area = (r.inicio.y - r.fim.y) * (r.inicio.x - r.fim.x);
	printf("A área resultante é %d"".\n", area);
	return 0;
}


