#include "t2fs.h"
#include "FilesController.h"
#include "BootController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	char teste[6];
	strcpy(teste, "/Test");
	if(mkdir2(teste)) printf("Deu ruim.\n");
	printRecords(1);
	return 0;
}
