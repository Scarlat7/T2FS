#include <stdio.h>
#include "t2fs.h"
#include "BootController.h"
#include "TuplesController.h"
#include "apidisk.h"

int main(){

	DWORD LBN;
	int i;

	/* Esse teste supõe que o arquivo t2fs_disk.dat está re-inicializado */

	init_lib();	

	for(i = 0; i < 65 ; i++){
		mapVBN(8,i,&LBN);
		printf("\t\t\t\tReg 8, VBN %u, LBN %u\n", i, LBN);
		mapVBN(9,i,&LBN);
		printf("\t\t\t\tReg 9, VBN %u, LBN %u\n", i, LBN);
	}

	printf("Registro 9 file size in blocks: %d\n\texpected 65\n,", getFileBlockSize(9));

	printf("Teste: %d\n", deleteRegister(8));

	return 0;
}
