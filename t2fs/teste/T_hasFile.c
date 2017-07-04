#include <stdio.h>
#include <string.h>
#include "FilesController.h"
#include "t2fs.h"

int main(){
	char root[2];
	strcpy(root, "/");
	if(init_lib()) return 1;
	printf("Pai do root: %d\n", pathExists(root, ""));
	return 0;

}
