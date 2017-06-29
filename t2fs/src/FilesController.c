#include "FilesController.h"
#include "BootController.h"
#include "TuplesController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isValidName(char *name){
    char current;
    int i = 0;
    if(strlen(name) > 51 || strlen(name) < 0) return 1;
    for(i = 0; i<strlen(name); i++) {
        current = name[i];
        if((current < 'A' || current > 'z') && (current <'0' || current > '9') && current != '.') return 1;
    }
    return 0;
}

/*
int allocateBlock(struct t2fs_4tupla *vector){
	int block, newVBN;
	int i = 0, found = 0;
	struct t2fs_4tupla newTuplas;

	block = searchBitmap2(0);
	if(block == 0) return -1;
	if(setBitmap2(block, 1);
	do {
		if(vector[i].atributeType == 0) {
			if(i > 0) i--;
			found = 1;
		}
		else i++;
	}while(i < 32 && !found);

	//Chegou ao fim da cadeia de tuplas
	if(!found) {
		//Tem bloco contíguo
		if(vector[31].logicalBlockNumber + vector[31].numberOfContiguosBlocks == block){
			vector[31].numberOfContiguosBlocks ++;
			return 0;
		}
		
		//Não tem bloco contíguo (aloca um novo registro)
		newVBN = vector[i-1].virtualBlockNumber + vector[i-1].numberOfContiguosBlocks;
		//newTupla(vector, newVBN); //Natáaaaaaalia! Preciso que tu faça essa, pfv
		return 0;
	}

	//Achou o fim da tupla
	//Tem bloco contíguo
	if(vector[i].logicalBlockNumber + vector[i].numberOfContiguosBlocks == block){
		vector[i].numberOfContiguosBlocks ++;
		return 0;
	}
	//Não tem bloco contíguo
	newVBN = vector[i].virtualBlockNumber + vector[i].numberOfContiguosBlocks;
	//newTupla(vector, newVBN);
	return 0;	
}
*/

void printRecords(DWORD reg) {
	int i, j, k;
	struct t2fs_4tupla* tuplas;
	struct t2fs_record* records;

	do {
		i = 0;
		searchMFT(reg, tuplas); //Dá uma falha de segmentação bizarra aqui
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){
					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) break;
					for(k=0; k < ctrl.boot.blockSize; k++) printf("Name: %s\tType: %d\nBlocks: %d\tBytes: %d\n", records[k].name, records[k].TypeVal, records[k].blocksFileSize, records[k].bytesFileSize);
			}
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);
}

//Compila, mas não testei
DWORD searchFile(struct t2fs_record *records, char *name) {
	int i;
	for(i=0; i< 4*ctrl.boot.blockSize; i++){
		if(strcmp(records[i].name, name)) return records[i].MFTNumber;
	}
	return -1;
}

//Compila, mas não testei
int LBNToRecord(DWORD LBN, struct t2fs_record* records){
	int i;
	DWORD index=0;
	DWORD sector;
	//Pega o primeiro setor do LB	
	if(mapLBN(LBN, &sector) < 0) return -1;
	for(i = 0; i < ctrl.boot.blockSize; i++){
		if(read_sector(sector + i, (unsigned char*)(records + index))) return -1;
		index += 4 * sizeof(struct t2fs_record);
	}
	return 0;
}

//Compila, mas não testei
DWORD hasFile(char *directories, DWORD currentReg) {
	struct t2fs_4tupla *tuplas;
	struct t2fs_record *records;
	int i, j;
	DWORD reg;

	reg = currentReg;

	if(directories == NULL) return reg;

	do {
		i = 0;
		searchMFT(reg, tuplas);
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){
					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) return -1;
					reg = searchFile(records, directories);
					if(reg) return hasFile(strtok(NULL, "/"), reg);
			}
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);	
	return -1;
}

//Compila, mas não testei
DWORD pathExists(char *pathName) {
	char *directories;
	directories = strtok(pathName, "/");
	return hasFile(directories, 0);
}
/*
//Função que imprime o conteúdo de um diretório, dado seu setor e tamanho em bytes
//Ainda não testada
int printDirectory(unsigned int sector, DWORD bytesFileSize){
    	unsigned char buffer[SECTOR_SIZE];
	int index = 0;
	int numberOfRegisters, numberOfSectors;
    	t2fs_record current;

	current = malloc(sizeof(t2fs_record));

	
	if(ctrl == NULL){
        	init_lib();
        	return -1;
	}

    	numberOfRegisters = bytesFileSize/64; //Diretórios são sempre múltiplos de 64, logo arredondamento não é necessário.
    numberOfSectors = numberOfRegisters/4;
    if(numberOfRegisters%4 != 0) numberOfSectors++;

    do {
        if(read_sector(0, buffer) != 0){
            fprintf(stderr, "Falha ao ler setor do disco.\n");
            return -1;
        }

        do {
            memcpy(&current.TypeVal, buffer+index, sizeof(BYTE));
            index += sizeof(BYTE);
            memcpy(&current.name, buffer+index, MAX_FILE_NAME_SIZE*sizeof(char));
            index += MAX_FILE_NAME_SIZE*sizeof(char);
            memcpy(&current.blocksFileSize, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            memcpy(&current.bytesFileSize, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            memcpy(&current.MFTNumber, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            printf("Type: %02x\tName: %s\n", current.TypeVal, current.name);
            printf("BlocksFileSize: %4d\tBytesFileSize: %4d\tMFTNumber: %10d\n", current.blocksFileSize, current.bytesFileSize, current.MFTNumber);
            numberOfRegisters --;
        }while(numberOfRegisters != 0 && (numberOfRegisters+1)%4 != 0);
        numberOfSectors --;
    }while(numberOfSectors != 0);
    return 0;
}
*/
