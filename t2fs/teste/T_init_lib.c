#include <stdio.h>
#include "BootController.h"

int main(){

	if(init_lib() == 0)
		printf("Falha no teste da init_lib.\n");
	else
		printf("Sucsso no teste da init_lib.\n");

	return 0;
}
