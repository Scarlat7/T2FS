#
# Makefile para testes
# 
# Gera todos testes das pastas

CC=gcc
CFLAGS= -Wall

LIB_DIR=../lib
BIN_DIR=../bin
INC_DIR=../include

INIT=init_lib
READBOOT=read_boot_section
VALIDNAME=isValidName
SEARCHMFT=searchMFT
PRINTRECORD=printRecords
REGSEC=registerToSector
FIND=findMFT
VBN=mapVBN

all: T_$(INIT) T_$(READBOOT) T_$(VALIDNAME) T_$(SEARCHMFT) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN)

T_$(INIT): T_$(INIT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(INIT) T_$(INIT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(READBOOT): T_$(READBOOT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(READBOOT) T_$(READBOOT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(VALIDNAME): T_$(VALIDNAME).c $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(VALIDNAME) T_$(VALIDNAME).c -I$(INC_DIR)/ $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/TuplesController.o $(CFLAGS)

T_$(SEARCHMFT): T_$(SEARCHMFT).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o
	$(CC) -o T_$(SEARCHMFT) T_$(SEARCHMFT).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(CFLAGS)

T_$(PRINTRECORD): T_$(PRINTRECORD).c $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/TuplesController.o
	$(CC) -o T_$(PRINTRECORD) T_$(PRINTRECORD).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/TuplesController.o $(CFLAGS)

T_$(REGSEC): T_$(REGSEC).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o
	$(CC) -o T_$(REGSEC) T_$(REGSEC).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(CFLAGS)

T_$(FIND): T_$(FIND).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(FIND) T_$(FIND).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(VBN): T_$(VBN).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(VBN) T_$(VBN).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

clean:
	rm -rf *.o *~ T_$(INIT) T_$(READBOOT) T_$(SEARCHMFT) T_$(VALIDNAME) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN)
