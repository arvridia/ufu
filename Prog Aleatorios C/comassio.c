#include <stdio.h>

int main()
{
    float a[20][3], soma;
    int i, j, nl;
    
    printf("Introduza o número de alunos da classe: ");
    scanf("%d", &nl);
    printf("Digite a nota dos alunos nas 3 avaliações\n");
    for(i=0;i<nl;i++){
        for(j=0;j<3;j++){
            printf("A[%d,%d]=", i+1, j+1);
            scanf("%f", &a[i][j]);
            
        }
    } 
    soma=0;
    for(i=0;i<nl;i++){
        for(j=0;j<3;j++){
            soma+=a[i][j];
        }
    }
	printf ("%.2f", soma);
    for(i=0;i<nl;i++){
        printf("O aluno %d tirou", i+1);
        for(j=0;j<3;j++){
            printf("%5.2f",a[i][j]);
            
        }
        printf(" nas avaliações e sua média nas avaliações: %5.2f\n", soma/3);
        printf("\n");
        
    }
    return 0;
}