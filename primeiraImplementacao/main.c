#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "registro.h"
#include "size.h"

struct timespec { long tv_sec; long tv_nsec; };    //header part
int clock_gettime(int a, struct timespec *spec)      //C-file part
{
  __int64 wintime;
  GetSystemTimeAsFileTime((FILETIME*)&wintime);
  wintime      -= 116444736000000000;           // 1jan1601 to 1jan1970
  spec->tv_sec  = wintime / 10000000;           // seconds
  spec->tv_nsec = wintime % 10000000 *100;      // nano-seconds
  return 0;
}

// Convert bytes to GB
#define DIV 1073741824

#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "registro.h"
#include "size.h"
#endif


int time_seq_sweep(FILE *arq, int rnum_by_page, nseq_t *valid_registers, int *num_of_pages, double *time);
int time_rnd_sweep(FILE *arq, nseq_t qtd_reg, nseq_t *valid_registers, double *time);
void print_menu();

int main()
{
	struct REGISTRO reg;
	nseq_t nro_registros;
	nseq_t valid_registers;
	double time;

	int op;
	do {
    print_menu();
		printf("\nOPTION: ");
		scanf("%d", &op);
		fflush(stdin);

		switch(op) {
			case 1:
      {
        #ifdef _WIN32
          MEMORYSTATUSEX statex;
          statex.dwLength = sizeof(statex);
          GlobalMemoryStatusEx(&statex);

          __int64 ram_size_gb = statex.ullTotalPhys / DIV;
        #endif

        #ifdef linux
          char cmd[30];
          int  flag = 0;
          FILE *fp;
          char line[130];
          int  TotalMem, TotalFree, TotalUsed;

          memcpy (cmd,"\0",30);
          sprintf(cmd,"free -t -m|grep Total");
          fp = popen(cmd, "r");

          while(fgets(line, sizeof line, fp))
          {
            flag++;
            sscanf(line,"%*s %d %d %d",&TotalMem, &TotalUsed, &TotalFree);
          }
          pclose(fp);

          int ram_size_gb = TotalMem/1024;
        #endif


        nro_registros = 5 * ram_size_gb * Gi / sizeof(struct REGISTRO);
        if(!CREATE_HEAP_FILE(nro_registros)) {
            printf("Erro na criacao da heap file...\n");
            break;
        }

        printf("Sucesso na criacao da heap file!\n");
        break;
      }

			case 2:
	    		if(!READ_RANDOM(fopen("arquivo", "rb"), &reg)) {
	  				printf("Erro na leitura aleatoria...\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("\nLeitura aleatoria com sucesso!\n");
	 			break;

	 		case 3:
	 			if(!ISRT_AT_END(fopen("arquivo", "rb+"))) {
	 			    printf("Erro na insercao no final do arquivo...\n");
	 				break;
	 			}
	 			printf("Sucesso na insercao no final do arquivo!\n");
	 			break;

			case 4:
	    		if(!UPDATE_RANDOM(fopen("arquivo", "rb+"), &reg)) {
	  				printf("Erro na atualizacao aleatoria...\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("Sucesso na atualizacao aleatoria!\n");
	 			break;

	 		case 5:
	 			if(!DELETE_RANDOM(fopen("arquivo", "rb+"), &reg)) {
	  				printf("Erro na remocao aleatoria...\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("Sucesso na remocao aleatoria!\n");
	 			break;

			case 6:
      {
				int i, num_of_pages, block_sizes[4] = {1, 1e3, 1e4, 1e6};

				do {
					printf("Tamanho do bloco:\n");
					printf(" [1] 1\n");
					printf(" [2] 1e3\n");
					printf("\nEscolha: ");

					scanf("%d", &i);
				} while(i < 1 || i > 3);

				FILE *fb = fopen("arquivo", "rb");

				if(time_seq_sweep(fb, block_sizes[i], &valid_registers, &num_of_pages, &time)) {
					FILE_REGS(fb, &nro_registros);
					printf("Varredura Sequencial - \n");
					printf("Tamanho do bloco %d\n", block_sizes[i]);
					printf("Validos:\n");
					printf("%u\n\n", valid_registers);
					printf("Invalidos:\n");
					printf("%u\n\n", (nro_registros - valid_registers));
					printf("Paginas lidas com sucesso:\n");
                    printf("%d\n\n", num_of_pages);
					printf("Desempenho: \n");
					printf("%lfs\n\n", time);
				}
				break;
      }

			case 7:
      {
				nseq_t nro_rnd_sweep = 1;
				do {
					printf("Registros a serem lidos\n");
					scanf("%i", &nro_rnd_sweep);
				} while(nro_rnd_sweep <= 0);

				if(time_rnd_sweep(fopen("arquivo", "rb"), nro_rnd_sweep, &valid_registers, &time)) {
					printf("Leitura aleatoria:\n");
					printf("%d Registros\n\n", nro_rnd_sweep);
					printf("Validos:\n");
					printf("%u\n\n", valid_registers);
					printf("Invalidos:\n");
					printf("%u\n\n", (nro_rnd_sweep - valid_registers));
					printf("Desempenho:\n");
					printf("%lfs\n\n", time);
				}


        if (nro_rnd_sweep == 1) {
          int num_of_pages;
          double time_taken_rand = time;
          double time_taken_seq_sweep = 0;
          FILE *fb = fopen("arquivo", "rb");
          time_seq_sweep(fb, 1e3, &valid_registers, &num_of_pages, &time_taken_seq_sweep);

          while(time_taken_rand < time_taken_seq_sweep) {
            nro_rnd_sweep += 10000;
            time_rnd_sweep(fopen("arquivo", "rb"), nro_rnd_sweep, &valid_registers, &time_taken_rand);
          }

          printf("Aleatorio com melhor desempenho com %i registros\n", nro_rnd_sweep);
        }

				break;
      }

			case 8:
        break;

			default:
				printf("Insira um numero de 1 a 8, por favor!\n");
				break;
		}

	} while(op != 9);

	return 0;
}

void print_menu() {
  printf("\n[1] Criacao da heap file\n");
  printf("[2] Leitura aleatoria\n");
  printf("[3] Insercao no final\n");
  printf("[4] Atualizacao aleatoria\n");
  printf("[5] Remocao aleatoria\n");

  printf("[6] Varredura sequencial\n");
  printf("[7] Varredura aleatoria\n");

  printf("[8] Sair\n");
}

int time_seq_sweep(FILE *arq, int rnum_by_page, nseq_t *nvalids, int *num_of_pages, double *time) {

#ifdef __WIN32
  __int64 CLOCK_REALTIME;
  GetSystemTimeAsFileTime((FILETIME*)&CLOCK_REALTIME);
  CLOCK_REALTIME      -= 116444736000000000;           //1jan1601 to 1jan1970
#endif

	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);
	int retval = SEQUENTIAL_SWEEP(arq, rnum_by_page, nvalids, num_of_pages);
	clock_gettime(CLOCK_REALTIME, &t2);
	long s = t2.tv_sec - t1.tv_sec;
	long ns = t2.tv_nsec - t1.tv_nsec;

	*time = (double) s + ns * 1e-9;
	return retval;
}

int time_rnd_sweep(FILE *arq, nseq_t nreg, nseq_t *nvalids, double *time) {

#ifdef __WIN32
  __int64 CLOCK_REALTIME;
  GetSystemTimeAsFileTime((FILETIME*)&CLOCK_REALTIME);
  CLOCK_REALTIME      -= 116444736000000000;           //1jan1601 to 1jan1970
#endif

	struct timespec t1, t2;
	clock_gettime(CLOCK_REALTIME, &t1);

	int flag = RANDOM_SWEEP(arq, nreg, nvalids);

	clock_gettime(CLOCK_REALTIME, &t2);
	long s = t2.tv_sec - t1.tv_sec;
	long ns = t2.tv_nsec - t1.tv_nsec;

	*time = (double) s + ns * 1e-9;
	return flag;
}

