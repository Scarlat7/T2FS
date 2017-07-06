#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	
	init_lib();
	int handle;

	if((handle = create2("/natMoriiii")) == ERROR){
		printf("Incapaz de criar arquivo\n");
		return -1;
	}	

	printf("********************************************\n");
	write2(handle, "cechin eh o maioral", 20);
	printf("s2:%d\n",ctrl.openFilesArray[handle].bytesSize);
	write2(handle, "e vc nao", 9);
	printf("s3:%d\n",ctrl.openFilesArray[handle].bytesSize);

	printf("Teste %d\n", close2(handle));

	return 0;
}