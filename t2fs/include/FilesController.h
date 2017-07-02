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

/*retorna o nome do arquivo a partir do path*/
//char* getFileName(char *filename);

/*cria um registro mft pro novo arquivo e retorna seu record*/
//struct t2fs_records createFile(char* name, short int typeVal);

/*inicializa o openFilesArray com -1*/
//void init_openFilesArray();

/* Verifies if the array has space and returns the handle
** Main author: LEONARDO DA LUZ DORNELES - 00262516
** @RETURN:	handle - if there is a valid position
**		-1 - in case of invalid type or full array
** @ARGUMENTS: 	[IN - int] type - 1, files array
**				- 2, directories array
*/
int getHandle(int type);

/*abre um arquivo e retorna o handle*/
//int openFile(char *path);

/*retorna um record do file especificado*/
//struct t2fs_records getRecordsFile(char *path);

/*procura numa região de memória o record com o nome especificado e o retorna*/
//struct t2fs_records getRecordByName(char *name, BYTE *sectors);

/* Verifies if the passed parameter is valid
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - char*] name - name
*/
int isValidName(char *name);

/* Prints all the records of the directory
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - DWORD] reg - MFT register
*/
void printRecords(DWORD reg);

/* Adds a record to the directory pointed by fatherReg
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - DWORD] fatherReg - MFT register
**		[IN - struct t2fs_record] record - to be added
*/
int addRecord(DWORD fatherReg, struct t2fs_record *record);

/* Removes the record from the directory pointed by fatherReg
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - DWORD] fatherReg - MFT register
**		[IN - struct t2fs_record] record - to be removed

*/
int rmRecord(DWORD fatherReg, struct t2fs_record *record);

/*Alloc one block to an file*/
//int allocateBlock(struct t2fs_4tupla *vector);

/* Recursive method that verifies if the file pointed by directories
** is in the current directory
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	MFT register - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - DWORD] currentReg - MFT register
**		[IN - char*] directories - pathname
*/
DWORD hasFile(char *directories, DWORD currentReg);

/* Verifies if path is valid and return the last MFT register
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	MFT register - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - char*] pathname - pathname
*/
DWORD pathExists(char *pathName, char *fileName);

/* Converts LBN into array of records
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - DWORD] LBN - Logical Block Number
**		[OUT - struct t2fs_record] records - array containing all the records 
*/
int LBNToRecord(DWORD LBN, struct t2fs_record* records);

/* Search for a specific file in an array of records, returning its MFT register
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	register - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN - char*] name - file name
**		[In - struct t2fs_record] records - array containing all the records 
*/
DWORD searchFile(struct t2fs_record *records, char *name);

/* Verifies if the file given by path is already open
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if it is not open
**		1 - if it is open
**		-1 - in case of invalid type
** @ARGUMENTS: 	[IN - char*] pathname - path
**		[IN - int] type - 1, search file
**				- 2, search directory
*/
int isOpen(char *pathname, int type);
