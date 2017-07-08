#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

#define SIZE 2049
#define SIZE2 1040
int main(){
	init_lib();
	int i;
	//init_openFilesArray();
	int handle;

	char escrita[SIZE];
	char escrita2[SIZE2];

	char leitura[SIZE];
	char leitura2[SIZE2];
	

	//if((handle = open2("/theUltimateWrite")) == ERROR)
		if((handle = create2("/theUltimateWrite")) == ERROR){
			printf("Incapaz de criar /Test\n");
			return -1;
		}
	
	escrita2[0] = 'C';	
	write2(handle, "C", 1);

	for(i = 1; i < SIZE2; i++){
		if(i == SIZE2 - 1){
			write2(handle, "\0", 1);
			escrita2[i] = '\0';
		}else{
			write2(handle, "b", 1);
			escrita2[i] = 'b';
		}
	}
	
	
	escrita[0] = 'D';
	for(i = 1; i < SIZE; i++){
		escrita[i] = 'a';
	}
	escrita[SIZE-1] = '\0';
	
	
	write2(handle, escrita, SIZE);

	

	printf("********************************************\n");
	
	
	printf("********************************************\n");
	
	seek2(handle, 0);	
	read2(handle, leitura2, SIZE2);

	read2(handle, leitura, SIZE);
	
	
	puts(leitura2);
	puts(leitura);

	puts("TESTE ESCRITA DO B");

	if(strcmp(escrita2, leitura2) < 0){
		puts("leu mais do que escreveu");
	} else if(strcmp(escrita2, leitura2) == 0){
		puts("Teste sucedido!");
	} else{
		puts("A string lida é menor do que a escrita");
		printf("%d\n", strcmp(escrita2, leitura2));
	}

	puts("TESTE ESCRITA DO A");

	if(strcmp(escrita, leitura) < 0){
		puts("leu mais do que escreveu");
	} else if(strcmp(escrita, leitura) == 0){
		puts("Teste sucedido!");
	} else{
		puts("A string lida é menor do que a escrita");
		printf("%d\n", strcmp(escrita, leitura));
	}


	return 0;
}
