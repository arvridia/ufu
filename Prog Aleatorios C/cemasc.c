/* este programa captura uma senha digitada pelo usuário
 e apresenta ela criptografada conforme a tabela ASCII
 Criado por Arthur Resende Santos, 2020 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 
 int
 main ()
 {
	char senha[100];
	scanf ("%s", senha);
	
	int z = 0;
	z = strlen (senha);
	
	char i;
	
	int j = 0;
	
	while (j < z) 
	{
		
		char i = senha[j];
		printf ("%c", i);
		j++;
	}
	
 }