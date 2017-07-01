#include "t2fs.h"
#include "FilesController.h"
#include "BootController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	init_openFilesArray();
	int handle;
	char teste[6];
	strcpy(teste, "/oi.a");

	if((handle = create2(teste)) == ERROR) printf("Incapaz de criar /Test\n");
	printf("********************************************\n");
	printf("%d\n", handle);
	printf("********************************************\n");

	return 0;
}
