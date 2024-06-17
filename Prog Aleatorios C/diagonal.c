#include <stdio.h>

int
main()
{
	float m[10][10];
	int n = 0;
	int i = 0;
	int j = 0;
	int z = 0;
	int x = 0;
	int p = 0;
	int b = 0;
	printf ("Digite a ordem para a matriz quadrada:\n");
	scanf ("%d", &n);
	if ( n < 2 )
	{
		printf ("O número digitado é muito pequeno para criar uma matriz quadrada\n");
		return 0;
	}
	if ( n > 10 )
	{
		printf ("O número digitado é grande demais\n");
		return 0;
	}
	b = n;
	n = n * n;
	printf ("Agora, digite %d números para preencher a matriz: (Digite um número, aperte 'Enter' e digite o próximo)\n", n);
	scanf ("%f", &m[i][j]);
	j++;
	z++;
	for (;z < n;i++, j = 0)
		for (;j < b;j++, z++)
			scanf ("%f", &m[i][j]);
	x = b - 1;
	printf ("A diagonal secundária é:\n");
	for (;p < b; p++, x--)
		printf ("%.0f", m[p][x]);
	printf ("\n");
}
