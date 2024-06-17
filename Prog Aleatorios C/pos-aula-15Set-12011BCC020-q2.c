/*  Criado por Autran Macedo e modificado por Arthur Resende Santos 12011BCC020, 2020
	Este programa carrega o valor "v" a todas as posições de um array e o apresenta
*/
#include <stdio.h>
#define MAX 100
int A1[MAX]; /*declarada global para que possa ser usada em todas as funções*/
void
loadA(int t, int a[], int v)
{
	int i;
	for (i = 0; i < t; i++) /*laço para preencher com o valor "v" todas as posições do array*/
		A1[i] = v;
}
void
showA(int t, int a[])
{
	int i;
	for (i = 0; i < t; i++) /*laço para apresentação de todos os números armazenados no array*/
		printf("%d", A1[i]);
}
int
main()
{
	loadA (MAX, A1, 0);
	showA (MAX, A1);
	printf("\n");
	return 0;
}
