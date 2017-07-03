#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	int handle1, handle2;
	char path[8], teste[6];
	init_lib();
	strcpy(teste, "/Test");
	strcpy(path, "/Test/A");

	if((handle1 = mkdir2(teste)) == -1) {
		printf("%s já foi criado.\n", teste);
		handle1 = opendir2(teste);
		if(handle1 == -1) {
			printf("A abertura do diretorio %s falhou.\n", teste);
			return 1;
		}
		printf("Handle %d gerado para %s\n", handle1, teste);
	}
	if((handle2 = mkdir2(path)) == -1) {
		printf("%s já foi criado.\n", path);
		handle2 = opendir2(path);
		if(handle2 == -1) {
			printf("A abertura do diretorio %s falhou.\n", path);
			return 1;
		}
		printf("Handle %d gerado para %s\n", handle2, path);
	}
	if(closedir2(handle1)) {
		printf("Arquivo %s não pode ser fechado.\n", teste);
	}
	if(closedir2(handle2)) {
		printf("Arquivo %s não pode ser fechado.\n", path);
	}
	printf("Validade de %d: %d\n", handle1, ctrl.openDirectoriesArray[handle1].valid);
	printf("Validade de %d: %d\n", handle2, ctrl.openDirectoriesArray[handle2].valid);
	return 0;
}
