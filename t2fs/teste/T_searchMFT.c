#include <stdio.h>
#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"

int main(){
	struct t2fs_4tupla MFT[32];

	if(init_lib() != 0 )
		printf("Falha na init_lib.\n");

	if(searchMFT(2, MFT) == 0) {
		printf("Sucesso!\n");
		printf("Validade: %d\nVBN: %d\tLBN: %d\nNumCB: %d\n", MFT[0].atributeType, MFT[0].virtualBlockNumber, MFT[0].logicalBlockNumber, MFT[0].numberOfContiguosBlocks);
	}
	return 0;
}
