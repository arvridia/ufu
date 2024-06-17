#include <stdio.h>
#define MAXN 50

int
main ()
{
	unsigned char n[MAXN]; // nome de uma pessoa
	printf ("digite seu nome\n");
	scanf ("%s", n);
	printf ("\t voce digitou %s\n", n);
	return 0;
}