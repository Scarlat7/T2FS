#include "FilesController.h"
#include <stdio.h>
#include <string.h>

#define ERRO -1

int main(){
	int option, handle;
	DIRENT2 entry;
	init_lib();
	char path1[8], path2[8], path3[8], teste[6], root[2];
	strcpy(root, "/");
	strcpy(teste, "/Test");
	strcpy(path1, "/Test/A");
	strcpy(path2, "/Test/B");
	strcpy(path3, "/Test/C");

	//Cria o diretório principal, com os 3 subdiretórios dentro dele
	if(mkdir2(teste) == ERRO) printf("Incapaz de criar /Test\n");
	if(mkdir2(path1) == ERRO) printf("Incapaz de criar %s\n", path1);
	if(mkdir2(path2) == ERRO) printf("Incapaz de criar %s\n", path2);
	if(mkdir2(path3) == ERRO) printf("Incapaz de criar %s\n", path3);

	printf("Tentando remover %s...\n", root);
	option = rmdir2(root);
	if(option == -1) printf("Sucesso! Root não pode ser removido.\n");
	else printf("Erro no teste 1. Retornou %d.\n", option);
	
	printf("Tentando remover %s...\n", teste);
	option = rmdir2(teste);
	if(option == -3) printf("Sucesso! %s não pode ser removido pois não está vazio.\n", teste);
	else printf("Erro no teste 2. Retornou %d.\n", option);
	
	printf("Tentando remover %s...\n", path1);
	option = rmdir2(path1);
	if(option == 0) printf("Sucesso! %s foi removido.\n", path1);
	else printf("Erro no teste 3. Retornou %d.\n", option);

	handle = opendir2(teste);
	readdir2(handle, &entry);
	printf("Primeiro record de /Test:\n");
	printf("Name: %s\n", entry.name);

	return 0;
}
