#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long resto_da_mult(long long a, long long b, long long mod)
{
    long int x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

long int modulo(long int base, long int expoente, long int mod)
{
    long int a = 1;
    long int b = base;
    while (expoente > 0)
    {
        if (expoente % 2 == 1)
            a = (a * b) % mod;
        b = (b * b) % mod;
        expoente = expoente / 2;
    }
    return a % mod;
}


int criterio(long int y,int mod)
{

    mod = 5;
    int i;
    long int x;
    if (y < 2)
    {
        return 0;
    }
    if (y != 2 && y % 2==0)
    {
        return 0;
    }
    x = y - 1;
    while (x % 2 == 0)
    {
        x /= 2;
    }
    for (i = 0; i < mod; i++)
    {
        long int a = 0;
        long int med;
        a = rand() % (y - 1) + 1, med = x;
        long int mod = modulo(a, med, y);
        while (med != y - 1 && mod != 1 && mod != y - 1)
        {
            mod = resto_da_mult(mod, mod, y);
            med *= 2;
        }
        if (mod != y - 1 && med % 2 == 0)
        {
            return 0;
        }
    }
    return 1;
}


int main()
{
    char esc;
    do{

        printf("\n\t-Criterio de Rabin-Miller-\n");
        int mod = 0;
        long int numero;
        printf("\nDigite um numero para determinar, a partir do criterio de Rabin-Miller, se ele eh primo ou nao: \n");
        scanf("%ld", &numero);
        if (criterio(numero, mod) == 1)
            printf("\nO numero %ld eh primo!\n", numero);
        else
            printf("\nO numero %ld nao eh primo!\n", numero);
        do{
            printf("\nDeseja repetir a operacao? Digite 's' caso sim e 'n' caso nao: \n");
            fflush(stdin);
            scanf("%c", &esc);
            if(esc != 's' && esc!= 'n')
                printf("\nEscolha invalida! Digite 's' para sim ou 'n' para nao\n");
        }while(esc != 's' && esc!= 'n');
    }while(esc != 'n');
    return 0;
}
