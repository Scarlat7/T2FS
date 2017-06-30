#include "FileController.h"
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
*********************************************/

