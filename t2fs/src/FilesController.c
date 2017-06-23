#include "FilesController.h"
#include "t2fs.h"
#include "apidisk.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isValidName(char *name){
    char current;
    int i = 0;
    if(strlen(name) > 51 || strlen(name) < 0) return -1;
    for(i = 0; i<strlen(name); i++) {
        current = name[i];
        if((current < 'A' || current > 'z') && (current <'0' || current > '9') && current != '.') return -1;
    }
    return 0;
}

//Fun��o que imprime o conte�do de um diret�rio, dado seu setor e tamanho em bytes
//Ainda n�o testada
int printDirectory(unsigned int sector, DWORD bytesFileSize){
    unsigned char buffer[SECTOR_SIZE];
	int index = 0;
	int numberOfRegisters, numberOfSectors;
    t2fs_record current;

	if(ctrl == NULL){
        init_lib();
        return -1;
	}

    numberOfRegisters = bytesFileSize/64; //Diret�rios s�o sempre m�ltiplos de 64, logo arredondamento n�o � necess�rio.
    numberOfSectors = numberOfRegisters/4;
    if(numberOfRegisters%4 != 0) numberOfSectors++;

    do {
        if(read_sector(0, buffer) != 0){
            fprintf(stderr, "Falha ao ler setor do disco.\n");
            return -1;
        }

        do {
            memcpy(&current.TypeVal, buffer+index, sizeof(BYTE));
            index += sizeof(BYTE);
            memcpy(&current.name, buffer+index, MAX_FILE_NAME_SIZE*sizeof(CHAR));
            index += MAX_FILE_NAME_SIZE*sizeof(CHAR);
            memcpy(&current.blocksFileSize, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            memcpy(&current.bytesFileSize, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            memcpy(&current.MFTNumber, buffer+index, sizeof(DWORD));
            index += sizeof(DWORD);
            printf("Type: %02x\tName: %s\n", current.TypeVal, current.name);
            printf("BlocksFileSize: %4d\tBytesFileSize: %4d\tMFTNumber: %10d\n", current.blocksFileSize, current.bytesFileSize, current.MFTNumber);
            numberOfRegisters --;
        }while(numberOfRegisters != 0 && (numberOfRegisters+1)%4 != 0);
        numberOfSectors --;
    }while(numberOfSectors != 0);
    return 0;
}
