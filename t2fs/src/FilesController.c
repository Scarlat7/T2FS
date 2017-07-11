#include "FilesController.h"
#include "TuplesController.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int readRequestedSectors(FILE2 handle, int size, BYTE *leitura){

	int BLOCK_SIZE = ctrl.boot.blockSize*SECTOR_SIZE;
	DWORD mft = ctrl.openFilesArray[handle].MFT, currentLB, initial_sector;
	DWORD n_blocks = ctrl.openFilesArray[handle].bytesSize/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	DWORD end_pointer = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE);
	DWORD offset = (ctrl.openFilesArray[handle].currentPointer%(ctrl.boot.blockSize*SECTOR_SIZE))/SECTOR_SIZE;

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;

	DWORD remaining = n_sectors;
	int i, j;

	if(remaining == 0)
		return 0;

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

int writeRequestedSectors(FILE2 handle, int size, BYTE *escrita){

	int BLOCK_SIZE = ctrl.boot.blockSize*SECTOR_SIZE;
	DWORD fileSize = ctrl.openFilesArray[handle].bytesSize;
	DWORD mft = ctrl.openFilesArray[handle].MFT, currentLB, initial_sector;
	DWORD n_blocks = (fileSize+updateFileSize(ctrl.openFilesArray[handle], size))/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	DWORD end_pointer = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE);
	DWORD offset = (ctrl.openFilesArray[handle].currentPointer%(ctrl.boot.blockSize*SECTOR_SIZE))/SECTOR_SIZE;

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;

	DWORD remaining = n_sectors;
	int i, j;

	for(i = 0; i < n_blocks-end_pointer; i++){
		mapVBN(mft, i+end_pointer, &currentLB);
		mapLBN(currentLB, &initial_sector);
		for(j = 0; j < (ctrl.boot.blockSize - offset); j++){
			write_sector(initial_sector+offset+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE);
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

	if((newMFT = findMFT()) == ERROR)
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
        if((current < 'A' || current > 'Z') && (current < 'a' || current > 'z') && (current <'0' || current > '9') && current != '.') return 1;
    }
    return 0;
}

int updateRecord(DWORD fatherReg, struct t2fs_record r){

	struct t2fs_record records[RECORDS_IN_SECTOR];
	DWORD LBN, sector;
	DWORD i = 0;
	int j, dirSize, k;

	dirSize = getFileBlockSize(fatherReg);

	do{

		mapVBN(fatherReg, i, &LBN);
		mapLBN(LBN, &sector);

		for(j = 0; j < ctrl.boot.blockSize; j++){
			read_sector(sector+j, (BYTE*) records);
			
			for(k = 0; k < RECORDS_IN_SECTOR; k++){
				if(!strcmp(records[k].name, r.name) && records[k].TypeVal == TYPEVAL_REGULAR){
					records[k] = r;
					write_sector(sector+j, (BYTE *)records);
					return 0;
				}
			}

		}

		i++;
	} while(i < dirSize);

	return -1;

}

int addRecord(DWORD fatherReg, struct t2fs_record *record) {
	struct t2fs_record records[RECORDS_IN_SECTOR];
	DWORD LBN;
	int k, i, j;
	DWORD sector;

	i = 0;

	do{
		mapVBN(fatherReg, i, &LBN);
		mapLBN(LBN, &sector);

		for(j = 0; j < ctrl.boot.blockSize; j++){
			read_sector(sector+j, (BYTE*) records);
			
			for(k = 0; k < RECORDS_IN_SECTOR; k++){
				if(records[k].TypeVal == TYPEVAL_INVALIDO){
					records[k] = *record;

#ifdef DEBUG
	for(i=0; i<ctrl.boot.blockSize; i++){
		printf("Type: %d.\tBlocks: %d\tBytes: %d\tName: %s\n", records[i].TypeVal, records[i].blocksFileSize, records[i].bytesFileSize, records[i].name);
	}
	printf("FatherReg: %d\n", fatherReg);
#endif
					write_sector(sector+j, (BYTE*)records);
					return 0;
				}
			}

		}

		i++;
	} while(1);

	return ERROR;
}

int rmRecord(DWORD fatherReg, struct t2fs_record *record) {
	struct t2fs_record records[RECORDS_IN_SECTOR];
	DWORD LBN, sector;
	DWORD validos = 0, i = 0;
	int j, dirSize, k;

	dirSize = getFileBlockSize(fatherReg);

	do{

		mapVBN(fatherReg, i, &LBN);
		mapLBN(LBN, &sector);

		for(j = 0; j < ctrl.boot.blockSize; j++){
			read_sector(sector+j, (BYTE*) records);
			
			for(k = 0; k < RECORDS_IN_SECTOR; k++){
				if(!strcmp(records[k].name, record->name) && records[k].TypeVal != TYPEVAL_INVALIDO){
					if(read_sector(sector, (unsigned char*) records)) return -1;
					records[k] = *record;
					records[k].TypeVal = TYPEVAL_INVALIDO;
					if(write_sector(sector+j, (unsigned char*)records)) return -1;
					return 0;
				}
				if(records[k].TypeVal > 0 && records[k].TypeVal < 3) validos++;
			}

		}
		i++;
	} while(i < dirSize);
	
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

					if(LBNToRecord(tuplas[i].logicalBlockNumber + j, records)) {
						printf("Incapaz de converter para record.\n");
						return NULL;
					}
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

//Compila
DWORD searchFile(struct t2fs_record *records, char *name) {
	int i;
	for(i=0; i< 4*ctrl.boot.blockSize; i++){
		if(strcmp(records[i].name, name) == 0) return records[i].MFTNumber;
	}
	return -1;
}

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
DWORD hasFile(char *name, DWORD fatherReg, int type) {
	struct t2fs_record records[RECORDS_IN_SECTOR];
	DWORD LBN, sector;
	DWORD i = 0;
	int j, dirSize, k;

	dirSize = getFileBlockSize(fatherReg);

	do{

		mapVBN(fatherReg, i, &LBN);
		mapLBN(LBN, &sector);

		for(j = 0; j < ctrl.boot.blockSize; j++){
			read_sector(sector+j, (BYTE*) records);
			
			for(k = 0; k < RECORDS_IN_SECTOR; k++){
				if(!strcmp(records[k].name, name) && records[k].TypeVal == type){
					return records[k].MFTNumber;
				}
			}

		}

		i++;
	} while(i < dirSize);

	return -1;
}

//Funcionando --- dá pra tirar o *filename
DWORD pathExists(char *pathName) {
	char path[strlen(pathName)+1];
	//Manha pra pegar path até antes do file
	char *ptr;
	strcpy(path, pathName);
	ptr = strrchr(path, '/');
	*ptr = '\0';
	char *directories = strtok(path, "/");
	DWORD reg = 1, i;
	//Verifica se o path até a pasta pai existe
	while(directories){
		i = hasFile(directories, reg, TYPEVAL_DIRETORIO);

		if(reg == ERROR)
			return ERROR;
		reg = i;
		directories = strtok(NULL, "/");
	}
	return reg;
}

int isOpen(char *name, int type){
	int i;

	switch(type) {
		case 1: for(i=0; i < N_OPENFILES; i++)
					if(strcmp(ctrl.openFilesArray[i].name, name) == 0 && ctrl.openFilesArray[i].valid != INVALID_PTR) return i+1;
				break;
		case 2: for(i=0; i < N_OPENDIRECTORIES; i++)
					if(strcmp(ctrl.openDirectoriesArray[i].name, name) == 0 && ctrl.openDirectoriesArray[i].valid != INVALID_PTR) return i+1;
				break;
		default: return -1;
	}
	return 0;
}

OPENFILE getFile(DWORD fatherReg, char *name){
	OPENFILE file;
	struct t2fs_record *record = findRecord(fatherReg, name, -1);
	if(record == NULL || record->TypeVal != TYPEVAL_REGULAR){
		file.valid = -1;
	} 
	else {
		file.valid = 1;
		file.currentPointer = 0;
		file.blocksSize = record->blocksFileSize;
		file.bytesSize = record->bytesFileSize;
		file.MFT = record->MFTNumber;
		file.fatherMFT = fatherReg;
		strcpy(file.name, record->name);
	}	
	return file;
}

OPENDIRECTORY getDir(DWORD fatherReg, char *name) {
	OPENDIRECTORY dir;
	struct t2fs_record *record = findRecord(fatherReg, name, -1);

	if(fatherReg == ROOT_FATHER){
		dir.valid = 1;
		dir.currentEntry = 0;
		dir.blocksSize = getFileBlockSize(fatherReg);
		dir.bytesSize = dir.blocksSize*SECTOR_SIZE*ctrl.boot.blockSize;
		dir.MFT = MFT_ROOT;
		strcpy(dir.name, name);
	}
	else if(record == NULL) {
		dir.valid = -1;
	}
	else {
		dir.valid = 1;
		dir.currentEntry = 0;
		dir.blocksSize = record->blocksFileSize;
		dir.bytesSize = record->bytesFileSize;
		dir.MFT = hasFile(name, fatherReg, TYPEVAL_DIRETORIO);
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
