#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a = 0;
    int fat = 1;
    scanf("%d", &a);
    while(a > 1){
        fat = fat*a;
        a = a-1;
    }
    printf("%d", fat);
    return 0;
}
