#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_control ctrl;

int mapLBN(DWORD LBN, DWORD* sector){
	DWORD base;
	base = 1 + ctrl.boot.MFTBlocksSize*ctrl.boot.blockSize;
	*sector = base + LBN * ctrl.boot.blockSize;
	if(*sector > ctrl.boot.diskSectorSize) return -1;
	return 0;
}

int searchMFT(DWORD numReg, struct t2fs_4tupla *vector) {
	//Fins de debug
	printf("Chego até aqui no MFT.\n");
	printf("BlockSize: %d\tNumReg: %d\tVector: %p\n", ctrl.boot.blockSize, numReg, vector);
	//Falha de segmentação abaixo
	if(read_sector(ctrl.boot.blockSize + 2*numReg, (unsigned char*)vector)) return -1;
	if(read_sector(ctrl.boot.blockSize + 1 + 2*numReg, (unsigned char*)vector + SECTOR_SIZE)) return -1;
	
	return 0;
}

/*
int readSectorFile(FILE2 fileHandle, int nSectors, BYTE* buffer) {
	
	DWORD sector;
	DWORD startVirtualBlock, block;
	int i, j, k;
	int remaining = 0;
	BYTE bufferS[SECTOR_SIZE];
	t2fs_4tupla bufferT[SECTOR_SIZE/sizeof(t2fs_4tupla)];

	int currentMFT = ctrl.OpenFilesArray[fileHandle].MFT;
	
	j = 0;
	do{
		if(read_sector(registerToSector(currentMFT)+j, bufferT) != 0){
			fprintf(stderr, "Erro ao ler registro MFT do arquivo.\n");
			return -1;
		}
	
		startVirtualBlock = ctrl.OpenFilesArray[fileHandle].currentPointer/ctrl.blockSize;	
		
		i = 0;
		
		//loop de leitura do buffer de tuplas de um setor
		while(i < SECTOR_SIZE/sizeof(t2fs_4tupla) && remaining != nSectors){
			if(bufferT[i].atributeType == MAPEAMENTO){
				if((bufferT[i].virtualBlockNumber + bufferT[i].numberOfContiguousBlocks-1) >=  startVirtual && bufferT[i].virtualBlockNumber >= startVirtual){
					//for(k = 0; k < nSectors; k++){
					k = startVirtualBlock - bufferT[i].virtualBlockNumber;
					while(remaining != nSectors && k < numberOfContiguousBlocks){
						block = (startVirtualBlock - bufferT[i].virtualBlockNumber)+bufferT[i].logicalBlockNumber + k;
						sector = block*ctrl.blockSize;
						while(sector%blockSize != 0 && remaining != nSectors){
							if(!remaining) 
								sector += (ctrl.OpenFilesArray[fileHandle].currentPointer%blockSize)/SECTOR_SIZE;
							else	sector++;
							//read_sector(sector, bufferS);
							read_sector(sector, buffer+index);
							remaining++;
							//memcpy(buffer+index, bufferS, SECTOR_SIZE);
							index += SECTOR_SIZE;
						}
						k++;
					}

				}
				i++;
			}else if(bufferT[i-1].attributeType == FIM_ENCADEAMENTO){
				if(remaining != nSectors ){
					fprintf(stderr, "Numero de setores requisitados inexistentes no arquivo.\n");
					return -1;
				}
			}
		}
	
		if(bufferT[i-1].attributeType == MFT_ADICIONAL){
			currentMFT = bufferT[i-1].virtualBlockNumber;
			j = 0;
		}else{
			j+=1;
		}

		if(bufferT[i-1].attributeType == FIM_ENCADEAMENTO){
			if(remaining != nSectors ){
				fprintf(stderr, "Numero de setores requisitados inexistentes no arquivo.\n");
				return -1;
			}
		}
		 
	}while(remaining != nSectors);

	return 0;
}

int registerToSector(DWORD MFT){

	if(MFT > MFTBlocksSize || MFT < 0){
		fprintf(stderr, "Registro MFT requisitado fora dos limites.\n");i
		return -1;
	}

	return (MFT + 1)*blockSize;
}

int mapVBN(DWORD MFT, DWORD VBN, DWORD* LBN) {
	return -1;
}*/
