#include "FilesController.h"
#include <stdio.h>
#include <string.h>

#define ERRO -1

int main(){
	//Este teste pressupõe um disco reinicializado
	int i, handle, option;
	DIRENT2 current;
	init_lib();
	char path1[8], path2[8], path3[8], teste[6];
	strcpy(teste, "/Test");
	strcpy(path1, "/Test/A");
	strcpy(path2, "/Test/B");
	strcpy(path3, "/Test/C");

	//Cria o diretório principal, com os 3 subdiretórios dentro dele
	if((handle = mkdir2(teste)) == ERRO) printf("Incapaz de criar /Test\n");
	if(mkdir2(path1) == ERRO) printf("Incapaz de criar %s\n", path1);
	if(mkdir2(path2) == ERRO) printf("Incapaz de criar %s\n", path2);
	if(mkdir2(path3) == ERRO) printf("Incapaz de criar %s\n", path3);

	if(isOpen(teste, 2) == 0) handle = opendir2(teste);

	for(i = 0; i < 4; i ++) {
		option = readdir2(handle, &current);
		printf("option: %d\n", option);
		if(option == 0) {
			printf("\nEntry %d\n", i);
			printf("Name: %s\tType: %d\tSize: %d\n", current.name, current.fileType, current.fileSize);
		}
		else if(option == -1){
			printf("Fim da leitura.\n");
			return 0;
		}
		else{ 
			printf("Retornou: %d. Erro na função readdir2.\n", option);
			return 0;
		}
	}

	return 0;
}
