#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	//este teste supõe um disco reinicializado
	init_lib();
	char teste[7]; // /teste
	char dir[13]; // /teste/dirXX
	int i, erro;
	DWORD handle;
	strcpy(teste, "/teste");
	mkdir2(teste);
	for(i = 0; i < 48; i++) { //O suficiente para encher três blocos
		sprintf(dir, "/teste/dir%d", i);
		handle = mkdir2(dir);
	}
	//Remove bloco do meio
	for(i = 16; i < 32; i++) {
		sprintf(dir, "/teste/dir%d", i);
		if((erro = rmdir2(dir))) {
			printf("Erro %d ao remover %s\n", erro, dir);
			return 1;
		}
		else printf("Sucesso ao remover %s\n", dir);
	}
	//Remove bloco do início
	for(i = 0; i < 16; i++) {
		sprintf(dir, "/teste/dir%d", i);
		if((erro = rmdir2(dir))) {
			printf("Erro %d ao remover %s\n", erro, dir);
			return 1;
		}
		else printf("Sucesso ao remover %s\n", dir);
	}
	//Remove bloco do fim
	for(i = 32; i < 48; i++) {
		sprintf(dir, "/teste/dir%d", i);
		if((erro = rmdir2(dir))) {
			printf("Erro %d ao remover %s\n", erro, dir);
			return 1;
		}
		else printf("Sucesso ao remover %s\n", dir);
	}
	//Remove /teste
	if((erro = rmdir2(teste))) {
		printf("Erro %d ao remover %s\n", erro, teste);
		return 1;
	}
	else printf("Sucesso ao remover %s\n", teste);
	
	return 0;
}
