#include "FilesController.h"
#include "t2fs.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int isValidName(char *name){
    char atual;
    int i = 0;
    if(strlen(name) > 51 || strlen(name) < 0) return 1;
    for(i = 0; i<strlen(name); i++) {
        atual = name[i];
        if((atual < 'A' || atual > 'z') && (atual <'0' || atual > '9') && atual != '.') return 1;
    }
    return 0;
}
