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

/* Maps the program Virtual Block Number (VBN) to a disk Logical Block Number
** (LBN)
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS:[IN - DWORD] MFT - MFT number for the register being modified 
**	      [IN - DWORD] VBN - Virtual Block Number to be mapped
** 	      [OUT - DWORD] LBN - Logical Block Number mapping
*/
int map_VBN(DWORD MFT, DWORD VBN, DWORD* LBN);

/* Reads the requested blocks from file on disk
** If current pointer points to the middle of a block, that block will be read and
** counted as a block in "nBlocks"
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS:[IN - DWORD] currentPointer - file current pointer to decide which blocks will be read 
**	      [IN - int] nBlocks - number of blocks to be read
** 	      [OUT - BYTE*] buffer - buffer in which the data will be put
*/
int read_block_file(DWORD currentPointer, int nBlocks, BYTE* buffer);
