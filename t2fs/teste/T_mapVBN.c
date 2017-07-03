#include <stdio.h>
#include "t2fs.h"
#include "BootController.h"
#include "TuplesController.h"
#include "apidisk.h"

int main(){

	DWORD LBN;

	/* Esse teste supõe que o arquivo t2fs_disk.dat está re-inicializado */

	init_lib();	

	if(mapVBN(6,1, &LBN) == 0){
		printf("ERRO no teste.\n");
	}else{
		printf("Sucesso no teste de tentar acessar um VBN != 0 em um registro ainda nao inicializado.\n");
	}

	if(mapVBN(6,0, &LBN) != 0){
		printf("ERRO no teste mapVBN no registro 6, VBN 0.\n");
	}else{
		printf("Mapeamento registro 6, VBN 0, LBN %u\n", LBN);
	}

	if(mapVBN(6,0,&LBN) != 0){
		printf("ERRO no teste de consulta de mapeamento existente.\n");
	}else{
		printf("Consulta mapeamento registro 6, VBN 0, LBN %u\n", LBN);
	}

	if(mapVBN(6,1,&LBN) != 0){
		printf("ERRO no teste de mapeamento da VBN 1\n");
	}else{
		printf("Mapeamento registro 6, VBN 1, LBN %u\n", LBN);
	}

	mapVBN(7,0,&LBN);
	printf("Mapeamento registro 7, VBN 0, LBN %u\n", LBN);
	mapVBN(7,1,&LBN);
	printf("Mapeamento registro 7, VBN 1, LBN %u\n", LBN);

	if(mapVBN(6,2,&LBN) != 0){
		printf("ERRO no teste de mapeamento bloco nao contiguo.\n");
	}else{
		printf("Mapeamento registro 6, VBN 2, LBN %u\n", LBN);
	}

	int i;

	for(i = 0; i < 33 ; i++){
		mapVBN(8,i,&LBN);
		printf("\t\t\t\tReg 8, VBN %u, LBN %u\n", i, LBN);
		mapVBN(9,i,&LBN);
		printf("\t\t\t\tReg 9, VBN %u, LBN %u\n", i, LBN);
	}

	printf("Registro 9 file size in blocks: %d\n\texpected 33\n,", getFileBlockSize(9));
	printf("Registro 6 file size in blocks: %d\n\texpected 3\n,", getFileBlockSize(6));

	return 0;
}
