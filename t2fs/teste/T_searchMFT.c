#include <stdio.h>
#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"

int main(){
	struct t2fs_4tupla MFT[64];

	if(init_lib() != 0 )
		printf("Falha na init_lib.\n");

	if(searchMFT(1, MFT) == 0) {
		printf("Sucesso!\n");
		printf("Tupla 0:\nValidade: %d\tVBN: %d\tLBN: %d\tNumCB: %d\n", MFT[0].atributeType, MFT[0].virtualBlockNumber, MFT[0].logicalBlockNumber, MFT[0].numberOfContiguosBlocks);
		printf("Tupla 31:\nValidade: %d\tVBN: %d\tLBN: %d\tNumCB: %d\n", MFT[31].atributeType, MFT[31].virtualBlockNumber, MFT[31].logicalBlockNumber, MFT[31].numberOfContiguosBlocks);
	}
	return 0;
}
