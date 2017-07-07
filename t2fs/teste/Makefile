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
MKDIR=mkdir
ADD=addRecord
OPDIR=opendir
MAIN=main
CREATE=create2
WRITE=write2
OPEN=open2
READD=readdir2
SEEK=seek2
READ=read2
CLOSED=closedir2
DELR=deleteRegister
DELB=deleteBlocks
ID=identify2
TRUNC=truncate2
HAS=hasFile
RMDIR=rmdir2
DEL=delete2
CLOSE=close2
STDIR=stressDir
STFILE=stressFile
TT=THETree

all: T_$(INIT) T_$(READBOOT) T_$(VALIDNAME) T_$(SEARCHMFT) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN) T_$(MKDIR) T_$(ADD) T_$(OPDIR) T_$(CREATE) T_$(WRITE) T_$(OPEN) T_$(READD) T_$(SEEK) T_$(READ) T_$(CLOSED) T_$(DELR) T_$(DELB) T_$(ID) T_$(TRUNC) T_$(RMDIR) T_$(DEL) T_$(CLOSE) T_$(STDIR) T_$(STFILE) T_$(TT)

T_$(INIT): T_$(INIT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(INIT) T_$(INIT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(READBOOT): T_$(READBOOT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(READBOOT) T_$(READBOOT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(VALIDNAME): T_$(VALIDNAME).c $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(VALIDNAME) T_$(VALIDNAME).c -I$(INC_DIR)/ $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/TuplesController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(SEARCHMFT): T_$(SEARCHMFT).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(SEARCHMFT) T_$(SEARCHMFT).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/BootController.o $(CFLAGS)

T_$(PRINTRECORD): T_$(PRINTRECORD).c $(BIN_DIR)/FilesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/TuplesController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(PRINTRECORD) T_$(PRINTRECORD).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/TuplesController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(REGSEC): T_$(REGSEC).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(REGSEC) T_$(REGSEC).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(FIND): T_$(FIND).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(FIND) T_$(FIND).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(VBN): T_$(VBN).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o
	$(CC) -o T_$(VBN) T_$(VBN).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(CFLAGS)

T_$(MKDIR): T_$(MKDIR).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(MKDIR) T_$(MKDIR).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(OPDIR): T_$(OPDIR).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(OPDIR) T_$(OPDIR).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(CLOSED): T_$(CLOSED).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(CLOSED) T_$(CLOSED).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(ADD): T_$(ADD).c $(BIN_DIR)/FilesController.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/TuplesController.o
	$(CC) -o T_$(ADD) T_$(ADD).c -I$(INC_DIR)/ $(BIN_DIR)/FilesController.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/TuplesController.o $(CFLAGS)

$(MAIN): $(MAIN).c $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o
	$(CC) -o $(MAIN) $(MAIN).c -I$(INC_DIR)/ $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(CREATE): T_$(CREATE).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(CREATE) T_$(CREATE).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(WRITE): T_$(WRITE).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(WRITE) T_$(WRITE).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(OPEN): T_$(OPEN).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(OPEN) T_$(OPEN).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(READD): T_$(READD).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(READD) T_$(READD).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(SEEK): T_$(SEEK).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(SEEK) T_$(SEEK).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(READ): T_$(READ).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(READ) T_$(READ).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(DELR): T_$(DELR).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(DELR) T_$(DELR).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(DELB): T_$(DELB).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(DELB) T_$(DELB).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(ID): T_$(ID).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(ID) T_$(ID).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(TRUNC): T_$(TRUNC).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(TRUNC) T_$(TRUNC).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(HAS): T_$(HAS).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(HAS) T_$(HAS).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(RMDIR): T_$(RMDIR).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(RMDIR) T_$(RMDIR).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(DEL): T_$(DEL).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(DEL) T_$(DEL).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(CLOSE): T_$(CLOSE).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(CLOSE) T_$(CLOSE).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(STDIR): T_$(STDIR).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(STDIR) T_$(STDIR).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(STFILE): T_$(STFILE).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(STFILE) T_$(STFILE).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

T_$(TT): T_$(TT).c $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o
	$(CC) -o T_$(TT) T_$(TT).c -I$(INC_DIR)/ $(BIN_DIR)/TuplesController.o $(BIN_DIR)/apidisk.o $(BIN_DIR)/BootController.o $(BIN_DIR)/bitmap2.o $(BIN_DIR)/FilesController.o $(BIN_DIR)/t2fs.o $(CFLAGS)

clean:
	rm -rf *.o *~ T_$(INIT) T_$(READBOOT) T_$(SEARCHMFT) T_$(VALIDNAME) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN) T_$(MKDIR) T_$(ADD) T_$(OPDIR) T_$(CREATE) T_$(WRITE) T_$(OPEN) T_$(READD) T_$(SEEK) T_$(READ) T_$(CLOSED) T_$(DELR) T_$(DELB) T_$(ID) T_$(TRUNC) T_$(RMDIR) T_$(DEL) T_$(CLOSE) T_$(STDIR) T_$(STFILE) T_$(TT)
