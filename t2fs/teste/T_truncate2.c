#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	int i;
	//init_openFilesArray();
	int handle, read;
	char teste[30];
	char buf[30];
	strcpy(teste, "/natMoriiii");

	if((handle = create2(teste)) == ERROR){
		printf("Incapaz de criar /Test\n");
		return -1;
	}	
	printf("********************************************\n");
	write2(handle, "cechin eh o maioral", 20);
	write2(handle, "e vc nao", 9);
	ctrl.openFilesArray[handle].currentPointer = 26;
	write2(handle, "se67", 5);
	for(i = 0; i < 1024; i++){
		write2(handle, "a", 1);
	}
	printf("s0:%d\n",ctrl.openFilesArray[handle].bytesSize);
	seek2(handle, 3);
	printf("Teste: %d\n", truncate2(handle));
	printf("s1:%d\n",ctrl.openFilesArray[handle].bytesSize);
	write2(handle, "ao eh massa", 11);
	seek2(handle, 0);
	read = read2(handle, buf, 19);
	printf("Teste: %d\n", read);
	buf[read] = '\0';
	printf("Teste: %s\n", buf);
	printf("********************************************\n");

	return 0;
}