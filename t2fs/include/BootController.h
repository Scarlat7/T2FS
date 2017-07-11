/******************************
* BOOT CONTROLLER COMPONENT
* MAIN AUTHOR: NATÁLIA GUBIANI RAMPON - 00262502
* 
* Component responsible for booting the filesystem and this library
*
*******************************/

#include <stdio.h>
#include "t2fs.h"

#define ERROR -1
#define N_OPENFILES 20
#define N_OPENDIRECTORIES 50

/** Control struct for library data static data */

typedef struct openFile{
	int valid;
	DWORD MFT;
	DWORD fatherMFT;
	DWORD currentPointer;
	DWORD blocksSize;
	DWORD bytesSize;
	char name[MAX_FILE_NAME_SIZE];

}OPENFILE;

typedef struct openDirectory{
	int valid;
	DWORD MFT;
	DWORD currentEntry;
	DWORD blocksSize;
	DWORD bytesSize;
	char name[MAX_FILE_NAME_SIZE];

}OPENDIRECTORY;

typedef struct s_Control {
	
	struct t2fs_bootBlock boot;
	OPENFILE openFilesArray[N_OPENFILES];
	OPENDIRECTORY openDirectoriesArray[N_OPENDIRECTORIES];
	int N_OpenFiles;
	int N_OpenDirectories;

} t_control;

extern t_control ctrl; 

extern int *init;

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
