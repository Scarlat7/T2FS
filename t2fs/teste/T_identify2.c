#include <stdio.h>
#include <stdlib.h>
#include "t2fs.h"

int main(){

	char* nomes = malloc(160);
		
	if(identify2(nomes, -1) != 0)
		printf("Teste 1 sucesso (size negativo, erro esperado)\n %s\n", nomes); 

	nomes[0] = '\0';

	identify2(nomes, 0);
	printf("Teste 2 (size=0)\n %s\n", nomes);

	nomes[0] = '\0';
	
	identify2(nomes, 10);
	printf("Teste 3 (size insuficiente)\n %s\n", nomes);

	nomes[0] = '\0';

	identify2(nomes, 150);
	printf("Teste 4 (size exacerbado)\n %s\n", nomes);

	nomes[0] = '\0';
	
	identify2(nomes,108);
	printf("Teste 5 (size exato)\n %s\n", nomes);


	return 0;
}