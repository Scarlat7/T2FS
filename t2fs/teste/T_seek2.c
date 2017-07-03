#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();

	int handle;
	char teste[12];
	strcpy(teste, "/leomoriii");

	if((handle = create2(teste)) == ERROR){
		printf("Incapaz de criar /Test\n");
		return -1;
	}	
	printf("********************************************\n");
	write2(handle, "cechin eh o maioral", 20);
	printf("s1: Pointer %d\n",ctrl.openFilesArray[handle].currentPointer);
	write2(handle, "e vc nao", 9);
	printf("s2: Pointer %d\n",ctrl.openFilesArray[handle].currentPointer);
	
	if(seek2(handle, 2) != 0)	printf("Erro!\n");


	write2(handle, "s", 1);
	printf("s3:%d\n",ctrl.openFilesArray[handle].currentPointer);
	if(seek2(handle, -1) != 0)	printf("Erro!!\n");

	printf("s4:%d\n",ctrl.openFilesArray[handle].currentPointer);
	write2(handle, "HA", 2);
	write2(handle, "HAHA", 2);
	if(seek2(handle, 35) == 0)	printf("Erro!!!\n");
	printf("********************************************\n");

	return 0;
}                                                           