#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	char file[8]; // /fileXX
	int i;
	DWORD handle;
	for(i = 0; i < 21; i++) {
		sprintf(file, "/file%d", i);
		handle = create2(file);
		if(handle != -1 && i < 20) printf("File%d criado com sucesso. Seu handle é %d\n", i, handle);
		else if(handle == -1 && i == 20) printf("Muitos arquivos abertos. File%d não pôde ser aberto.\n", i);
		else {
			printf("Erro crítico.\n");
			return 1;
		}
	}
	return 0;
}
