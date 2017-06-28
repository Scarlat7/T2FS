#include "../include/t2fs.h"

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
