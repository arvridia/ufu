#include <stdio.h>

int 
main()
{
	float temperaturaFaren = 0;
	float temperaturaCelsius = 0;
	float estacaoClima = 0;
	printf("Digite a estação:\n");
	scanf ("%f",&estacaoClima);
	if (estacaoClima == 0)
	{
		return 0;
	}
	printf("Digite a temperatura:\n");
	scanf ("%f",&temperaturaFaren);
	while ( estacaoClima != 0 )
	{
		temperaturaCelsius = (temperaturaFaren - 32) * 5 / 9;
		printf ("Estação %.0f com temperatura de %.1f""°C\n", estacaoClima, temperaturaCelsius);
		printf ("Digite a estação:\n");
		scanf ("%f",&estacaoClima);
		if (estacaoClima == 0)
		{
			return 0;
		}
		printf("Digite a temperatura:\n");
		scanf ("%f",&temperaturaFaren);
	}
			
}
