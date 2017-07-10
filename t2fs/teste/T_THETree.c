#include "t2fs.h"
#include "BootController.h"
#include <stdio.h>
#include <string.h>

int main(){
	
	DIRENT2 entry;
	int handle;
	init_lib();
	mkdir2("/A");					//1
	mkdir2("/A/Lauren");				//2
	mkdir2("/A/Natalia");				//3
	mkdir2("/A/Lauren/gosta");			//4
	mkdir2("/A/Lauren/gosta/de");			//5
	mkdir2("/A/Lauren/gosta/de/bolo");		//6
	mkdir2("/A/Lauren/gosta/de/joginhos");		//7
	mkdir2("/A/Natalia/namora");			//8		
	mkdir2("/A/Natalia/namora/o");			//9
	mkdir2("/A/Natalia/namora/o/cara");		//10
	mkdir2("/A/Natalia/namora/o/cara/dos");		//11
	mkdir2("/A/Natalia/namora/o/cara/dos/Lolzinho");//12
	mkdir2("/A/Natalia/namora/o/cara/dos/files");	//13
	mkdir2("/A/Natalia/namora/o/Leo");		//14
	mkdir2("/A/Lauren/gosta/de/bolo/de");		//15
	mkdir2("/A/Lauren/gosta/de/bolo/de/cenoura");	//16
	mkdir2("/A/Lauren/gosta/de/bolo/de/milho");	//17
	mkdir2("/A/Lauren/gosta/de/bolo/de/chocolate");	//18
	mkdir2("/A/Lauren/gosta/de/bolo/de/morango"); 	//19
	mkdir2("/A/Lauren/gosta/de/bolo/de/amendoas");  //20


	if(rmdir2("/A/Lauren/gosta/de/bolo") == 0) printf("Oh, não! Bolo foi removido :/\n");
	else printf("Sucesso! Bolo não foi removido!");
	
	if(rmdir2("/A/Lauren/gosta/de/bolo/de/cenoura") == 0) printf("Sucesso! Cenoura foi removido!");
	else printf("Oh, não! Cenoura não foi removido :/\n");

	if(rmdir2("/A/Lauren/gosta/de/bolo/de/milho") == 0) printf("Sucesso! Milho foi removido!");
	else printf("Oh, não! Milho não foi removido :/\n");
	
	if(rmdir2("/A/Lauren/gosta/de/bolo/de/chocolate") == 0) printf("Sucesso! Chocolate foi removido!");
	else printf("Oh, não! Chocolate não foi removido :/\n"); 

	if(rmdir2("/A/Lauren/gosta/de/bolo/de/morango") == 0) printf("Sucesso! Morango foi removido!");
	else printf("Oh, não! Morango não foi removido :/\n"); 

	if(rmdir2("/A/Lauren/gosta/de/bolo/de/amendoas") == 0) printf("Sucesso! amendoas foi removido!");
	else  printf("Oh, não! amendoas não foi removido :/\n");

	if(rmdir2("/A/Lauren/gosta/de/bolo/de") == 0) printf("Sucesso! de foi removido!");
	else printf("Oh, não! de não foi removido :/\n"); 
	
	if(rmdir2("/A/Natalia/namora/o/Leo") == 0) printf("Leo foi removido com sucesso!\n");
	else printf("Oh, não! Leo não pôde ser removido :/\n");
	
	if(rmdir2("/") == 0) printf("Oh, não! O root foi removido!\n");
	else printf("Sucesso! O root não foi removido.\n");
	
	handle = opendir2("/A/Lauren/gosta/de/bolo");

	while(readdir2(handle, &entry) != -1) { //Nunca deve executar
		printf("Name: %s\tType: %d\tSize: %d\n", entry.name, entry.fileType, entry.fileSize); 
	}

	return 0;
	
}
