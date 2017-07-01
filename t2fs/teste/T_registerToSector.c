#include <stdio.h>
#include "t2fs.h"
#include "BootController.h"
#include "TuplesController.h"

int main(){

	init_lib();	

	if(registerToSector(0) == -1){
		printf("Erro no teste da registerToSector.\n");
	}	
	else if(registerToSector(0) != ctrl.boot.blockSize*1){
		printf("Erro no teste da funcao registerToSector, setor retornado para o registro 0: %d\n", registerToSector(0));
	}
	
	if(registerToSector(7) != 7*2 + ctrl.boot.blockSize){
		printf("Erro no teste da função registerToSector, setor retornado para o registro 7: %d\n", registerToSector(7));
	}

	printf("MFT 0: %d MFT 3: %d MFT 5: %d Último MFT: %d\n", registerToSector(0),registerToSector(3),registerToSector(5), registerToSector(ctrl.boot.MFTBlocksSize*2-1));

	if(registerToSector(ctrl.boot.MFTBlocksSize*2) == 0){
		printf("Erro no teste de limite superior.\n");
	}
	
	return 0;
}
