#include "t2fs.h"
#include "FilesController.h"
#include <stdio.h>
#include <string.h>

int main(){
	init_lib();
	printf("********************************************\n");
	printf("handle: %d\n", create2("/oi.a"));
	printf("handle: %d\n", create2("/oioi.mori"));
	printf("close %d\n", close2(0));
	printf("close %d\n", close2(1));
	printf("open %d\n", open2("/oi.a"));
	printf("open %d\n", open2("/oioi.mori"));
	printf("open %d\n", open2("/oi.a"));
	printf("********************************************\n");

	return 0;
}