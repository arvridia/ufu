#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADEx03.h"

void imprimir_fila(Fila F, int cont)
{
    Fila X = cria_fila();
    if(cont == 6)
        printf("\n\tFila de espera:\n");
    else
       printf("\n\tBox %d:\n", cont);
    if(fila_vazia(F) == 1)
        printf("\nVazio\n");
    else{
        while(fila_vazia(F) != 1)
        {
            func f;
            remove_ini(F,&f);
            printf("%s\n", f.placa);
            insere_fim(X,f); // passagem de elementos para fila X
        }
        while(fila_vazia(X) != 1)
        {
            func f;
            remove_ini(X,&f);
            insere_fim(F,f); // passagem de elementos para fila p
        }
    }
}

int entrada_carro(Fila P, int sina){
    func A;
    int cont1, cont2 = 0;
    do{
        printf("\nDigite a placa do carro: (As letras devem ser maiusculas)\n");
        fflush(stdin);
        gets(A.placa);
        fflush(stdin);
        int i = 0;
        while(A.placa[i] != '\0'){
            if(A.placa[i ]>= 'A' && A.placa[i] <= 'Z')
                cont1++;
            else{
                if(A.placa[i] >= '0' && A.placa[i] <= '9')
                    cont2++;
            }
            i++;
        }
        if(cont1 != 4 && cont2 != 3)
            printf("A placa inserida eh invalida! (Uma placa possui 7 algarismos, sendo 4 letras do alfabeto e 3 numeros de 0 a 9, sem hifen)\n");
    }while(cont1 != 4 && cont2 != 3);
    do{
        printf("\nDigite o tipo de servico: 'A' para avulso ou 'M' para mensalista\n");
        scanf("%c", &A.serv);
        fflush(stdin);
        if(A.serv != 'A' && A.serv != 'M')
            printf("Opcao invalida! Digite 'A' para servico avulso ou 'M' para mensalista\n");
    }while(A.serv != 'A' && A.serv != 'M');
    do{
        printf("\nInsira a hora de entrada do veiculo: (Somente as horas, como '1' da manha ou '14' da tarde...)\n");
        scanf("%d", &A.hora);
        fflush(stdin);
        if(A.hora < 0 || A.hora > 23)
            printf("Hora invalida! (As horas devem ser numeros entre 0 e 23)\n");
    }while(A.hora < 0 || A.hora > 23);
    do{
        printf("\nAgora, insira os minutos:\n");
        scanf("%d", &A.minutos);
        fflush(stdin);
        if(A.minutos < 0 || A.minutos > 59)
            printf("Minutos invalidos! (Os minutos devem ser numeros entre 0 e 59)\n ");
    }while(A.minutos < 0 || A.minutos > 59);
    printf("\nEntrada do veiculo...");
    insere_fim(P, A);
    printf("Com sucesso!\n\n");
    return 1;
}

int saida_carro(Fila P, func B, Fila E, int espera){
    func A;
    Fila Q = cria_fila();
    while(1){
        if(remove_ini(P, &A) == 0)
            break;
        if(strcmp(A.placa,B.placa) == 0){
            if(A.serv == 'A'){
                int hor, min, valor = 0;
                do{

                    printf("\nInforme a hora de saida do veiculo: ");
                    scanf("%d", &hor);
                    fflush(stdin);
                    if(hor < 0 || hor > 23)
                        printf("Hora invalida! (As horas devem ser numeros entre 0 e 23)\n");
                }while(hor < 0 || hor > 23);
                do{
                    printf("\nAgora, insira os minutos:\n");
                    scanf("%d", &min);
                    fflush(stdin);
                    if(min < 0 || min > 59)
                        printf("Minutos invalidos! (Os minutos devem ser numeros entre 0 e 59)\n ");
                }while(min < 0 || min > 59);
                printf("\nObrigado pela preferencia!!! Cobramos pelo servico do nosso estacionamento R$ 10,00 para a primeira hora e R$ 3,00 para cada hora adicional, com 15 minutos de tolerancia.\n");
                printf("Como seu carro esta estacionado desde a(as) %d:%d,", A.hora, A.minutos);
                printf(" e foi retirado a(as) %d:%d,", hor, min);
                hor = hor - A.hora;
                min = min - A.minutos;
                printf(" o valor a ser pago eh de R$");
                for(int i = 0; hor > 0; i++, hor--){
                    if(i == 0)
                        valor = valor + 10;
                    else
                        valor = valor + 3;
                }
                if(min > 15){
                    if(valor > 0)
                        valor = valor + 3;
                    else
                        valor = valor + 10;
                }
                printf("%d, obrigado!\n", valor);
            }
            printf("\nO carro foi retirado com sucesso!\n");
            if(espera > 0){
                func C;
                remove_ini(E,&C);
                insere_fim(P, C);
                printf("\nO carro foi retirado com sucesso! E o proximo da fila de espera foi alocado!\n");
                return 2;
            }
            return 1;
        }
        else
            insere_fim(Q, A);
    }
    while(fila_vazia(Q) != 1){
        remove_ini(Q, &A);
        insere_fim(P, A);
    }
    return 0;
}

int main()
{
    int sina1, sina2, sina3, sina4, sina5 = 0;
    int espera = 0;
    int swi = 0; // sinal contabiliza a qtde de reinicializacoes da fila
    Fila F,I,L,A,S,E;
    F = cria_fila();
    I = cria_fila();
    L = cria_fila();
    A = cria_fila();
    S = cria_fila();
    E = cria_fila();
    func C;
    do {
        do{
            // Obtem opcao do usuario
            printf("\n\n\tEstacionamento\n");
            printf("\nOpcoes:\n");
            printf("[1] Entrada de veiculos\n");
            printf("[2] Saida de veiculos\n");
            printf("[3] Visualizacao do cenario\n");
            printf("[4] Sair do sistema\n");
            printf("\nQual opcao deseja realizar? ");
            scanf("%d", &swi);
            setbuf(stdin, NULL);
            if (swi < 1 || swi > 4)
                printf("\nOpcao invalida...Somente existem essas opcoes:\n\n");

        } while (swi < 1 || swi > 4);
        if (swi != 1 && sina1+sina2+sina3+sina4+sina5 == 0 && swi != 4) {
            printf("\nAntes de realizar as outras operacoes, insira ao menos um veiculo.\n\n");
            continue;
        }
        switch (swi) {
            case 1: {
                if(sina1 <= sina2 && sina1 <= sina3 && sina1 <= sina4 && sina1 <= sina5 && sina1 < 10){
                    if(entrada_carro(F,sina1) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        sina1++;
                    break;
                }
                if(sina2 <= sina3 && sina2 <= sina4 && sina2 <= sina5 && sina2 < 10){
                    if(entrada_carro(I,sina2) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        sina2++;
                    break;
                }
                if(sina3 <= sina4 && sina3 <= sina5 && sina3 < 10){
                    if(entrada_carro(L,sina3) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        sina3++;
                    break;
                }
                if(sina4 <= sina5 && sina4 < 10){
                    if(entrada_carro(A,sina4) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        sina4++;
                    break;
                }
                if(sina5 < 10){
                    if(entrada_carro(S,sina5) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        sina5++;
                    break;
                }
                if(espera < 10){
                    printf("O estacionamento esta cheio no momento...Seu carro sera colocado na lista de espera na posicao %d de 10 e assim que vagas forem desocupadas e for a sua vez, seu carro podera ser estacionado", espera);
                    if(entrada_carro(E,espera) == -1)
                        printf("Houve um erro na alocacao do box...");
                    else
                        espera++;
                    break;
                }
                else
                    printf("O estacionamento esta lotado, volte mais tarde!");
                break;
            }
            case 2: {
                printf("\nInsira a placa do carro que deseja remover\n");
                gets(C.placa);
                fflush(stdin);
                if(saida_carro(F, C, E, espera) == 1){
                    printf("\n");
                    sina1--;
                    break;
                }
                if(saida_carro(F, C, E, espera) == 2){
                    printf("\n");
                    sina1--;
                    espera--;
                    break;
                }
                if(saida_carro(I, C,E,espera) == 1){
                    printf("\n");
                    sina2--;
                    break;
                }
                if(saida_carro(I, C, E, espera) == 2){
                    printf("\n");
                    sina2--;
                    espera--;
                    break;
                }
                if(saida_carro(L, C,E,espera) == 1){
                    printf("\n");
                    sina3--;
                    break;
                }
                if(saida_carro(L, C, E, espera) == 2){
                    printf("\n");
                    sina3--;
                    espera--;
                    break;
                }
                if(saida_carro(A, C,E,espera) == 1){
                    printf("\n");
                    sina4--;
                    break;
                }
                if(saida_carro(A, C, E, espera) == 2){
                    printf("\n");
                    sina4--;
                    espera--;
                    break;
                }
                if(saida_carro(S, C,E,espera) == 1){
                    printf("\n");
                    sina5--;
                    break;
                }
                if(saida_carro(S, C, E, espera) == 2){
                    printf("\n");
                    sina5--;
                    espera--;
                    break;
                }
                else
                    printf("\nEsta placa nao foi encontrada nos carros do estacionamento...(Uma placa possui 7 algarismos que podem somente ser letras maiusculas do alfabeto ou numeros de 0 a 9) \n");
                break;
            }
            case 3: {
                int cont = 1;
                printf("\nDisposicao dos veiculos no estacionamento:\n\n");
                imprimir_fila(F, cont);
                cont = 2;
                imprimir_fila(I, cont);
                cont = 3;
                imprimir_fila(L, cont);
                cont = 4;
                imprimir_fila(A, cont);
                cont = 5;
                imprimir_fila(S, cont);
                cont = 6;
                imprimir_fila(E, cont);
                break;
            }
        }
    }while (swi != 4);
    printf("\nEncerrando o programa...\n");
    return 0;
}

