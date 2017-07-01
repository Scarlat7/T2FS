#include "FilesController.h"
#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"

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
int write2(FILE2 handle, char *buffer, int size){
	BYTE *escrita;	
	int i;
	DWORD mft = openFilesArray[handle].MFT;
	DWORD n_blocks = bytesToBlocks(openFilesArray[handle].size);
	DWORD pointerBlocks = bytesToBlocks(openFilesArray[handle].currentPointer);

	DWORD relativeByte = openFilesArray[handle].currentPointer % SIZE_SECTOR;	
	DWORD n_sectors = size/SECTOR_SIZE;
	if(size%SECTOR_SIZE != 0)
		n_sectors++;

	escrita = malloc(n_sectors*SECTOR_SIZE);
	  
	for(i = 0; i < n_blocks-pointerBlocks; i++){
		currentLB = mapVBN(mft, i+pointerBlocks);
		initial_sector = blocksToSector(currentLB);
		for(j = 0; j < sectorsInBlock; j++){
			read_sector(initial_sector+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE)
		}
	}
	
	memcpy(escrita+relativeByte, buffer, size);
	
	for(i = 0; i < n_blocks-pointerBlocks; i++){
		currentLB = mapVBN(mft, i+pointerBlocks);
		initial_sector = blocksToSector(currentLB);
		for(j = 0; j < sectorsInBlock; j++){
			write_sector(initial_sector+j, escrita+i*BLOCK_SIZE+j*SECTOR_SIZE)
		}
	}
}
*********************************************/
FILE2 create2 (char *filename){
	char *name;
	struct t2fs_record *newRecord = malloc(sizeof(struct t2fs_record));
	DWORD mftDir;

	if((name = getFileName(filename)) == NULL)
		return ERROR;
	
	if((mftDir = pathExists(filename, name)) <= 0)
		return ERROR;

	if((newRecord = createFile(name, 1)) == NULL)
		return ERROR;

	if(addRecord(mftDir, newRecord))
		return ERROR;

	return openFile(filename);
	
}
int mkdir2 (char *pathname){
	char *last = strrchr(pathname, '/');
	char dirName[MAX_FILE_NAME_SIZE];
	struct t2fs_record newRecord;
	DWORD  fatherReg, newReg, LBN;

	//Pega última palavra
	if(last == NULL) return -1;
	strcpy(dirName, last+1);
	
	//Procura pelo pai
	fatherReg = pathExists(pathname, dirName);
	if(fatherReg > 0) {
		newReg = findMFT();
		if(newReg <= 0) return -1;
		//Atualiza registro MFT recém criado
		if(mapVBN(newReg, 0, &LBN)) return -1;

		//Cria novo record
		newRecord.TypeVal = 2;
		strcpy(newRecord.name, dirName);
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
