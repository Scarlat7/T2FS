/******************************
* FILES CONTROLLER COMPONENT
* MAIN AUTHORS: LAUREN SILVA ROLAN SAMPAIO - 00262517
*               LEONARDO DA LUZ DORNELES - 00262516
*
* Component responsible for manipulating files and directories
*
*******************************/

#include <stdio.h>
#include "t2fs.h"


#define N_OPENFILES 20

typedef struct openFiles{
	DWORD MFT;
	DWORD currentPointer;
	char name[MAX_NAME];
	char sectorBuffer[SECTOR_SIZE];

}OPENFILES;

OPENFILES openFilesArray[N_OPENFILES];

/*inicializa o openFilesArray com -1*/
void init_openFilesArray();

/*verifica no array de arquivos aberto se há um handle disponível*/
int getFileNumber()

/*abre um arquivo e retorna o handle*/
int openFile(char *path);

/* Verifies if the name passed as parameter is valid */
int isValidName(char *name);

void printRecords(DWORD reg);

/*Alloc one block to an file*/
int allocateBlock(struct t2fs_4tupla *vector);

DWORD hasFile(char *directories, DWORD currentReg);

DWORD pathExists(char *pathName);

int LBNToRecord(DWORD LBN, struct t2fs_record* records);

DWORD searchFile(struct t2fs_record *records, char *name);

/*Prints the contents of sector */
//void printDirectory(unsigned int sector);
