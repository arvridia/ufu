/* Este programa captura um carácter digitado pelo usuário 
e apresenta seu respectivo número da tabela ASCII continuamente, até que "FIM" seja digitado.
Criado por Arthur Resende Santos, 2020 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int const X = 100; 
int
main()
{

	unsigned char senha[X]; // carácter que o usuário digitará
	printf("Digite uma senha:\n");
	
	int a = -1; // variável para uso de comparação para saída do laço
	int j = 0;
	int b = 0;
	b = strlen (senha);
	for (;a != 0;)
	{// caso o usuário digite "FIM", a será 0 e o programa parará
		scanf ("%s", senha);
		a = strcmp(senha,'FIM'); // compara se o conteúdo digitado pelo usuário é equivalente a palavra "FIM"
		if (a == 0)
			return 0;
		do
		{	
			printf("%d ", senha[j]);
			j++;
		}
		while (j < b);
	}
}