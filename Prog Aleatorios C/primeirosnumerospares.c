#include <stdio.h>

int
main()
{
	float a = 0;
	printf ("Digite a quantidade de números pares que você deseja\n")
	scanf ("%f", &a);
	while (a <= 0)
	{
		printf ("Por favor, digite um número maior que zero");
		scanf ("%f", &a);
	}
	float i = 0;
	while (a > 0)
	{
		printf ("%.0f\n", i);
		i = i + 2;
		a--;
	}
	return 0;
}
		
		
		