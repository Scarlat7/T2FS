#include <stdio.h>
#include "t2fs.h"
#include "BootController.h"
#include "TuplesController.h"
#include "apidisk.h"

int main(){

	DWORD LBN;
	int i, n;

	/* Esse teste supõe que o arquivo t2fs_disk.dat está re-inicializado */

	init_lib();	

	for(i = 0; i < 63 ; i++){
		mapVBN(8,i,&LBN);
		printf("\t\t\t\tReg 8, VBN %u, LBN %u\n", i, LBN);
		mapVBN(9,i,&LBN);
		printf("\t\t\t\tReg 9, VBN %u, LBN %u\n", i, LBN);
	}

	mapVBN(9,63,&LBN);
	mapVBN(9,64,&LBN);
	mapVBN(8,63,&LBN);
	mapVBN(9,65,&LBN);

	printf("Registro 9 file size in blocks: %d\n\texpected 66\n,", getFileBlockSize(9));

	n = 8;
	printf("Teste: %d\n", deleteBlocks(9, &n));
	printf("Registro 9 file size in blocks: %d\n\texpected 58\n,", getFileBlockSize(9));

	n = getFileBlockSize(9);
	printf("Teste: %d\n", deleteBlocks(9, &n));
	printf("Registro 9 file size in blocks: %d\n\texpected 0\n,", getFileBlockSize(9));

	return 0;
}
