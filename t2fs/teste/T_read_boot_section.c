#include <stdio.h>
#include "BootController.h"

int main(){

	if(init_lib() == 0 )
		printf("Falha na init_lib.\n");

	if(read_boot_section() == 0)
		printf("Falha no teste da read_boot_sector.\n");
	else
		printf("Sucesso no teste da read_boot_sector.\n");

	return 0;
}
