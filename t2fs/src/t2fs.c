#include "FilesController.h"
#include "TuplesController.h"
#include "apidisk.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *init;

int close2 (FILE2 handle){

	struct t2fs_record rec;

	if(init == NULL)
		init_lib();

	if(isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR) <= 0) 
		return ERROR;

	rec.TypeVal = TYPEVAL_REGULAR;
	strncpy(rec.name, ctrl.openFilesArray[handle].name, MAX_FILE_NAME_SIZE);
	rec.blocksFileSize = ctrl.openFilesArray[handle].blocksSize;
	rec.bytesFileSize = ctrl.openFilesArray[handle].bytesSize;
	rec.MFTNumber = ctrl.openFilesArray[handle].MFT;

	if(updateRecord(ctrl.openFilesArray[handle].fatherMFT, rec) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle].valid = -1;

	return 0;

}

int delete2 (char *filename){

	char* name;
	DWORD fatherDir;
	struct t2fs_record *record;
	FILE2 handle;

	if(init == NULL)
		init_lib();

	if((name = getFileName(filename)) == NULL)
		return ERROR;

	if((handle = isOpen(name, TYPEVAL_REGULAR)) < 0)
		ctrl.openFilesArray[handle-1].valid = -1;

	if((fatherDir = pathExists(filename)) == ERROR)
		return ERROR;

	if(hasFile(name, fatherDir, TYPEVAL_REGULAR) == ERROR)
		return ERROR;

	if((record  = findRecord(fatherDir, name, -1)) == NULL)
		return ERROR;

	if(deleteBlocks(record->MFTNumber,&(record->blocksFileSize)) == ERROR)
		return ERROR;

	if(rmRecord(fatherDir, record) < 0 ) 
		return ERROR;

	return 0;

}

int truncate2 (FILE2 handle){

	DWORD n_blocks = ctrl.openFilesArray[handle].bytesSize/(ctrl.boot.blockSize*SECTOR_SIZE)+1;	
	DWORD end_block = ctrl.openFilesArray[handle].currentPointer/(ctrl.boot.blockSize*SECTOR_SIZE)+1;
	DWORD delete_blocks = n_blocks - end_block;

	if(init == NULL)
		init_lib();

	if(isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR) <= 0) 
		return ERROR;

	if(deleteBlocks(ctrl.openFilesArray[handle].MFT, &delete_blocks) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle].bytesSize = ctrl.openFilesArray[handle].currentPointer;

	return 0;
}

int seek2 (FILE2 handle, DWORD offset){
	
	if(init == NULL)
		init_lib();

	if(isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR) <= 0) 
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

	if(init == NULL)
		init_lib();

	if(isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR) <= 0) 
		return ERROR;
	if(ctrl.openFilesArray[handle].currentPointer + size > ctrl.openFilesArray[handle].bytesSize){
		actualReadSize = ctrl.openFilesArray[handle].bytesSize - ctrl.openFilesArray[handle].currentPointer;
	}

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;
	
	leitura = malloc(n_sectors*SECTOR_SIZE);

	if(readRequestedSectors(handle, actualReadSize, leitura) == ERROR) return ERROR;

	memcpy(buffer, leitura+relativeByte, size);

	ctrl.openFilesArray[handle].currentPointer += actualReadSize;

	return actualReadSize;
}

int write2(FILE2 handle, char *buffer, int size){
	BYTE *escrita;

	if(init == NULL)
		init_lib();

	if(isOpen(ctrl.openFilesArray[handle].name, TYPEVAL_REGULAR) <= 0) 
		return ERROR;

	DWORD relativeByte = ctrl.openFilesArray[handle].currentPointer % SECTOR_SIZE;

	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;
	
	escrita = malloc(n_sectors*SECTOR_SIZE);

	if(readRequestedSectors(handle, size, escrita) == ERROR) return ERROR;

	memcpy(escrita+relativeByte, buffer, size);

	if(writeRequestedSectors(handle, size, escrita) == ERROR) return ERROR;

	ctrl.openFilesArray[handle].bytesSize += updateFileSize(ctrl.openFilesArray[handle], size);
	ctrl.openFilesArray[handle].currentPointer += size;
	ctrl.openFilesArray[handle].blocksSize = bytesToBlocks(ctrl.openFilesArray[handle].bytesSize);

	return size;
}

FILE2 open2(char *filename){
	char *name;
	DWORD mftDir;
	FILE2 handle;

	if(init == NULL)
		init_lib();

	if((name = getFileName(filename)) == NULL)
		return ERROR;

	if(isOpen(name, TYPEVAL_REGULAR)) 
		return ERROR;

	if((mftDir = pathExists(filename)) == ERROR)
		return ERROR;

	if((handle = getHandle(TYPEVAL_REGULAR)) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle] = getFile(mftDir, name);

	if(ctrl.openFilesArray[handle].valid == ERROR)
		return ERROR;

	return handle;
}

FILE2 create2 (char *filename){
	char *name;
	struct t2fs_record* newRecord;
	DWORD mftDir;
	FILE2 handle;

	if(init == NULL)
		init_lib();

	if((name = getFileName(filename)) == NULL)
		return ERROR;
	
	if(isValidName(name))
		return ERROR;

	if((mftDir = pathExists(filename)) == ERROR)
		return ERROR;

	if(hasFile(name, mftDir, TYPEVAL_REGULAR) != ERROR)
		return ERROR;

	if((newRecord = createFile(name, TYPEVAL_REGULAR)) == NULL)
		return ERROR;

	if(addRecord(mftDir, newRecord))
		return ERROR;
	
	free(newRecord);

	if((handle = getHandle(1)) == ERROR)
		return ERROR;

	ctrl.openFilesArray[handle] = getFile(mftDir, name);
	
	if(ctrl.openFilesArray[handle].valid == ERROR)
		return ERROR;

	return handle;
	
}

int mkdir2 (char *pathname){
	char *name;
	struct t2fs_record* newRecord;
	DWORD mftDir;
	
	if(init == NULL)
		init_lib();

	if((name = getFileName(pathname)) == NULL)
		return ERROR;

	if(isValidName(name))
		return ERROR;

	if((mftDir = pathExists(pathname)) == ERROR)
		return ERROR;

	if(hasFile(name, mftDir, TYPEVAL_DIRETORIO) != ERROR)
		return ERROR;

	if((newRecord = createFile(name, 2)) == NULL)
		return ERROR;

	if(addRecord(mftDir, newRecord))
		return ERROR;
	
	free(newRecord);
	
	return 0;
}

int rmdir2 (char *pathname){
	char *dirName = getFileName(pathname);
	DWORD  fatherReg, dirReg;
	DWORD block = 1;
	struct t2fs_record *record;

	if(init == NULL)
		init_lib();
	
	//Caso tente excluir o root, retorna -1
	if(strcmp(pathname, "/")==0) return -1;	
	//Procura pelo pai
	fatherReg = pathExists(pathname);
	dirReg = hasFile(dirName, fatherReg, TYPEVAL_DIRETORIO);
	//Se a pasta não existe, retorna erro
	if(dirReg == ERROR) return -1;

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
	DWORD fatherReg = pathExists(pathname);
	
	if(init == NULL)
		init_lib();
	//Verifica se diretório existe
	if(fatherReg == ERROR) return -1;

	if(strcmp(pathname, "/") != 0){
		if(hasFile(dirName, fatherReg, TYPEVAL_DIRETORIO) == -1) return -1;	
	}else{
		fatherReg = ROOT_FATHER;
		strcpy(dirName, "/");
	}

	//Verifica se está aberto
	if(isOpen(dirName, 2)) return -1; //Working
	//Verifica se há espaço
	newHandle = getHandle(2);
	if(newHandle == -1) return -1;

	ctrl.openDirectoriesArray[newHandle] = getDir(fatherReg, dirName);
	return newHandle;
}

int readdir2 (DIR2 handle, DIRENT2 *dentry) {
	struct t2fs_record *record;

	if(init == NULL)
		init_lib();

	if(isOpenH(handle, 2) <= 0) return -2; //Se não está aberto
	record = findRecord(ctrl.openDirectoriesArray[handle].MFT, NULL, ctrl.openDirectoriesArray[handle].currentEntry);
	if(record == NULL) return -1; //Se não há mais entradas
	//Converter record -> dirent2
	strcpy(dentry->name, record->name);
	dentry->fileType = record->TypeVal;
	dentry->fileSize = record->bytesFileSize;
	ctrl.openDirectoriesArray[handle].currentEntry++;
	return 0;
}

int closedir2 (DIR2 handle) {
	
	if(init == NULL)
		init_lib();

	//Caso não esteja aberto
	if(isOpenH(handle, 2) != 1) return -1;
	ctrl.openDirectoriesArray[handle].valid = -1;
	return 0;
}

int identify2 (char *name, int size){

	char *str = "Lauren Silva Rolan Sampaio - 00262517\nLeonardo da Luz Dorneles - 00262516\nNatalia Gubiani Rampon - 00262502\n";

	if(init == NULL)
		init_lib();

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
