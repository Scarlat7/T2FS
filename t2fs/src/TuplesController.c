#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"
#include "apidisk.h"
#include "bitmap2.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_control ctrl;

int mapLBN(DWORD LBN, DWORD* sector){
	//DWORD base;
	//base = (1 + ctrl.boot.MFTBlocksSize)*ctrl.boot.blockSize;
	//*sector = base + LBN * ctrl.boot.blockSize;
	*sector = LBN*ctrl.boot.blockSize;
	//if(*sector > ctrl.boot.diskSectorSize) return -1;
	if(*sector >= ctrl.boot.diskSectorSize) return -1;
	return 0;
}

int searchMFT(DWORD numReg, struct t2fs_4tupla *vector) {
 	if(read_sector(ctrl.boot.blockSize + 2*numReg, (unsigned char*)vector)) return -1;
	if(read_sector(ctrl.boot.blockSize + 1 + 2*numReg, (unsigned char*)vector + SECTOR_SIZE)) return -1;
	
	return 0;
}

/*
int readSectorFile(FILE2 fileHandle, int nSectors, BYTE* buffer) {
	
	DWORD sector, currentMFT;
	DWORD startVirtualBlock, block;
	int k, offset;
	int remaining = 0;
	int index = 0;
	BYTE bufferS[SECTOR_SIZE];
	t2fs_4tupla bufferT[TUPLES_IN_REG];
	DWORD LBN;

	currentMFT = ctrl.OpenFilesArray[fileHandle].MFT;

	searchMFT(curentMFT, bufferT);
	
	startVirtualBlock = ctrl.OpenFilesArray[fileHandle].currentPointer/ctrl.boot.blockSize;	
	
	offset = (ctrl.OpenFilesArray[fileHandle].currentPointer%ctrl.boot.blockSize)/SECTOR_SIZE;	
	
	if(ctrl.OpenFilesArray[fileHandle].size/SECTOR_SIZE+1 < offset + nSectors){
		fprintf(stderr,"Numero de setores requisitados eh maior do que o arquivo.\n");
		return ERROR;
	}

	k = 0;

	while(remaining != nSectors){

		if(mapVBN(currentMFT, startVirtualBlock+k, &LBN) != 0){
			return ERROR;
		}			
	
		mapLBN(LBN, &sector);
				
		//percorre até o fim desse bloco
		while(sector%ctrl.boot.blockSize != 0 && remaining != nSector){	
			//primeiro bloco pode ter apenas uma parte
			if(!remaining){
				sector +=  offset;
			}else sector++;
			if(read_sector(sector, buffer+index) != 0)
				return ERROR;
			remaining++;
			index+=SECTOR_SIZE;
		}
		k++;
	}

	return 0;

lllllllllllllllllllll
		//loop de leitura do buffer de tuplas de um setor
		while(i < TUPLES_IN_REG && remaining != nSectors){
			if(bufferT[i].atributeType == MAPEAMENTO){
				if(isInRange(startVirtualBlock, bufferT[i])){
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

} */
 
int registerToSector(DWORD MFT){

	if(MFT > ((ctrl.boot.MFTBlocksSize*ctrl.boot.blockSize)/SECTORS_IN_REG - 1) || MFT < 0){
		fprintf(stderr, "Registro MFT requisitado fora dos limites.\n");
		return -1;
	}

	return ctrl.boot.blockSize + MFT*SECTORS_IN_REG;

}


int mapVBN(DWORD MFT, DWORD VBN, DWORD* LBN) {
	
	struct t2fs_4tupla bufferT[TUPLES_IN_REG], bufferNew[TUPLES_IN_REG/2];

	int i;
	DWORD currentMFT = MFT, newMFT;
	int bit;	

	searchMFT(MFT, bufferT);
	
	if(bufferT[0].atributeType == INVALID_PTR && VBN != 0){
		fprintf(stderr,"MFT invalido para mapeamento.\n");
		return -1;
	}
	else if(bufferT[0].atributeType == INVALID_PTR && VBN == 0){
		//This MFT is new
		bufferT[0].atributeType = MAPEAMENTO;
		bufferT[0].virtualBlockNumber = VBN;
		bit = searchBitmap2(0);
		if(bit > 0){
			bufferT[0].logicalBlockNumber= bit;
			*LBN = bit;
			setBitmap2(bit, 1);
		}else{
			fprintf(stderr, "Bitmap nao pode mapear bloco.\n");
			return -1;
		}
		bufferT[0].numberOfContiguosBlocks = 1;
		bufferT[1].atributeType = FIM_ENCADEAMENTO;
		write_sector(registerToSector(currentMFT), (BYTE*) bufferT);
#ifdef DEBUG
		printf("PRIMEIRA TUPLA do registro %d.\n", currentMFT);
		printf("\tTupla 0: type: %d VBN: %u LBN: %u contiguous: %d\n",bufferT[0].atributeType,bufferT[0].virtualBlockNumber,
			bufferT[0].logicalBlockNumber,bufferT[0].numberOfContiguosBlocks);
		printf("\tTupla 1: type: %d\n", bufferT[1].atributeType); 
#endif
		return 0;		
	}

	do{
		i = 0;
		while(i < TUPLES_IN_REG  && bufferT[i].atributeType != FIM_ENCADEAMENTO){
			//se o VBN procurado está mapeado nessa tupla
			if(bufferT[i].atributeType == MAPEAMENTO){
#ifdef DEBUG
				//printf("Verificar se VBN esta no RANGE da tupla.\n");
				//printf("\ttupla: VBN %u cont: %d range: %d\n", bufferT[i].virtualBlockNumber, bufferT[i].numberOfContiguosBlocks,
				//	bufferT[i].virtualBlockNumber + bufferT[i].numberOfContiguosBlocks-1);
				//printf("\tVBN procurada %u\n",VBN);
#endif
				if(isInRange(VBN, bufferT[i])){
					*LBN = (VBN  - bufferT[i].virtualBlockNumber) + bufferT[i].logicalBlockNumber;
					return 0;
				}
			}
			i++;
		}		
	
		//Achou o lugar onde deve começar a mapeamento do próximo
		if(i < TUPLES_IN_REG && bufferT[i].atributeType == FIM_ENCADEAMENTO){
			if(!isSequential(VBN, bufferT[i-1])){
				fprintf(stderr,"Mapeamento requer bloco virtual nao contiguou ao ultimo mapeado.\n");
				return -1;
			}
			if (i == TUPLES_IN_REG-1){
				//Esse é a última tupla disponível nesse registro
				bufferT[i].atributeType = MFT_ADICIONAL;
				newMFT = findMFT();
				if(newMFT <= 0){
					fprintf(stderr,"Disco cheio, impossivel escrever dados.\n");
					return -1;
				}
				bufferT[i].virtualBlockNumber = newMFT;
						// lookUpMFT vai procurar o próximo MFT válido, se for executada sem erros devolve um MFT >0
						// se nao possuir mais MFT disponíveis retorna 0
						// se der erro -1
				writeRegister(currentMFT, bufferT);
				read_sector(registerToSector(newMFT), (BYTE*)bufferNew);
				bufferNew[0].atributeType = MAPEAMENTO;
				bufferNew[1].atributeType = FIM_ENCADEAMENTO;
				bufferNew[0].virtualBlockNumber = VBN;
				bit = searchBitmap2(0);
				bufferNew[0].logicalBlockNumber = bit;
				*LBN = bit; 
				setBitmap2(bit, 1);
				bufferNew[0].numberOfContiguosBlocks = 1;
				write_sector(registerToSector(newMFT), (BYTE*) bufferNew);
#ifdef DEBUG
				printf("MAPEAMENTO NOVO BLOCO\n");
#endif
				return 0;
			}//fim i==TUPLES_IN_REG-1
			else{
				bit = searchBitmap2(0);
				*LBN = bit;
				setBitmap2(bit, 1);
					
				if(isContiguous(bit, bufferT[i-1])){
					bufferT[i-1].numberOfContiguosBlocks++;	
					writeRegister(currentMFT, bufferT);
#ifdef DEBUG
					printf("MAPEAMENTO CONTIGUO:\n"); 
					printf("\tTupla num %d modificada do registro %d\n", i-1, currentMFT);
					printf("\ttupla: type %d VBN %u LBN %u cont %d\n", bufferT[i-1].atributeType,bufferT[i-1].virtualBlockNumber, 
						bufferT[i-1].logicalBlockNumber, bufferT[i-1].numberOfContiguosBlocks);
#endif
					return 0;
				}
				//precisa de uma nova tupla
				bufferT[i].atributeType = MAPEAMENTO;
				bufferT[i].virtualBlockNumber = VBN; 
				bufferT[i].logicalBlockNumber = bit;
				bufferT[i].numberOfContiguosBlocks = 1;
	
				bufferT[i+1].atributeType = FIM_ENCADEAMENTO;
				writeRegister(currentMFT, bufferT);
#ifdef DEBUG
				printf("MAPEAMENTO NOVA TUPLA:\n"); 
				printf("\tTupla num %d (anterior):type %d VBN %u LBN %u cont %d\n", i, bufferT[i].atributeType,
					bufferT[i].virtualBlockNumber, bufferT[i].logicalBlockNumber, bufferT[i].numberOfContiguosBlocks);
				printf("\tTupla num %d (proxima):type %d\n", i+1, bufferT[i+1].atributeType);
#endif					
				return 0;	
			}
		}
	
		if(bufferT[i-1].atributeType == MFT_ADICIONAL){
			currentMFT = bufferT[i-1].virtualBlockNumber;
			searchMFT(currentMFT, bufferT);
#ifdef DEBUG
			printf("INDO PARA PROXIMO BLOCO.\n");
#endif
		}
	}while(1);

	return 0;
}

DWORD findMFT(){

	int i;
	struct t2fs_4tupla buffer[SECTOR_SIZE];	

	//Loop starts at 4 because MFT register 0 to 4 are reserved to the file system
	for(i = 4; i < ctrl.boot.MFTBlocksSize; i++){
		
		if(read_sector(registerToSector(i), (BYTE*)buffer) != 0){
			fprintf(stderr, "Failed to read MFT register %d in sector %d.\n", i, registerToSector(i));
			return -1;
		}
		
		if(buffer[0].atributeType == INVALID_PTR) return i;
	}

	fprintf(stderr, "Disk is full, impossible to find a MFT register.\n");
	return 0;
}

int getFileBlockSize(DWORD MFT){

	int i, counter = 0;
	DWORD currentMFT = MFT;
	struct t2fs_4tupla buffer[TUPLES_IN_REG];

	do{
		searchMFT(currentMFT,buffer);
		i = 0;
		while(i < TUPLES_IN_REG){
	
			if(buffer[i].atributeType == MAPEAMENTO){
				counter+=buffer[i].numberOfContiguosBlocks;
			}
			else if(buffer[i].atributeType == FIM_ENCADEAMENTO){
				return counter;
			}
			else if(buffer[i].atributeType == INVALID_PTR){
				return 0;
			}
			i++;
		}

		if(buffer[i-1].atributeType == MFT_ADICIONAL){
			currentMFT = buffer[i].virtualBlockNumber;
		}
	}while(1);

	return -1;
}

int isContiguous(int bit, struct t2fs_4tupla t){

	if (t.numberOfContiguosBlocks + t.logicalBlockNumber == bit){
		return 1;
	}else return 0;
}

int isSequential(DWORD VBN, struct t2fs_4tupla t){

	if(VBN - (t.virtualBlockNumber + t.numberOfContiguosBlocks - 1) != 1){
		return 0;
	}else return 1;

}

int isInRange(DWORD VBN, struct t2fs_4tupla t){

	if((t.virtualBlockNumber + t.numberOfContiguosBlocks-1) >= VBN && t.virtualBlockNumber <= VBN){
		return 1;
	} else return 0;
}

int writeRegister(DWORD MFT, struct t2fs_4tupla* bufferT){

	if(write_sector(registerToSector(MFT), (BYTE*) bufferT) != 0) return ERROR;
	if(write_sector(registerToSector(MFT)+1, (BYTE*) bufferT+SECTOR_SIZE) != 0) return ERROR;

	return 0;
}
