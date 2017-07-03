#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	//init_openFilesArray();
	int handle;
	char teste[12];
	char buffer[20];
	strcpy(teste, "/moribardo");

	if((handle = create2(teste)) == ERROR){
		printf("Incapaz de criar /Test\n");
		return -1;
	}	
	printf("********************************************\n");
	printf("s1:%d\n",ctrl.openFilesArray[handle].bytesSize);
	write2(handle, "cechin eh o maioral", 20);
	seek2(handle, 0);
	printf("Retorno 1: %d\n",read2(handle, buffer, 6));
	buffer[6] = '\0';
	printf("Lido: %s\n",buffer);
	printf("Retorno 2: %d\n",read2(handle, buffer, 14));
	buffer[15] = '\0';
	printf("Lido: %s\n",buffer);
	seek2(handle,6);
	printf("Retorno 3: %d\n",read2(handle, buffer, 16));
	buffer[17] = '\0';
	printf("Lido: %s\n",buffer);


	printf("********************************************\n");

	return 0;
}