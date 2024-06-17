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
  	fscanf(abrir, "%[^0-9] %f %f", z.n, &z.p, &z.a); /* para ler cada linha do arquivo selecionado */
  	fscanf(abrir, " ");	/* para evitar que o programa leia o fim do arquivo, que não tem nada */
  	IMC = imc(z.p, z.a);
  	showP(z);
  	showIMC(IMC);
	
  }
  printf("\n");
  fclose(abrir);			/*para fechar o arquivo*/
  abrir = NULL;
  
  abrir = fopen(arquivo, "r"); /*abrindo o arquivo agora para a leitura do menor imc*/
  while ( !feof(abrir) )
  {
	fscanf(abrir, "%[^0-9] %f %f %[^0-9] %f. %f", p1.n, &p1.p, &p1.a, p2.n, &p2.p, &p2.a);
	pRetorno = mIMC(p1, p2);
	
  }
  printf("Dentre todas as pessoas apresentadas no arquivo, a que apresenta o menor imc é: %s.\n", pRetorno.n);
  fclose(abrir);			/*para fechar o arquivo*/
  abrir = NULL;				
  return 0;
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
	float imc1 = 0.0;
	float imc2 = 0.0;
	imc1 = p1.p/(p1.a*p1.a);
	imc2 = p2.p/(p2.a*p2.a);
	if (pRetorno.p/(pRetorno.a*pRetorno.a) > imc1 && pRetorno.p/(pRetorno.a*pRetorno.a) > imc2)
		return pRetorno;
	return (imc1 > imc2)? p1:p2;
}

	
