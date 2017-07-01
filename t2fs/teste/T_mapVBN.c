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

	return 0;
}
