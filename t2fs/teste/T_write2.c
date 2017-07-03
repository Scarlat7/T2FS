#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	int i;
	//init_openFilesArray();
	int handle;
	char teste[12];
	strcpy(teste, "/natmoriiii");

	if((handle = create2(teste)) == ERROR){
		printf("Incapaz de criar /Test\n");
		return -1;
	}	
	printf("********************************************\n");
	printf("s1:%d\n",ctrl.openFilesArray[handle].bytesSize);
	write2(handle, "cechin eh o maioral", 20);
	printf("s2:%d\n",ctrl.openFilesArray[handle].bytesSize);
	write2(handle, "e vc nao", 9);
	printf("s3:%d\n",ctrl.openFilesArray[handle].bytesSize);
	ctrl.openFilesArray[handle].currentPointer = 26;
	write2(handle, "se67", 5);
	printf("s4:%d\n",ctrl.openFilesArray[handle].bytesSize);
	for(i = 0; i < 1024; i++){
		write2(handle, "a", 1);
	}
	printf("********************************************\n");

	return 0;
}