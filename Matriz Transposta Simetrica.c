/**************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

***************************/

#include <stdio.h>
#include <string.h>
#define MAX1 10
#define MAX2 100

int 
main()
{
    int a[MAX1][MAX1];                  //representa a matriz
    int at[MAX1][MAX1];                 //representa a matriz transposta
    int v[MAX2];                        //vetor que armazena os elementos da matriz
    int vt[MAX2];  						//vetor que armazena os elementos da matriz transposta
    int i = 0;                          //contador de laço 1
    int j = 0;                          //contador de laço 2
    int k = 0;                          //variavel auxilizar para laço
    int x = 0;							
	int m = 0;                          //indice 1 da matriz
    int n = 0;                          //indice 2 da matriz
    int soma = 0;  						//variavel para ajudar na identificacao de simetria da matriz
    printf("Digite m: \n");             //captura valor para m
    scanf("%d", &m);

    printf("Digite n: \n");             //captura valor para n
    scanf("%d", &n);
    
    if ( m < 2 || m > 10 || n < 2 || n > 10)        //condição para m e n
        printf("Valores invalidos para m e n\n");
    else                                            //condição correta
    {
        for ( i = 0; i < m; i++)
        {
            for ( j = 0; j < n; j++)
            {
                printf("Digite um elemento para a posicao %d %d da matriz: ", i + 1, j + 1);    //usuário digita os valores para a matriz
                scanf("%d", &a[i][j]);
                v[k] = a[i][j];                       //vetor recebe o elemento da matriz
                k++;
            }
        }
        for ( i = 0; i < m; i++)                    //elaboração da matriz transposta
        {
            for ( j = 0; j < n; j++)
            {
                at[j][i]=a[i][j];
                vt[k]=at[i][j];                     //vetor recebe o elemento da matriz transposta
                x++;
            }
        }
        printf("\nA matriz é: \n");                 
        
        for ( i = 0; i < m; i++)                    //impressão da matriz
        {
            for ( j = 0; j < n; j++)
                printf("%d ", a[i][j]);    
            printf("\n"); 
        }
        
        printf("\nA matriz transposta é: \n");      //impressão da matriz transposta
        
        for ( i = 0; i < n; i++)
        {
            for ( j = 0; j < m; j++)
                printf("%d ", at[i][j]);    
            printf("\n");
            
        }
        
        while ( i < 0)
        {
            if (v[i] == vt[i])
            {
                soma++;
                i++;
            }
            else
                i++;
        }
        if ( soma == ( m * n))
            printf("A matriz é simétrica\n");
        else
            printf("A matriz é assimétrica\n");
    }

    return 0;
}