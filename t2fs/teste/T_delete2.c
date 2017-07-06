#include "t2fs.h"
#include "FilesController.h"
#include "apidisk.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	int i;
	int handle;
	struct t2fs_record t[4];

	handle = create2("/EuAmoOLeo2");


	printf("********************************************\n");
	write2(handle, "cechin eh o maioral", 20);
	write2(handle, "e vc nao", 9);
	for(i = 0; i < 1024; i++){
		write2(handle, "a", 1);
	}

	printf("Antes close bytesSize: %d blocksSize: %d\n", ctrl.openFilesArray[handle].bytesSize, ctrl.openFilesArray[handle].blocksSize);

	close2(handle);

	read_sector(8200, (BYTE*)t);

	printf("Depois close bytesSize: %d blocksSize: %d\n", t[2].bytesFileSize, t[2].blocksFileSize);

	printf("%d\n", delete2("/EuAmoOLeo2"));


	printf("********************************************\n");

	return 0;
}