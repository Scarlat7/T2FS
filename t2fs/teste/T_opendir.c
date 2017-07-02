#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	int handle1, handle2;
	char path[8], teste[6];
	init_lib();
	strcpy(teste, "/Test");
	strcpy(path, "/Test/A");

	if(mkdir2(teste)) printf("Incapaz de criar /Test\n");
	printf("********************************************\n");
	printf("Imprimindo os primeiros records do root.\n");
	printRecords(1);
	printf("********************************************\n");

	if(mkdir2(path)) printf("Incapaz de criar %s\n", path);
	printf("********************************************\n");
	printf("Imprimindo os primeiros records de /Test.\n");
	printRecords(pathExists(path, "A"));
	printf("********************************************\n");

	handle1 = opendir2(teste);
	if(handle1 == -1) printf("A abertura do diretorio /Test falhou.\n");
	else printf("Handle gerado para /Test: %d\n", handle1);

	handle2 = opendir2(path);
	if(handle2 == -1) printf("A abertura do diretorio /Test/A falhou.\n");
	else printf("Handle gerado para /Test/A: %d\n", handle2);
	return 0;
}
