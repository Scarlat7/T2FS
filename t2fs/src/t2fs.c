﻿#include "FilesController.h"
#include "TuplesController.h"
#include "apidisk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************
int seek2 (FILE2 handle, DWORD offset){
	if(fileIsOpen(handle))
		openFilesArray[handle].currentPointer += offset;
	else return ERROR;

	return 0;
}

int read2 (FILE2 handle, char *buffer, int size){
	BYTE *bufferAux;
	DWORD sectors = bytesToSectors(size);
	DWORD relativeByte = openFilesArray[handle].currentPointer % SIZE_SECTOR;	
	
	bufferAux = malloc(sectors*sizeof(BYTE));

	if(readSectorFile(handle, sectors, bufferAux))
		memcpy(buffer, bufferAux+relativeByte, size);
	else return ERROR;	
}
*/
int write2(FILE2 handle, char *buffer, int size){
	BYTE *escrita;	
	int i, j;
	int BLOCK_SIZE = ctrl.boot.blockSize*SECTOR_SIZE;
	DWORD mft = ctrl.openFilesArray[handle].MFT, currentLB, initial_sector;
	DWORD n_blocks = ctrl.openFilesArray[handle].bytesSize/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	DWORD end_pointer = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE);
	DWORD relativeByte = ctrl.openFilesArray[handle].currentPointer % SECTOR_SIZE;
	DWORD offset = (ctrl.openFilesArray[handle].currentPointer%(ctrl.boot.blockSize*SECTOR_SIZE))/SECTOR_SIZE;

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;

	escrita = malloc(n_sectors*SECTOR_SIZE);
	int remaining = n_sectors;


	for(i = 0; i < n_blocks-end_pointer; i++){
		mapVBN(mft, i+end_pointer, &currentLB);
		mapLBN(currentLB, &initial_sector);
		for(j = 0; j < (ctrl.boot.blockSize - offset); j++){
			read_sector(initial_sector+ offset+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE);
			remaining--;
			if(remaining == 0) break;
		}
		if(remaining == 0) break;
	}

	memcpy(escrita+relativeByte, buffer, size);

	remaining = n_sectors;
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

	ctrl.openFilesArray[handle].bytesSize += updateFileSize(ctrl.openFilesArray[handle], size);
	ctrl.openFilesArray[handle].currentPointer += size;
	ctrl.openFilesArray[handle].blocksSize = bytesToBlocks(ctrl.openFilesArray[handle].bytesSize);

	return size;
}

FILE2 create2 (char *filename){
	char *name;
	struct t2fs_record* newRecord; // Tirei isso porque já tem malloc dentro da fnção createFile = malloc(sizeof(struct t2fs_record));
	DWORD mftDir;
	FILE2 handle;

	if((name = getFileName(filename)) == NULL)
		return ERROR;
		
	if((mftDir = pathExists(filename, name)) <= 0)
		return ERROR;

	if(hasFile(name, mftDir) != ERROR)
		return ERROR;

	if((newRecord = createFile(name, 1)) == NULL)
		return ERROR;

	if(addRecord(mftDir, newRecord))
		return ERROR;
	
	free(newRecord);

	if((handle = getHandle(1)) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle] = getFile(mftDir, name);
	
	return handle;
	
}

int mkdir2 (char *pathname){
	int i;
	char *last = strrchr(pathname, '/');
	char dirName[strlen(last+1)];
	struct t2fs_record newRecord;
	DWORD  fatherReg, newReg, LBN;

	//Pega última palavra
	if(last == NULL) return -1;
	strcpy(dirName, last+1);
	
	//Procura pelo pai
	fatherReg = pathExists(pathname, dirName);
	//Se a pasta já existe, retorna erro
	if(hasFile(dirName, fatherReg) != -1) return -1;

	if(fatherReg > 0) {
		newReg = findMFT();
		if(newReg <= 0) return -1;
		//Atualiza registro MFT recém criado
		if(mapVBN(newReg, 0, &LBN)) return -1;

		//Cria novo record
		newRecord.TypeVal = 2;
		strcpy(newRecord.name, dirName);

		//Vocês estão prontas para a gambiarra, crianças?
		for(i=strlen(dirName); i<MAX_FILE_NAME_SIZE; i++) newRecord.name[i]='\0';

		newRecord.blocksFileSize = 1;
		newRecord.bytesFileSize = ctrl.boot.blockSize*SECTOR_SIZE;
		newRecord.MFTNumber = newReg;

		//Para fins de debug
		printf("Name: %s\tType: %d\tBlocks: %d\tBytes:%d\tMFT: %d\n", newRecord.name, newRecord.TypeVal, newRecord.blocksFileSize, newRecord.bytesFileSize, newRecord.MFTNumber);

		if(addRecord(fatherReg, &newRecord)) return -1;
		return 0;
	}
	return -1;
}
/***********************************************************
int rmdir2 (char *pathname){
	char *last = strrchr(pathname, '/');
	char dirName[MAX_FILE_NAME_SIZE];
	DWORD  fatherReg, dirReg;
	struct t2fs_record record;

	//Pega última palavra
	if(last == NULL) return -1;
	strcpy(dirName, last+1);
	
	//Procura pelo pai
	fatherReg = pathExists(pathname, dirName);
	dirReg = hasFile(dirName, fatherReg);
	//Se a pasta não existe, retorna erro
	if(dirReg <= 0) return -1;

	if(fatherReg > 0) {
		//Verifica se está vazio
		//Pega o record
		//Reduz blockSize do pai
		//Invalida no disco		
	}
	return -1;
}
**************************************************************/

DIR2 opendir2 (char *pathname) {
	int newHandle;
	char *dirName = getFileName(pathname);
	DWORD fatherReg = pathExists(pathname, dirName);
	
	//Verifica se diretório existe
	if(fatherReg <= 0) return -1;
	if(hasFile(dirName, fatherReg) == -1) return -1;
	//Verifica se está aberto
	if(isOpen(pathname, 2)) return -1; //Working
	//Verifica se há espaço
	newHandle = getHandle(2);
	if(newHandle == -1) return -1;
	ctrl.openDirectoriesArray[newHandle] = getDir(fatherReg, dirName);
	return newHandle;
}

/*************************************************************
int readdir2 (DIR2 handle, DIRENT2 *dentry) {
	char *recordName;
	struct t2fs_record *record = malloc(sizeof(struct t2fs_record));
	if(isOpenH(handle, 2) != 1) return -2;
	//Busca pelo record apontado por reader.currentEntry
	//Criar função que, com base no reader.currentEntry e no reader.MFT,
	//retorna um nome válido para pesquisar via findRecord
	recordName = getRecordName(ctrl.openDirectoriesArray[handle].MFT, ctrl.openDirectoriesArray[handle].currentEntry);
	if(recordName == NULL) return -2; //Caso não exista
	if(strcmp(recordName, "")) return -1;	//Caso tenha acabado
	record = findRecord(ctrl.openDirectoriesArray[handle].MFT, recordName);
	//Converter record -> dirent2
	ctrl.openDirectoriesArray[handle].currentEntry ++;
	free(record);
	return 0;
}

*************************************************************/
