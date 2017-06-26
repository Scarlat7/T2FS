#include "../include/t2fs.h"

typedef struct openFile{
	DWORD currentPointer;
	DWORD MFTNumber;
}

DWORD bytesToBlocks(DWORD bytes){
	if(bytes%getBlockSize() == 1)
		return bytes/getBlockSize() + 1;
	return bytes/getBlockSize();
} 

DWORD MFTToSectors(DWORD MFTNumber){
	DWORD n_MFTinBlock = getBlockSize()/getMFTSize();
	
	DWORD logicalBlock = MFTNumber/n_MFTinBlock;

	DWORD sectorsInMFTRegister = n_MFTinBlock/getSectorsInBlock(); 

	DWORD initialSector = logicalBlock*getSectorsInBlock();

	DWORD relativeSector = sectorInMFTRegister*(MFTNumber % n_MFTinBlock);

	return initialSector + relativeSector;
	 
}


/*esse pedaço de código não sei se vai ser uma função futuramente, mas
* a ideia era já achar o bloco inicial de leitura/edição do arquivo
* determinado pelo current pointer. rascunho
*/
int getInitialBlock(DWORD size, int fileNumber){
	DWORD currentPointer = openFiles[fileNumber].currentPointer;
	DWORD mft_number = openFiles[fileNumber].MFTNumber;

	DWORD pointerBlocks = bytesToBlocks(currentPointer);

	DWORD relativeSector = currentPointer%(pointerBlocks*getBlockSize());
	relativeSector = relativeSector/getSectorSize();
	int tuple = -1;

	while(pointerBlocks > 0){
		tuple++;
		DWORD tupleBlocks = getContiguousBlocks(tuple);
		pointerBlocks -= tupleBlocks;	
	}

	if(pointerBlocks < 0){
		initialTupleBlock = getContiguousBlocks(tuple) + pointerBlocks;	
	}

	
			

}
