#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FIM_ENCADEAMENTO 0
#define MAPEAMENTO 1
#define MFT_ADICIONAL 2

t_control ctrl;

int searchMFT(int numReg, struct t2fs_4tupla *vector) {
	unsigned char buffer1[256], buffer2[256];
	int i = 0, index = 0;
	if(read_sector(ctrl.boot.blockSize + 2*numReg, buffer1)) return -1;
	if(read_sector(ctrl.boot.blockSize + 2*numReg + 1, buffer2)) return -1;
	for(i=0; i<16; i++) {
		memcpy(&vector[i].atributeType, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].virtualBlockNumber, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].logicalBlockNumber, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].numberOfContiguosBlocks, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
	}
	printf("Validade: %d\nVBN: %d\tLBN: %d\nNumCB: %d\n", vector[0].atributeType, vector[0].virtualBlockNumber, vector[0].logicalBlockNumber, vector[0].numberOfContiguosBlocks);
	index = 0;
	for(i=16; i<32; i++) {
		memcpy(&vector[i].atributeType, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].virtualBlockNumber, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].logicalBlockNumber, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].numberOfContiguosBlocks, buffer2 + index, sizeof(DWORD));
	}
	return 0;
}

int readSectorFile(FILE2 fileHandle, int nSectors, BYTE* buffer) {
	
	DWORD sector;
	DWORD startVirtualBlock, block;
	int i, j, k;
	BYTE found = 0, bufferS[SECTOR_SIZE];
	t2fs_4tupla bufferT[SECTOR_SIZE/sizeof(t2fs_4tupla)];

	int currentMFT = ctrl.OpenFilesArray[fileHandle].MFT;
	/*
	j = 0;
	do{
		if(read_sector(RegisterToSector(currentMFT)+j, buffer) != 0){
			fprintf(stderr, "Erro ao ler registro MFT do arquivo.\n");
			return -1;
		}
	
		startVirtualBlock = ctrl.OpenFilesArray[fileHandle].currentPointer/ctrl.blockSize;	
		
		i = 0;
		
		while(i < SECTOR_SIZE/sizeof(t2fs_4tupla) && found != 1){
			if(bufferT[i].atributeType == MAPEAMENTO){
				if((bufferT[i].virtualBlockNumber + bufferT[i].numberOfContiguousBlocks-1) <=  startVirtual && bufferT[i].virtualBlockNumber >= startVirtual){
					found = 1;
					for(k = 0; k < nSectors; k++){
						block = (startVirtualBlock - bufferT[i].virtualBlockNumber)+bufferT[i].logicalBlockNumber;
						sector = block*ctrl.blockSize;
						sector += (ctrl.OpenFilesArray[fileHandle].currentPointer%blockSize)/SECTOR_SIZE;
						read_sector(sector, bufferS);
						memcpy(buffer+index, bufferS, SECTOR_SIZE);
						index += SECTOR_SIZE;
					}

				}
				i++;
			}
		}
	
		if(bufferT[i-1].attributeType == MFT_ADICIONAL){
			currentMFT = bufferT[i-1].virtualBlockNumber;
			j = 0;
		}else{
			j+=1;
		}
		 
	}while(found != 1);
	*/

	return -1;
}

int mapVBN(DWORD MFT, DWORD VBN, DWORD* LBN) {
	return -1;
}
