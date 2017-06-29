#include <stdio.h>
#include "FilesController.h"
#include "BootController.h"
#include "t2fs.h"

int main(){
	if(init_lib()) return 1;
	printRecords(2);
	return 0;
}
