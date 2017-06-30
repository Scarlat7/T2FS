#include <stdio.h>
#include "FilesController.h"
#include "BootController.h"
#include "t2fs.h"

int main(){
	if(init_lib()) return 1;
	printf("Imprimindo root.\n");
	printRecords(1);
	printf("Fim da impressão.\n");
	return 0;
}
