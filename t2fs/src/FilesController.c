#include "FilesController.h"
#include "TuplesController.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int readRequestedSectors(FILE2 handle, int size, BYTE *leitura, DWORD n_sectors){

	int BLOCK_SIZE = ctrl.boot.blockSize*SECTOR_SIZE;
	DWORD mft = ctrl.openFilesArray[handle].MFT, currentLB, initial_sector;
	DWORD n_blocks = ctrl.openFilesArray[handle].bytesSize/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	DWORD end_pointer = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE);
	DWORD offset = (ctrl.openFilesArray[handle].currentPointer%(ctrl.boot.blockSize*SECTOR_SIZE))/SECTOR_SIZE;

	DWORD remaining = n_sectors;
	int i, j;

	for(i = 0; i < n_blocks-end_pointer; i++){
		mapVBN(mft, i+end_pointer, &currentLB);
		mapLBN(currentLB, &initial_sector);
		for(j = 0; j < (ctrl.boot.blockSize - offset); j++){
			read_sector(initial_sector+ offset+j, leitura+i*BLOCK_SIZE+j*SECTOR_SIZE);
			remaining--;
			if(remaining == 0) break;
		}
		if(remaining == 0) break;
	}

	return 0;
}

DWORD bytesToBlocks(DWORD bytes){
	DWORD BLOCK_SIZE = ctrl.boot.blockSize*SECTOR_SIZE;
	return bytes/BLOCK_SIZE + (bytes%BLOCK_SIZE == 0 ? 0 : 1);

}

int getHandle(int type){
	int i;	
	switch(type) {
		case 1: for(i = 0; i < N_OPENFILES; i++)
			if(ctrl.openFilesArray[i].valid == -1) return i;
			break;
		case 2: for(i = 0; i < N_OPENDIRECTORIES; i++)
			if(ctrl.openDirectoriesArray[i].valid == -1) return i;
			break;
		default: return -1;
	}
	printf("NUMERO DE ARQUIVOS OU DIRETORIOS ABERTOS EXCEDIDO\n"); 	
	return -1;
}

/*
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

struct t2fs_record* getRecordsFile(char *path){
	char *directorie;
	char *dummy = malloc(sizeof(path));
	struct t2fs_record* actualRecord = malloc(sizeof(struct t2fs_record));
	BYTE *sectors;
	sectors = (BYTE*)malloc(ctrl.boot.blockSize*SECTOR_SIZE);
	int i, j;
	strcpy(dummy, path);
	DWORD rootBlocks = getFileBlockSize(1);
	DWORD currentLB, initial_sector;
	puts("b");
	printf("RB: %d\n", rootBlocks);
	directorie = strtok(dummy, "/");
	printf("%d", registerToSector(12));
	for(i = 0; i < rootBlocks; i++){
		puts("a");
		mapVBN(1, i, &currentLB);
		printf("LB: %d\n", currentLB);
		//if(mapLBN(currentLB, &initial_sector) == ERROR)
		//	return NULL;
		
		initial_sector = currentLB*ctrl.boot.blockSize;
		printf("IS: %d\n", initial_sector);
		
		for(j = 0; j < ctrl.boot.blockSize; j++){		
			read_sector(initial_sector+j, sectors+SECTOR_SIZE*j);
		}
		
		puts("c");

		if((actualRecord = getRecordByName(directorie, sectors)) != NULL)
			break;
	}
	
	if(actualRecord == NULL)	
		return NULL;

	if(actualRecord->TypeVal == 1)
		return actualRecord;
	puts("e");
	while((directorie = strtok(NULL, "/"))){
		for(i = 0; i < actualRecord->blocksFileSize; i++){
			mapVBN(actualRecord->MFTNumber,i, &currentLB);

			initial_sector = currentLB*ctrl.boot.blockSize;

			for(j = 0; j < ctrl.boot.blockSize; j++){
				read_sector(initial_sector+j, sectors+SECTOR_SIZE*j);
			}
			puts("g");
			if((actualRecord = getRecordByName(directorie, sectors)) != NULL)
				break;
		}
		if(actualRecord->TypeVal == 1)
			return actualRecord;
	}
	return NULL;
}

struct t2fs_record* getRecordByName(char *name, BYTE *sectors){
	int RECORD_SIZE = sizeof(struct t2fs_record);	
	int N_RECORDS = SECTOR_SIZE/RECORD_SIZE;
	int i;
	for(i = 0; i < sizeof(sectors); i++){
		printf("%c", *(sectors+i));
	}
	struct t2fs_record* actual_record = malloc(RECORD_SIZE);
	
	for(i = 0; i < N_RECORDS; i++){
		memcpy(actual_record, sectors+RECORD_SIZE*i, RECORD_SIZE);
		puts(actual_record->name);
		if(strcmp(actual_record->name, name) == 0)
			return actual_record; 
	}
	return NULL;
}
*****************************************************/
DWORD updateFileSize(OPENFILE file, DWORD size){
	int offset = file.currentPointer + size;

	if(offset > file.bytesSize)
		return offset - file.bytesSize;

	return 0;
}

char* getFileName(char *filename){
	char *ptr;
	ptr = strrchr(filename, '/');
	if(ptr)
		return ptr+1;
	else return NULL;
}



struct t2fs_record* createFile(char* name, short int typeVal){
	struct t2fs_record* newRecord = malloc(sizeof(struct t2fs_record));
	DWORD newMFT, LBN;

	if((newMFT = findMFT()) <= 0)
		return NULL;

	if(mapVBN(newMFT, 0, &LBN) < 0)
		return NULL;

	newRecord->TypeVal = typeVal;
	strcpy(newRecord->name, name);
	newRecord->blocksFileSize = 1;
	newRecord->bytesFileSize = 0;
	newRecord->MFTNumber = newMFT;	
	
	return newRecord;
}

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

int addRecord(DWORD fatherReg, struct t2fs_record *record) {
	int j, i, desloc, lastFound = 0;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record records[ctrl.boot.blockSize*4];
	struct t2fs_record recSec[4];
	DWORD nextReg, newVBN, LBN, sector;
	nextReg = fatherReg;
	do {
		j = 0;
		searchMFT(nextReg, tuplas);
		//Procura pela última tupla do pai
		while(tuplas[j].atributeType == 1){
			j++;
		}
		if(tuplas[j].atributeType == 0) {
			if(j > 0) j--;
			//Pega o último VBN
			newVBN = tuplas[j].virtualBlockNumber + tuplas[j].numberOfContiguosBlocks - 1;
			
		}
		nextReg = tuplas[31].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);
	//Atualiza registro MFT do pai
	if(mapVBN(fatherReg, newVBN, &LBN)) return -1;
	//Pega records desse LBN e chega até o fim
	if(LBNToRecord(LBN, records)) return -1;
	j = 0;
	do {
		if(records[j].TypeVal > 0 && records[j].TypeVal < 3) j++;
		else lastFound = 1;
	}while(lastFound == 0);
	
	//Mapeia LBN para setor de início
	if(mapLBN(LBN, &sector)) return -1;
	
	desloc = j / 4;
	if(read_sector(sector + desloc, (unsigned char*) recSec)) return -1;
	recSec[j%4] = *record;

#ifdef DEBUG
	for(i=0; i<4; i++){
		printf("Type: %d.\tBlocks: %d\tBytes: %d\tName: %s\n", recSec[i].TypeVal, recSec[i].blocksFileSize, recSec[i].bytesFileSize, recSec[i].name);
	}
#endif
	//Escreve o record adicionado logo abaixo do último
	if(write_sector(sector + desloc, (unsigned char*)recSec)) return -1;
	return 0;
}

int rmRecord(DWORD fatherReg, struct t2fs_record *record) {
	int i, j, k, desloc;
	DWORD sector, reg = fatherReg;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record *records = malloc(ctrl.boot.blockSize*4*sizeof(struct t2fs_record));
	struct t2fs_record *recSec = malloc(4*sizeof(struct t2fs_record));

	if(reg == -1) return -1;
	do {
		i = 0;
		searchMFT(reg, tuplas);
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){

					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) return -1;
					for(k=0; k < ctrl.boot.blockSize*4; k++){
							if(strcmp(records[k].name, record->name) == 0) {
								mapLBN(tuplas[i].logicalBlockNumber + j, &sector);
								desloc = k / 4;
								if(read_sector(sector + desloc, (unsigned char*) recSec)) return -1;
							recSec[k%4] = *record;
							recSec[k%4].TypeVal = 0;
							if(write_sector(sector + desloc, (unsigned char*)recSec)) return -1;
							return 0;
							}
					}
			}			
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);
	return -1;
}

int hasAnyFile (DWORD reg) {
	int i, j, k;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record *records = malloc(ctrl.boot.blockSize*4*sizeof(struct t2fs_record));

	if(reg == -1) return -1;
	do {
		i = 0;
		searchMFT(reg, tuplas);
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){

					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) return -1;
					for(k=0; k < ctrl.boot.blockSize*4; k++){
						if(records[k].TypeVal == 1 || records[k].TypeVal == 2) return 1;
					}
			}			
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);
	return 0;
}

struct t2fs_record* findRecord(DWORD reg, char *name, DWORD entry) {
	int i, j, k, l=0;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record *records = malloc(ctrl.boot.blockSize*4*sizeof(struct t2fs_record));

	if(reg == -1) return NULL;
	do {
		i = 0;
		searchMFT(reg, tuplas);
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){

					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) return NULL;
					for(k=0; k < ctrl.boot.blockSize*4; k++){
						if(entry == -1 && strcmp(records[k].name, name) == 0) return &records[k];
						if(records[k].TypeVal == 1 || records[k].TypeVal == 2){
							if(entry != -1 && l == entry) return &records[k];
							l++; //conta registros válidos
						}
					}
			}			
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);
	return NULL;
}

void printRecords(DWORD reg){
	int i, j, k;
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record records[ctrl.boot.blockSize*4];
	if(reg == -1) return;
	do {
		i = 0;
		searchMFT(reg, tuplas); 
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){
					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) break;
					for(k=0; k < ctrl.boot.blockSize*4; k++) printf("Name: %s\tType: %d\tBlocks: %d\tBytes: %d\n", records[k].name, records[k].TypeVal, records[k].blocksFileSize, records[k].bytesFileSize);
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
		if(strcmp(records[i].name, name) == 0) return records[i].MFTNumber;
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

//Funcionando
DWORD hasFile(char *directories, DWORD currentReg) {
	struct t2fs_4tupla tuplas[32];
	struct t2fs_record records[ctrl.boot.blockSize*4];
	int i, j;
	DWORD reg;

	reg = currentReg;

	do {
		i = 0;
		searchMFT(reg, tuplas);
		do {
			for(j = 0; j < tuplas[i].numberOfContiguosBlocks; j++){
					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) return -1;
					reg = searchFile(records, directories);
					if(reg) return reg;
			}
			i++;
		}while(tuplas[i].atributeType == 1);
		reg = tuplas[i].virtualBlockNumber;
	}while(tuplas[31].atributeType == 2);	
	return -1;
}

//Funcionando
DWORD pathExists(char *pathName, char *fileName) {
	char path[strlen(pathName)+1];
	strcpy(path, pathName);
	char *directories = strtok(path, "/");
	DWORD reg = 1, i;
	//Verifica se o path até a pasta pai existe
	while(directories && strcmp(directories, fileName)){
		i = hasFile(directories, reg);
		reg = i;
		directories = strtok(NULL, "/");
	}
	return reg;
}

int isOpen(char *name, int type){
	int i;

	switch(type) {
		case 1: for(i=0; i < N_OPENFILES; i++)
			if(strcmp(ctrl.openFilesArray[i].name, name) == 0) return i+1;
			break;
		case 2: for(i=0; i < N_OPENDIRECTORIES; i++)
			if(strcmp(ctrl.openDirectoriesArray[i].name, name) == 0) return i+1;
			break;
		default: return -1;
	}
	return 0;
}

OPENFILE getFile(DWORD fatherReg, char *name){
	OPENFILE file;
	struct t2fs_record *record = findRecord(fatherReg, name, -1);
	if(record == NULL) printf("Deu ruim no findRecord.\n");
	else {
		file.valid = 1;
		file.currentPointer = 0;
		file.blocksSize = record->blocksFileSize;
		file.bytesSize = record->bytesFileSize;
		file.MFT = record->MFTNumber;
		strcpy(file.name, record->name);
	}	
	return file;
}

OPENDIRECTORY getDir(DWORD fatherReg, char *name) {
	OPENDIRECTORY dir;
	struct t2fs_record *record = findRecord(fatherReg, name, -1);
	if(record == NULL) printf("Deu ruim no findRecord.\n");
	else {
		dir.valid = 1;
		dir.currentEntry = 0;
		dir.blocksSize = record->blocksFileSize;
		dir.bytesSize = record->bytesFileSize;
		dir.MFT = hasFile(name, fatherReg);
		strcpy(dir.name, record->name);
	}	
	return dir;
}

int isOpenH(int handle, int type) {
	switch(type) {
		case 1: if(ctrl.openFilesArray[handle].valid != -1) return 1;
			break;
		case 2: if(ctrl.openDirectoriesArray[handle].valid != -1) return 1;
			break;
		default: return -1;
	}
	return 0;
}
