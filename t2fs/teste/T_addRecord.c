#include <stdio.h>
#include <string.h>
#include "FilesController.h"

int main() {
	struct t2fs_record r[17]; //deve mudar de setor e bloco
	char string[18];
	int i;
	init_lib();
	strcpy(string, "");
	for(i = 0; i < 17; i++){
		string[i] = 'a';
		string[i+1] = '\0';
		strcpy(r[i].name, string);
		r[i].TypeVal = 1;
		r[i].blocksFileSize = 1;
		r[i].bytesFileSize = ctrl.boot.blockSize;
		addRecord(1, &r[i]);
	}
	return 0;
}
