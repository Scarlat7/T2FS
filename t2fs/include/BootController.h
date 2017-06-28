/******************************
* BOOT CONTROLLER COMPONENT
* MAIN AUTHOR: NATÁLIA GUBIANI RAMPON - 00262502
* 
* Component responsible for booting the filesystem and this library
*
*******************************/

#include <stdio.h>
#include "t2fs.h"

/** Control struct for library data static data */
typedef struct s_Control {
	
	struct t2fs_bootBlock boot;
	//struct TDAA OpenFilesArray (struct TDAA should have fileBytesSize, dirty bit, MFT, currentPointer
	//struct TDAA OpenDirectoriesArray/List	 (Directory should have MFT, dirty bit, fileBytesSize, currentEntry)
	int N_OpenFiles;

} t_control;

extern t_control ctrl; 

/* Initializes library 
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS: none
*/
int init_lib();

/* Reads boot section into memory 
** Main author: NATÁLIA GUBIANI RAMPON - 00262502
** @RETURN: 0 - if executed without errors
**          -1 - error
** @ARGUMENTS: none
*/
int read_boot_section();
