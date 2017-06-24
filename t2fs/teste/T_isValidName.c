#include <stdio.h>
#include <string.h>
#include "FilesController.h"

int main(){

	char longName[53];
	char maximumSizeName[52];
	char hasDotName[10];
	char hasSpecialCharacterName[10];

	int i;
	
	for(i=0; i<52; i++) {
		longName[i] = 'a';
	}
	longName[52] = '\0';
	for(i=0; i<51; i++) {
		maximumSizeName[i] = 'b';
	}
	maximumSizeName[51] = '\0';
	strcpy(hasDotName, "ola1.txt");
	strcpy(hasSpecialCharacterName, "ola*txt");

	printf("Is longName (size=%d)  invalid? (Must be 1) %d\n", strlen(longName), isValidName(longName));
	printf("Is maximumSizeName (size=%d) invalid? (Must be 0) %d\n", strlen(maximumSizeName), isValidName(maximumSizeName));
	printf("Is hasDotName valid? (Must be 0) %d\n", isValidName(hasDotName));
	printf("Is hasSpecialCharacterName valid? (Must be 1) %d\n", isValidName(hasSpecialCharacterName));

	return 0;
}
