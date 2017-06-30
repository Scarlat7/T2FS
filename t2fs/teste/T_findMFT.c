#include <stdio.h>
#include "t2fs.h"
#include "BootController.h"
#include "TuplesController.h"
#include "apidisk.h"

int main(){

	/* Esse teste supõe que o arquivo t2fs_disk.dat está re-inicializado */

	init_lib();	

	if(findMFT() <= 0){
		printf("Erro no teste de findMFT.\n");
	}
	else{
		printf("MFT encontrado: %d\n", findMFT());
	}

	struct t2fs_4tupla s[32];
	s[0].atributeType = MAPEAMENTO;
	write_sector(registerToSector(4), (BYTE *)s);

	if(findMFT(0) != 5){
		printf("Erro no teste de findMFT apos modificar registro.\n");
	}	
	else{
		printf("MFT encontrado: %d\n", findMFT());
	}

	return 0;
}
