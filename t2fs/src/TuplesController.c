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
						block = bufferT[i].logicalBlockNumber + k;
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
}*/
 
int registerToSector(DWORD MFT){

	if(MFT > ctrl.boot.MFTBlocksSize || MFT < 0){
		fprintf(stderr, "Registro MFT requisitado fora dos limites.\n");
		return -1;
	}

	return (MFT + 1)*ctrl.boot.blockSize;
}

/*
int mapVBN(DWORD MFT, DWORD VBN, DWORD* LBN) {
	
	t2fs_4tupla bufferT[SECTOR_SIZE/sizeof(t2fs_4tupla)], bufferNew[SECTOR_SIZE/sizeof(t2fs_4tupla)];

	int i, j = 0, k;
	DWORD currentMFT = MFT, newMFT;
	int bit;	

	read_sector(registerToSector(currentMFT)+j,bufferT);
	
	if(bufferT[0].attributeType == INVALID_PTR && VBN != 0){
		fpritnf(stderr,"MFT invalido para mapeamento.\n");
		return -1;
	}
	else if(bufferT[0].attributeType == INVALID_PTR && VBN == 0){
		//This MFT is new
		bufferT[0].attributeType = MAPEAMENTO;
		bufferT[0].VirtualBlockNumber = VBN;
		bit = searchBitMap2(0);
		if(bit > 0){
			bufferT[0].LogicalBlockNumber= bit;
			*LBN = bit;
			setBitMap2(bit, 1);
		}else{
			fprintf(stderr, "Bitmap nao pode mapear bloco.\n");
			return -1;
		}
		bufferT[0].numberOfContigousBlocks = 1;
		bufferT[1].attributeType = FIM_ENCADEAMENTO;
		write_sector(registerToSector(currentMFT), bufferT);
		return 0;		
	}

	do{
		i = 0;
		while(i < SECTOR_SIZE/sizeof(t2fs_4tupla) && bufferT[i].attributeType != FIM_ENCADEAMENTO){
			//se o VBN procuraod está mapeado nessa tupla
			if(bufferT[i].attributeType == MAPEAMENTO)
				if((bufferT[i].virtualBlockNumber + bufferT[i].numberOfContiguousBlocks-1) >= VBN && bufferT[i].virtualBlockNumber >= VBN){
					*LBN = (VBN  - bufferT[i].virtualBlockNumber) + bufferT[i].logicalBlockNumber;
				}
				else	i++;	
		}
		
		//Achou o lugar onde deve começar a mapeamento do próximo
		if(bufferT[i].attributeType == FIM_ENCADEAMENTO){
			if(VBN - (bufferT[i-1].virtualBlockNumber + bufferT[i-1].numberOfContiguousBlocks - 1) != 1){
				fprintf(stderr,"Mapeamento requer bloco virtual nao contiguou ao ultimo mapeado.\n");
				return -1;
			}
			else{
				if (i == 31){
					//Esse é a última tupla disponível nesse registro
					bufferT[i].attributeType = MFT_ADICIONAL;
					newMFT = lookUpMFT();
					if(newMFT <= 0){
						fprintf(stderr,"Disco cheio, impossivel escrever dados.\n");
						return -1;
					}
					bufferT[i].virtualBlockNumber = newMFT;
							// lookUpMFT vai procurar o próximo MFT válido, se for executada sem erros devolve um MFT >0
							// se nao possuir mais MFT disponíveis retorna 0
							// se der erro -1
					write_sector(registerToSector(currentMFT, bufferT);
					read_sector(registerToSector(newMFT), bufferNew);
					bufferNew[0].attributeType = MAPEAMENTO;
					bufferNew[1].attributeType = FIM_ENCADEAMENTO;
					bufferNew[0].virtualBlockNumber = VBN;
					bit = searchBitMap2(0);
					bufferNew[0].logicalBlockNumber = bit;
					*LBN = bit; 
					setBitMap2(bit, 1);
					bufferNew[0].numberOfContiguousBlocks = 1;
					write_sector(registerToSector(newMFT), bufferNew);
					return 0;
				}//fim i==31
				else{
					bit = searchBitMap2(0);
					*LBN = bit;
					setBitMap2(bit, 1);
					if(bufferT[i-1].virtualBlockNumber + bufferT[i-1].numberOfContiguousBlocks + bufferT[i-1].logicalBlockNumber == bit){
						//o bloco é contiguo ao ultimo da tupla
						bufferT[i-1].numberOfContiguousBlocks++;	
						write_sector(registerToSector(currentMFT), bufferT);
						return 0;
					}
					else{
						//precisa de uma nova tupla
						bufferT[i].attributeType = MAPEAMENTO;
						bufferT[i+1].attributeType = FIM_ENCADEAMENTO;
						bufferT[i].virtualBlockNumber = bit - bufferT[i-1].logicalBlockNumber;
						bufferT[i].logicalBlockNumber = bit;
						bufferT[i].numberOfContiguousBlocks = 1;
						write_sector(registerToSector(currentMFT), bufferT);
						return 0;
					}
				}
			}
		}

		if(bufferT[i-1].attributeType == MFT_ADICIONAL){
			currentMFT = bufferT[i-1].virtualBlockNumber;
			j = 0;
		}else{
			j+=1;
		}

		read_sector(registerToSector(currentMFT)+j, bufferT);
	}while(1);


}*/
