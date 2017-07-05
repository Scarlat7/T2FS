#include "FilesController.h"
#include "TuplesController.h"
#include "apidisk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int delete2 (char *filename){

	/*
	char* name;
	DWORD fatherDir, fileReg;

	if((name = getFileName(filename)) == NULL)
		return ERROR;

	if((fatherDir = pathExists(filename, name)) <= 0)
		return ERROR;

	getRecord(filename, &record);

	if(deleteBlocks(record.mft,record.blocksFileSize) == ERROR)
		return ERROR;

	deleteFileRecord(filename);

	*/

	return ERROR;
}

int truncate2 (FILE2 handle){

	DWORD n_blocks = ctrl.openFilesArray[handle].bytesSize/(ctrl.boot.blockSize*SECTOR_SIZE)+1;	
	DWORD end_block = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	int delete_blocks = n_blocks - end_block;

	if(!isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR)) 
		return ERROR;

	if(deleteBlocks(ctrl.openFilesArray[handle].MFT, &delete_blocks) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle].bytesSize = ctrl.openFilesArray[handle].currentPointer;

	return 0;
}

int seek2 (FILE2 handle, DWORD offset){
	
	if(!isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR)) 
		return ERROR;
	
	if(offset == END){
		ctrl.openFilesArray[handle].currentPointer = ctrl.openFilesArray[handle].bytesSize;
	}else{
		if(offset > ctrl.openFilesArray[handle].bytesSize){
			return ERROR;
		}
		ctrl.openFilesArray[handle].currentPointer = offset; 
	}

	return 0;
}


int read2 (FILE2 handle, char *buffer, int size){
	
	BYTE *leitura;
	DWORD relativeByte = ctrl.openFilesArray[handle].currentPointer % SECTOR_SIZE;
	DWORD actualReadSize = size;

	if(!isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR)) 
		return ERROR;
	if(ctrl.openFilesArray[handle].currentPointer + size > ctrl.openFilesArray[handle].bytesSize){
		actualReadSize = ctrl.openFilesArray[handle].bytesSize - ctrl.openFilesArray[handle].currentPointer;
	}

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;

	leitura = malloc(n_sectors*SECTOR_SIZE);

	if(readRequestedSectors(handle, actualReadSize, leitura, n_sectors) == ERROR) return ERROR;

	/*for(i = 0; i < n_blocks-end_pointer; i++){
		mapVBN(mft, i+end_pointer, &currentLB);
		mapLBN(currentLB, &initial_sector);
		for(j = 0; j < (ctrl.boot.blockSize - offset); j++){
			read_sector(initial_sector+ offset+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE);
			remaining--;
			if(remaining == 0) break;
		}
		if(remaining == 0) break;
	}*/

	memcpy(buffer, leitura+relativeByte, size);
	ctrl.openFilesArray[handle].currentPointer += actualReadSize;

	/*BYTE *bufferAux;
	DWORD sectors = bytesToSectors(size);
	DWORD relativeByte = openFilesArray[handle].currentPointer % SIZE_SECTOR;	
	
	bufferAux = malloc(sectors*sizeof(BYTE));

	if(readSectorFile(handle, sectors, bufferAux))
		memcpy(buffer, bufferAux+relativeByte, size);
	else return ERROR;	*/

	return actualReadSize;
}

int write2(FILE2 handle, char *buffer, int size){
	BYTE *escrita;	
	int i, j;

	if(!isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR)) 
		return ERROR;

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

	if(readRequestedSectors(handle, size, escrita, n_sectors) == ERROR) return ERROR;

	/*for(i = 0; i < n_blocks-end_pointer; i++){
		mapVBN(mft, i+end_pointer, &currentLB);
		mapLBN(currentLB, &initial_sector);
		for(j = 0; j < (ctrl.boot.blockSize - offset); j++){
			read_sector(initial_sector+ offset+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE);
			remaining--;
			if(remaining == 0) break;
		}
		if(remaining == 0) break;
	}*/

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

FILE2 open2(char *filename){
	char *name;
	DWORD mftDir;
	FILE2 handle;


	if((name = getFileName(filename)) == NULL)
		return ERROR;

	if(isOpen(name, TYPEVAL_REGULAR)) 
		return ERROR;

	if((mftDir = pathExists(filename, name)) <= 0)
		return ERROR;

	if((handle = getHandle(1)) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle] = getFile(mftDir, name);

	return handle;
}

FILE2 create2 (char *filename){
	char *name;
	struct t2fs_record* newRecord;
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

DIR2 mkdir2 (char *pathname){
	char *name;
	struct t2fs_record* newRecord;
	DWORD mftDir;

	DIR2 handle;

	if((name = getFileName(pathname)) == NULL)
		return ERROR;
		
	if((mftDir = pathExists(pathname, name)) <= 0)
		return ERROR;

	if(hasFile(name, mftDir) != ERROR)
		return ERROR;

	if((newRecord = createFile(name, 2)) == NULL)
		return ERROR;

	if(addRecord(mftDir, newRecord))
		return ERROR;
	
	free(newRecord);

	if((handle = getHandle(2)) == ERROR)
		return ERROR;

	ctrl.openDirectoriesArray[handle] = getDir(mftDir, name);
	
	return handle;
}

int rmdir2 (char *pathname){
	char *dirName = getFileName(pathname);
	DWORD  fatherReg, dirReg;
	int block = 1;
	struct t2fs_record *record;
	
	//Caso tente excluir o root, retorna -1
	if(strcmp(pathname, "/")==0) return -1;	
	//Procura pelo pai
	fatherReg = pathExists(pathname, dirName);
	dirReg = hasFile(dirName, fatherReg);
	//Se a pasta não existe, retorna erro
	if(dirReg <= 0) return -1;

	if(fatherReg > 0) {
		record = findRecord(fatherReg, dirName, -1);
		//Verifica se é um diretório
		if(record->TypeVal != 2) return -2;
		//Verifica se está vazio
		if(hasAnyFile(dirReg)) return -3;
		//Deleta record no diretório pai
		if(rmRecord(fatherReg, record) < 0) return -1;
		//Deleta bloco do diretório
		if(deleteBlocks(dirReg, &block)) return -1;
		//Deleta MFT
		deleteRegister(dirReg);	
		return 0;
	}
	return -1;
}

DIR2 opendir2 (char *pathname) {
	int newHandle;
	char *dirName = getFileName(pathname);
	DWORD fatherReg = pathExists(pathname, dirName);
	
	//Verifica se diretório existe
	if(fatherReg <= 0) return -1;
	if(hasFile(dirName, fatherReg) == -1) return -1;
	//Verifica se está aberto
	if(isOpen(dirName, 2)) return -1; //Working
	//Verifica se há espaço
	newHandle = getHandle(2);
	if(newHandle == -1) return -1;
	ctrl.openDirectoriesArray[newHandle] = getDir(fatherReg, dirName);
	return newHandle;
}

int readdir2 (DIR2 handle, DIRENT2 *dentry) {
	struct t2fs_record *record = malloc(sizeof(struct t2fs_record));
	if(isOpenH(handle, 2) != 1) return -2; //Se não está aberto
	record = findRecord(ctrl.openDirectoriesArray[handle].MFT, NULL, ctrl.openDirectoriesArray[handle].currentEntry);
	if(record == NULL) return -1; //Se não há mais entradas
	//Converter record -> dirent2
	strcpy(dentry->name, record->name);
	dentry->fileType = record->TypeVal;
	dentry->fileSize = record->bytesFileSize;
	ctrl.openDirectoriesArray[handle].currentEntry++;
	//segfault aqui na segunda vez que roda, então comentei
	//free(record);
	return 0;
}

int closedir2 (DIR2 handle) {
	//Caso não esteja aberto
	if(isOpenH(handle, 2) != 1) return -1;
	ctrl.openDirectoriesArray[handle].valid = -1;
	return 0;
}

int identify2 (char *name, int size){

	char *str = "Lauren Silva Rolan Sampaio - 00262517\nLeonardo da Luz Dorneles - 00262516\nNatalia Gubiani Rampon - 00262502\n";

	// Nao pode-se copiar um numero negativo de caracteres
	if(size < 0)
		return ERROR;

	//Copia string para name
	memcpy(name, str, size);

	//Coloca sinalizacao de final de string
	if(size == 0)
		name[0] = '\0';
	else
		name[size-1] = '\0';

	return 0;
}
