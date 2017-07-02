#include <stdio.h>
#include <string.h>
#include "apidisk.h"
#include "BootController.h"

	t_control ctrl;

int init_lib(){
	ctrl.N_OpenFiles = 0;
	ctrl.N_OpenDirectories = 0;
	read_boot_section();

	return 0;
}

int read_boot_section(){

	unsigned char buffer[256];
	int index = 0;

	if(read_sector(0, buffer) != 0){
		fprintf(stderr, "Falha ao ler setor do disco.\n");
		return -1;
	}

	memcpy(ctrl.boot.id,buffer,4*sizeof(char));
	index += 4*sizeof(char);
	memcpy(&ctrl.boot.version,buffer+index,sizeof(WORD));
	index += sizeof(WORD);
	memcpy(&ctrl.boot.blockSize,buffer+index,sizeof(WORD));
	index += sizeof(WORD);
	memcpy(&ctrl.boot.MFTBlocksSize,buffer+index, sizeof(WORD));
	index += sizeof(WORD);
	memcpy(&ctrl.boot.diskSectorSize,buffer+index,sizeof(DWORD));

#ifdef DEBUG
	printf("Boot Data:\n");
	printf("\tid:%c%c%c%c\n\tversion:%u\n\tblockSize:%u\n\tMFTBlocksSize:%u\n\tdiskSectorSize:%u\n", ctrl.boot.id[0], ctrl.boot.id[1], ctrl.boot.id[2], ctrl.boot.id[3], ctrl.boot.version, ctrl.boot.blockSize, ctrl.boot.MFTBlocksSize, ctrl.boot.diskSectorSize);
#endif

	if(ctrl.boot.version != 32273){
		fprintf(stderr, "File system version is outdated.\n");
		return -1;
	}

	if(ctrl.boot.id[0] != 'T' || ctrl.boot.id[1] != '2' || ctrl.boot.id[2] != 'F' || ctrl.boot.id[3] != 'S'){
		fprintf(stderr, "File system id is invalid.\n");
		return -1;
	}

	return 0;
}
