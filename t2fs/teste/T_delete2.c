#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	int i;
	//init_openFilesArray();
	int handle;

	handle = create2("/Eu");


	printf("********************************************\n");
	write2(handle, "cechin eh o maioral", 20);
	write2(handle, "e vc nao", 9);
	for(i = 0; i < 1024; i++){
		write2(handle, "a", 1);
	}

	printf("%d\n", delete2("/Eu"));


	printf("********************************************\n");

	return 0;
}