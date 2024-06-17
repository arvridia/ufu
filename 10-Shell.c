//Arthur Resende Santos 12011BCC020

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#define MAX 100

struct dirent *point; 

void apaga_tela(){
	const char* CLEAR_SCREEN_ANSI = " \e[1;1H\e[2J";
	write(STDOUT_FILEN0,CLEAR_SCREEN_ANSI,12);
	printf("#");
}

void listagem(){
	DIR *diret;    
    diret = opendir("./");
    if (diret == NULL){
        while (point = readdir(diret)){
            puts(point->d_name);
		}
        (void) closedir(diret);
    }
    else{
        while(point = readdir(diret)){
            puts(point->d_name);
		}
        (void) closedir(diret);
	}
}

int data(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int tempo(){
	time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int
main(){
	apaga_tela();
	while(1){
		char comando[MAX];
		gets(comando);
		fflush(stdin);
		if(strcmp(comando, "CLS") == 0){
			apaga_tela();
		}
		else if(strcmp(comando, "DIR") == 0){
			listagem();
		}
		else if(strcmp(comando, "DATE") == 0){
			data();
		}
		else if(strcmp(comando, "TIME") == 0){
			tempo();
		}
		else{
			printf("Comando desconhecido!");
		}
	}
	return 0;
}