/* 	
	Este programa abre um arquivo com dados de nome, peso e altura,
	calcula o respectivo imc, o apresenta, e, por fim, 
	determina quem possue o menor imc dentre as pessoas do arquivo.
	Criado por Arthur Resende Santos, em 2020.
 */

#include<stdio.h>
#include<ctype.h>
#define MAX 100

struct pessoa
{
	char n[MAX]; //nome
	float p; //peso
    float a; //altura
};
typedef struct pessoa Pessoa;




float imc (float p, float a);

void showIMC (float imc);

void showP (Pessoa z);
Pessoa getP(FILE *arquivo);

int contador = 0;
Pessoa mIMC(Pessoa p1, Pessoa p2);
Pessoa pRetorno;

     


int
main ()
{
  FILE *abrir = NULL;
  char arquivo[MAX];  
  
  float IMC = 0;
  
  Pessoa z;
  Pessoa p1;
  Pessoa p2;

  
 
  
  printf("digite o nome do arquivo a ser lido: ");
  
  scanf("%s", arquivo); /* informe do nome do arquivo para leitura*/
  abrir = fopen(arquivo,"r");
  
  
  if (abrir == NULL)        /* para possíveis erros no encontro do arquivo selecionado*/
  {
    fprintf(stderr,"Houve um erro ao abrir o arquivo %s!\n",arquivo);
    return 1;
  }
  
  

  while ( !feof(abrir) )
  {
  	while (contador <= 2)
		z = getP(abrir);
  	IMC = imc(z.p, z.a);
  	showP(z);
  	showIMC(IMC);
	contador = 0;
  }
  printf("\n");
  fclose(abrir);			/*para fechar o arquivo*/
  abrir = NULL;
  
  abrir = fopen(arquivo, "r"); /*abrindo o arquivo agora para a leitura do menor imc*/
  while ( !feof(abrir) )
  {
	fscanf(abrir, "%[^0-9] %f %f %[^0-9] %f %f", p1.n, &p1.p, &p1.a, p2.n, &p2.p, &p2.a);
	pRetorno = mIMC(p1, p2);
	
  }
  printf("Dentre todas as pessoas apresentadas no arquivo, a que apresenta o menor imc é: %s.\n", pRetorno.n);
  fclose(abrir);			/*para fechar o arquivo*/
  abrir = NULL;				
  return 0;
}
Pessoa
getP(FILE *abrir)
{
	Pessoa z;
	if (contador == 0)
	{
		fscanf(abrir, "%[^0-9]", z.n);
		contador++;
	}
	else if (contador == 1)
	{
		fscanf(abrir, "%f", &z.p);
		contador++;
	}
	else if (contador == 2)
	{
		fscanf(abrir, "%f", &z.a);
		contador++;
	}
	fscanf(abrir, " ");
	return z;
}
float
imc(float p, float a)
{
   float result = p / (a * a);
   return result;
}

void
showIMC(float imc)
{
	printf("Esta pessoa tem imc igual a: %.2f\n", imc);

	if(imc < 18.5)
		printf("Esta pessoa está abaixo do peso\n");
	else if(imc < 25)
	    printf("Esta pessoa está com o peso normal\n");
	else if(imc < 30)
	    printf("Esta pessoa está com sobrepeso\n");
	else if(imc < 35)
		printf("Esta pessoa está com obesidade de grau um\n");
	else if(imc < 40)
		printf("Esta pessoa está com obesidade de grau dois\n");
	else
	    printf("Esta pessoa está com obesidade de grau três\n");
}
void
showP(Pessoa z)
{
   printf ("\nNome: %s\n",z.n);
   printf ("Peso de: %.1f\n",z.p);
   printf ("Altura de: %.2f\n",z.a);
}
Pessoa 
mIMC(Pessoa p1, Pessoa p2)
{
	if (pRetorno.p/(pRetorno.a*pRetorno.a) < p1.p/(p1.a*p1.a) && pRetorno.p/(pRetorno.a*pRetorno.a) < p2.p/(p2.a*p2.a))
		return pRetorno;
	else if (p1.p/(p1.a*p1.a) < p2.p/(p2.a*p2.a))
		return p1;
	else 
		return p2;
}
