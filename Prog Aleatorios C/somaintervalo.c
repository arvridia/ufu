#include <stdio.h>

int 
main()
{
	int a = 0;
	int b = 0;
	int s = 0;
	printf ("digite dois números\n");
	scanf ("%d %d", &a, &b);
	while (a <=b)
	{
		s = s + a; // s += a;
		a = a + 1; // a++;
	}
	printf ("%d\n", s);
	return 0;
}