#include "t2fs.h"
#include "FilesController.h"
#include "BootController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	char path[8], teste[6];
	strcpy(teste, "/Test");
	strcpy(path, "/Test/A");

	if(mkdir2(teste)) printf("Incapaz de criar /Test\n");
	printf("********************************************\n");
	printf("Imprimindo os 4 primeiros records do root.\n");
	printRecords(1);
	printf("********************************************\n");

	if(mkdir2(path)) printf("Incapaz de criar %s\n", path);
	printf("********************************************\n");
	printf("Imprimindo os 4 primeiros records de /Test.\n");
	printRecords(pathExists(path, "A"));
	printf("********************************************\n");
	return 0;
}
