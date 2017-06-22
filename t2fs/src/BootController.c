#include <stdio.h>
#include <stdlib.h>
#include "BootController.h"

	t_control ctrl;

int init_lib(){
	
	FILE* disk;

	disk = fopen("../t2fs_disk.dat", "r+");
	if(disk == NULL){
		fprintf(stderr, "Error opening disk file.\n");
		return 0;
	}

	ctrl.disk = disk;	
	ctrl.N_OpenFiles = 0;	

	return 1;
}

int read_boot_section(){

	fread(ctrl.boot.id, sizeof(char), 4, ctrl.disk);
	fread(&ctrl.boot.version, sizeof(WORD), 1,ctrl. disk);
	fread(&ctrl.boot.blockSize, sizeof(WORD), 1, ctrl.disk);
	fread(&ctrl.boot.MFTBlocksSize, sizeof(WORD), 1, ctrl.disk);
	fread(&ctrl.boot.diskSectorSize, sizeof(DWORD), 1, ctrl.disk);

#ifdef DEBUG
	printf("Boot Data:\n");
	printf("\tid:%c%c%c%c\n\tversion:%u\n\tblockSize:%u\n\tMFTBlocksSize:%u\n\tdiskSectorSize:%u\n", ctrl.boot.id[0], ctrl.boot.id[1], ctrl.boot.id[2], ctrl.boot.id[3], ctrl.boot.version, ctrl.boot.blockSize, ctrl.boot.MFTBlocksSize, ctrl.boot.diskSectorSize);
#endif

	if(ctrl.boot.version != 32273){
		fprintf(stderr, "File system version is outdated.\n");
		return 0;
	}

	if(ctrl.boot.id[0] != 'T' || ctrl.boot.id[1] != '2' || ctrl.boot.id[2] != 'F' || ctrl.boot.id[3] != 'S'){
		fprintf(stderr, "File system id is invalid.\n");
		return 0;
	}

	return 1;
}
