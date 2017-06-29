/******************************
* TUPLES CONTROLLER COMPONENT
* MAIN AUTHOR: NATÁLIA GUBIANI RAMPON - 00262502
* 
* Component responsible for managing the tuples inside the registers
* in the MFT sector
*
*******************************/

#include <stdio.h>
#include "t2fs.h"

#define FIM_ENCADEAMENTO 0
#define MAPEAMENTO 1
#define MFT_ADICIONAL 2

/* Maps the program Virtual Block Number (VBN) to a disk Logical Block Number
** (LBN)
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS:[IN - DWORD] MFT - MFT number for the register being modified 
**	      [IN - DWORD] VBN - Virtual Block Number to be mapped
** 	      [OUT - DWORD] LBN - Logical Block Number mapping
*/
int mapVBN(DWORD MFT, DWORD VBN, DWORD* LBN);

int mapLBN(DWORD LBN, DWORD* sector);

/* Reads the requested sectors from file on disk
** If current pointer points to the middle of a sector, that sector will be read and
** counted as a sector in "nSectors"
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** Co-author:	LEONARDO DA LUZ DORNELES - 00262516
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS:[IN - FILE2] fileHandle - file handle of current file being read 
**	      [IN - int] nSectors - number of sectors to be read
** 	      [OUT - BYTE*] buffer - buffer in which the data will be put
*/
int readSectorFile(FILE2 fileHandle, int nSectors, BYTE* buffer);

/* Searches specific MFT and returns it
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error
** @ARGUMENTS: 	[IN] register number
**		[OUT] vector of tuples
*/
int searchMFT(DWORD numReg, struct t2fs_4tupla* vector);

/* Converts LBN into a sector
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517
** @RETURN:	0 - if executed without errors 
**		-1 - in case of any error

** @ARGUMENTS: 	[IN - DWORD] LBN
**		[OUT - DWORD*] sector

*/
int mapLBN(DWORD LBN, DWORD* sector);

/* Adds a new tuple to the vector passed as parameter
** Main author: 
** @RETURN:	0, if executed without errors
** 		-1, in case of any error
** @ARGUMENTS:	vector of tuples and the VBN number (-1, if it needs to create a new **		register)
*/
int newTuple(struct t2fs_4tupla vector, DWORD newVBN);

/* Gives initial sector of a given MFT register
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] Initial sector (to be used in read_sector() function )
** @ARGUMENTS:[IN - DWORD] MFT register 
*/
int registerToSector(DWORD MFT);


