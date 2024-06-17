#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
	float A[10][10];
	float T[10][10];
	int n, k, i, j, z, x, p, b = 0;
	printf ("Digite a ordem para a matriz quadrada: (Digite o número de linhas, aperte 'enter', digite o número de colunas e aperte 'enter' novamente\n");
	scanf ("%d", &n);
	scanf ("%d", &k);
	if ( n < 0 || k < 0 )
	{
		fprintf (stderr, "O número digitado é muito pequeno para criar uma matriz quadrada!\n");
		return 0;
	}
	if ( n > 10 || k > 10 )
	{
		fprintf (stderr, "O número digitado é grande demais!\n");
		return 0;
	}
	b = n;
	n = n * n;
	
	for (;z < n;i++, j = 0)
	{
		for (;j < b;j++, z++)
		{
			srand(time())
			A[i][j] = rand() % 11);
			printf("%.0f", A[i][j];
		}
		printf("\n");
	}
	x = b - 1;
	printf ("A matriz transposta é:\n");
	for (;p < b; p++, x--)
		printf ("%.0f", A[j][i]);
	printf ("\n");
}