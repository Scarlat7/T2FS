#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	printf("********************************************\n");
	printf("%d\n", open2("/oi.a"));
	printf("%d\n", open2("/oioi.mori:"));
	printf("%d\n", open2("/oi.a"));
	printf("********************************************\n");

	return 0;
}