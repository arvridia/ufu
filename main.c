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

        // -  OBS: o nro_de_registros deve ser tal que o tamanho total do
        //         arquivo em bytes seja maior ou igual a 5 vezes a memória RAM
        //         do equipamento onde serão realizados os experimentos.
        
        nro_registros = 5 * ram_size_gb * Gi / sizeof(struct REGISTRO);
        if(!CREATE_HEAP_FILE(nro_registros)) {
            printf("ERROR CREATING THE HEAP FILE\n");
            break;
        }

        printf("HEAP FILE CREATE SUCCESS\n");
        break;
      }

			case 2:
	    		if(!READ_RANDOM(fopen("arquivo", "rb"), &reg)) {
	  				printf("ERROR ON READ_RANDOM.\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("\nREAD_RANDOM SUCCESS\n");
	 			break;
	 			
	 		case 3:
	 			if(!ISRT_AT_END(fopen("arquivo", "rb+"))) {
	 			    printf("ISRT_AT_END ERROR.\n");
	 				break;
	 			}
	 			printf("ISRT_AT_END SUCCESS\n");
	 			break;

			case 4:
	    		if(!UPDATE_RANDOM(fopen("arquivo", "rb+"), &reg)) {
	  				printf("ERROR ON UPDATE_RANDOM\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("UPDATE_RANDOM SUCCESS\n");
	 			break;

	 		case 5:
	 			if(!DELETE_RANDOM(fopen("arquivo", "rb+"), &reg)) {
	  				printf("DELETE_RANDOM ERROR\n");
	  				break;
	    		}

	    		if(PRINT_REG(&reg))
	 				printf("DELETE_RANDOM SUCCESS\n");
	 			break;
	 			
			case 6:
      {
				int i, num_of_pages, block_sizes[4] = {1, 1e3, 1e4, 1e6};
				
				do {
					printf("BLOCK SIZE:\n");
					printf(" [0] 1\n");
					printf(" [1] 1e3\n");
					printf("\nCHOICE: ");

					scanf("%d", &i);
				} while(i < 0 || i > 2);

				FILE *fb = fopen("arquivo", "rb");

				if(time_seq_sweep(fb, block_sizes[i], &valid_registers, &num_of_pages, &time)) {
					FILE_REGS(fb, &nro_registros);
					printf("SEQUENTIAL_SWEEP - BLOCK SIZE %d\n", block_sizes[i]);
					printf("VALID: %u\n", valid_registers);
					printf("INVALID: %u\n", (nro_registros - valid_registers));
					printf("PAGES READ: %d\n", num_of_pages);
					printf("TIME TAKEN: %lfs\n\n", time);
				}
				break;
      }
				
			case 7:
      {
				nseq_t nro_rnd_sweep = 1;
				do {
					printf("RECORDS TO BE READ (do experiment with 1): ");
					scanf("%i", &nro_rnd_sweep);
				} while(nro_rnd_sweep <= 0);

				if(time_rnd_sweep(fopen("arquivo", "rb"), nro_rnd_sweep, &valid_registers, &time)) {
					printf("RANDOM READ %d RECORDS(s)\n\n", nro_rnd_sweep);
					printf("VALID: %u\n", valid_registers);
					printf("INVALID: %u\n", (nro_rnd_sweep - valid_registers));
					printf("TIME TAKEN: %lfs\n\n", time);
				}

        // OBS: repetir os experimento até que a quantidade de registros seja tal que
        //  o tempo de acesso aleatório seja maior que o menor tempo de leitura de todo o 
        //  arquivo obtido no item 1.B. Para cada repetição do experimento 
        //  deve-se reiniciar a máquina.

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

          printf("RANDOM BETTER AT %i RECORDS\n", nro_rnd_sweep);        
        }

				break;
      }
				
			case 8:
        break;

			default:
				printf("INVALID OPTION\n");
				break;
		}
				
	} while(op != 9);

	return 0;
}

void print_menu() {
  printf("\n[1] CREATE_HEAP_FILE\n");
  printf("[2] READ_RANDOM\n");
  printf("[3] ISRT_AT_END\n");
  printf("[4] UPDATE_RANDOM\n");
  printf("[5] DELETE_RANDOM\n");

  printf("[6] SEQUENTIAL SWEEP\n");
  printf("[7] RANDOM SWEEP\n");

  printf("[8] QUIT\n");
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

