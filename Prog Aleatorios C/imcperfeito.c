/* Este programa foi criado por Arthur Resende Santos, em 26/08/2020
Ele transforma os dados de peso e altura inseridos pelo usuário em seu IMC */

#include <stdio.h>
#include <wchar.h>
#include <string.h>

const unsigned int T = 50; // ou isso ou define T 50 ali em cima ou coloca ali em baixo, no lugar do T, mas n é aconselhavel

int
main() /* essa função é a que detém o corpo do programa, ela agrupa o cerne. Fora dela há somente complementações caso necessárias */
{
	unsigned char nome[T]; /* nome do usuário */ 
	float altura = 0; /* essa variável detém a altura do usuário */
	float peso = 0; /* essa variável detém o peso do usuário */
	float imc = 0; /* esse é o resultado do IMC */
	
	printf ("Digite seu nome:\n");
	scanf ("%s", nome);
	
	printf ("Digite sua altura:\n");
	scanf ("%f", &altura);
	
	printf ("Digite seu peso:\n");
	scanf ("%f", &peso);
	
	imc = peso / (altura * altura);
	printf ("%s"", seu IMC é %.2f"", o que significa que você está", nome, imc);
	
	if (imc < 18,5)
		printf (" abaixo do peso.\n");
	else if (imc < 25)
		printf (" com peso normal.\n");
	else if (imc < 30)
		printf (" com sobrepeso.\n");
	else if (imc < 35)
		printf (" com obesidade grau1.\n");
	else if (imc < 40)
		printf (" com obesidade grau2.\n");
	else 
		printf (" com obesidade grau3.\n");
}
		