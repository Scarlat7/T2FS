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
