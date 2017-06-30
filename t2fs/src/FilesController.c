#include "FilesController.h"
#include "BootController.h"
#include "TuplesController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/******************************************
	COMENTEI PRA NÃO ZOAR A COMPILAÇÃO
void init_openFilesArray(){
	int i = 0;
	for(i = 0; i < N_OPENFILES; i++){
		openFilesArray[i] = -1;
	}
}

int getFileNumber(){
	int i;	
	for(i = 0; i < N_OPENFILES; i++){
		if(openFilesArray[i] == -1){
			return i;		
		}
	}
	printf("NUMERO DE ARQUIVOS ABERTOS EXCEDIDO\n"); 	
	return -1;
}


int openFile(char *path){
	struct t2fs_records fileRecord;
	if(isOpen(path)) return ERROR;
		
	OPENFILES newFile;
	int fileNumber;

	fileRecord = getRecordsFile(path);

	newFile.MFT = fileRecord.MFTNumber;
	newFile.currentPointer = 0;
	strcpy(fileRecord.name, path);	
	newFile.size = fileRecord.bytesFileSize;

	if((fileNumber = getFileNumber())){
		openFilesArray[fileNumber] = newFile;
		return fileNumber;
	}

	else return ERROR;
}

struct t2fs_records getRecordsFile(char *path){
	char *directorie;
	struct t2fs_records actualRecord;
	BYTE sectors = malloc(sectorsInBlock*SECTOR_SIZE);
	int i, j;
	DWORD rootBlocks = getRootBlocks();
	DWORD currentLB;
	
	directorie = strtok(path, "/");	

	for(i = 0; i < rootBlocks; i++){
		currentLB = mapVBN(1, i);
		initial_sector = blockToSector(currentLB);
		for(j = 0; j < sectorsInBlock; j++){		
			read_sector(initial_sector+j, sectors);
			sectors+=SECTOR_SIZE;
		}
		
		if(actualRecord = getRecordByName(directorie, sectors))
			break;
	}

	if(actualRecord.TypeVal == 1)
		return actualRecord;
	 
	while((directorie = strtok(NULL, "/")){
		for(i = 0; i < actualRecord.blocksFileSize; i++){
			currentLB = mapVBN(actualRecord.MFTNumber,i);
			initial_sector = blockToSector(currentLB);
			for(j = 0; j < sectorsInBlock; j++){
				read_sector(initial_sector+j, sectors);
				sectors+=SECTOR_SIZE;
			}
			if(actualRecord = getRecordByName(directorie, sectors))
				break;
		}

		if(actualRecord.TypeVal == 1)
			return actualRecord;
	}

	return ERROR;
}

struct t2fs_records getRecordByName(char *name, BYTE *sectors){
	int RECORD_SIZE = sizeof(struct t2fs_records);	
	int N_RECORDS = SECTOR_SIZE/RECORD_SIZE;
	struct t2fs_records actual_record;
	int i;
	for(i = 0; i < N_RECORDS; i++){
		memcpy(&actual_record, sectors+RECORD_SIZE*i, RECORD_SIZE)
		if(strcmp(actual_record.name, name) == 0)
			return actual_record; 
	}

	return NULL;
}

*****************************************************/
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

void printRecords(DWORD reg){
	int i, j, k;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record records[ctrl.boot.blockSize*4];

	do {
		i = 0;
		searchMFT(reg, tuplas); 
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

//Dá seg fault quando testada separada, mas funciona quando chamada
int LBNToRecord(DWORD LBN, struct t2fs_record* records){
	int i;
	DWORD index=0;
	DWORD sector;
	//Pega o primeiro setor do LB
	if(mapLBN(LBN, &sector) < 0) return -1;
	for(i = 0; i < ctrl.boot.blockSize; i++){
		if(read_sector(sector + i, (unsigned char*)records + index)) return -1;
		index += 4 * sizeof(struct t2fs_record);
	}
	return 0;
}

//Compila, mas não testei
DWORD hasFile(char *directories, DWORD currentReg) {
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record records[ctrl.boot.blockSize*4];
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
