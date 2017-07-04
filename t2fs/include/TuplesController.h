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

#define TUPLES_IN_REG 32
#define SECTORS_IN_REG 2

/* Deletes "n" last blocks mapped by a register */
int deleteBlocks(DWORD MFT, int n);

/* Deletes a MFT register from disk 
** (ONLY THE REGISTER, THE MAPPED BLOCKS ARE NOT DELETED) */
int deleteRegister(DWORD MFT);

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

/* Maps the program Logical Block Number (LBN) to a disk Sector
** Main author: LAUREN SILVA ROLAN SAMPAIO - 00262517	
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS:[IN - DWORD] LBN - Logical Block Number
** 	      [OUT - DWORD] sector
*/
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

/* Gives initial sector of a given MFT register
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] Initial sector (to be used in read_sector() function )
** @ARGUMENTS:[IN - DWORD] MFT register 
*/
int registerToSector(DWORD MFT);

/* Finds first available MFT register
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [DWORD] MFT register number > 0 if executed without errors
**		    0 if no MFT is available (full disk)
**		    -1 if error occurred
** @ARGUMENTS: none 
*/
DWORD findMFT();

/* Boolean function to determine if a block is contiguous in a tuple
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] 1 - if contiguous
**		  0 - if not contiguous
** @ARGUMENTS: [INT - IN] mapped LBN
**	       [T2FS_4TUPLA - IN] tuple in which the block is to be put
*/
int isContiguous(int bit, struct t2fs_4tupla t);

/* Boolean function to determine if a VBN is sequential to mapping in a tuple
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] 1 - if sequential
**		  0 - if not sequential
** @ARGUMENTS: [DWORD - IN] requested VBN
**	       [T2FS_4TUPLA - IN] tuple in which the VBN is to be put
*/
int isSequential(DWORD VBN, struct t2fs_4tupla t);

/* Returns the file size in number of blocks
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] if positive file Size
**		  -1 if error occured
** @ARGUMENTS: [DWORD - IN] MFT register of the file
*/
int getFileBlockSize(DWORD MFT);

/* Boolean function to determine if a VBN is in the range of blocks
** mapped in a tuple
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: [INT] 1 - if it's in range
**		  0 - if it isn't in range
** @ARGUMENTS: [DWORD - IN] requested VBN
**	       [T2FS_4TUPLA - IN] tuple in which the VBN possibly is mapped
*/
int isInRange(DWORD VBN, struct t2fs_4tupla t);

/* Writes a MFT register
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed withour errors
**			1 - if an error occurred
** @ARGUMENTS: [DWORD - IN] MFT register to be written
**	       [T2FS_4TUPLA* - IN] buffer of size 32 to be written
*/
int writeRegister(DWORD MFT, struct t2fs_4tupla* bufferT);
