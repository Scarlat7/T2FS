#include "TuplesController.h"
#include "BootController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

t_control ctrl;

int searchMFT(int numReg, struct t2fs_4tupla *vector) {
	unsigned char buffer1[256], buffer2[256];
	int i = 0, index = 0;
	if(read_sector(ctrl.boot.blockSize + 2*numReg, buffer1)) return -1;
	if(read_sector(ctrl.boot.blockSize + 2*numReg + 1, buffer2)) return -1;
	for(i=0; i<16; i++) {
		memcpy(&vector[i].atributeType, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].virtualBlockNumber, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].logicalBlockNumber, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].numberOfContiguosBlocks, buffer1 + index, sizeof(DWORD));
		index += sizeof(DWORD);
	}
	index = 0;
	for(i=16; i<32; i++) {
		memcpy(&vector[i].atributeType, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].virtualBlockNumber, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].logicalBlockNumber, buffer2 + index, sizeof(DWORD));
		index += sizeof(DWORD);
		memcpy(&vector[i].numberOfContiguosBlocks, buffer2 + index, sizeof(DWORD));
	}
	return 0;
}

int read_block_file(DWORD currentPointer, int nBlocks, BYTE* buffer) {
	return -1;
}

int map_VBN(DWORD MFT, DWORD VBN, DWORD* LBN) {
	return -1;
}
