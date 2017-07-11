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
ULT=theUltimateWrite
RMB=rmBlocks
MAIN=main
CECHIN=cechin

all: T_$(INIT) T_$(READBOOT) T_$(VALIDNAME) T_$(SEARCHMFT) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN) T_$(MKDIR) T_$(ADD) T_$(OPDIR) T_$(CREATE) T_$(WRITE) T_$(OPEN) T_$(READD) T_$(SEEK) T_$(READ) T_$(CLOSED) T_$(DELR) T_$(DELB) T_$(ID) T_$(TRUNC) T_$(RMDIR) T_$(DEL) T_$(CLOSE) T_$(STDIR) T_$(STFILE) T_$(TT) T_$(ULT) T_$(RMB) $(CECHIN)

T_$(INIT): T_$(INIT).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(INIT) T_$(INIT).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(READBOOT): T_$(READBOOT).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(READBOOT) T_$(READBOOT).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(VALIDNAME): T_$(VALIDNAME).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(VALIDNAME) T_$(VALIDNAME).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(SEARCHMFT): T_$(SEARCHMFT).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(SEARCHMFT) T_$(SEARCHMFT).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(PRINTRECORD): T_$(PRINTRECORD).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(PRINTRECORD) T_$(PRINTRECORD).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(REGSEC): T_$(REGSEC).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(REGSEC) T_$(REGSEC).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(FIND): T_$(FIND).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(FIND) T_$(FIND).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(VBN): T_$(VBN).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(VBN) T_$(VBN).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(MKDIR): T_$(MKDIR).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(MKDIR) T_$(MKDIR).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(OPDIR): T_$(OPDIR).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(OPDIR) T_$(OPDIR).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(CLOSED): T_$(CLOSED).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(CLOSED) T_$(CLOSED).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(ADD): T_$(ADD).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(ADD) T_$(ADD).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

$(MAIN): $(MAIN).c $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o
	$(CC) -o $(MAIN) $(MAIN).c -I$(INC_DIR)/ $(BIN_DIR)/bitmap2.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(CREATE): T_$(CREATE).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(CREATE) T_$(CREATE).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(WRITE): T_$(WRITE).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(WRITE) T_$(WRITE).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(OPEN): T_$(OPEN).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(OPEN) T_$(OPEN).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(READD): T_$(READD).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(READD) T_$(READD).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(SEEK): T_$(SEEK).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(SEEK) T_$(SEEK).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(READ): T_$(READ).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(READ) T_$(READ).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(DELR): T_$(DELR).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(DELR) T_$(DELR).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(DELB): T_$(DELB).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(DELB) T_$(DELB).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(ID): T_$(ID).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(ID) T_$(ID).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(TRUNC): T_$(TRUNC).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(TRUNC) T_$(TRUNC).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(HAS): T_$(HAS).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(HAS) T_$(HAS).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(RMDIR): T_$(RMDIR).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(RMDIR) T_$(RMDIR).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(DEL): T_$(DEL).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(DEL) T_$(DEL).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(CLOSE): T_$(CLOSE).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(CLOSE) T_$(CLOSE).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(STDIR): T_$(STDIR).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(STDIR) T_$(STDIR).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(STFILE): T_$(STFILE).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(STFILE) T_$(STFILE).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(TT): T_$(TT).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(TT) T_$(TT).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(ULT): T_$(ULT).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(ULT) T_$(ULT).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

T_$(RMB): T_$(RMB).c $(LIB_DIR)/libt2fs.a
	$(CC) -o T_$(RMB) T_$(RMB).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

$(CECHIN): $(CECHIN).c $(LIB_DIR)/libt2fs.a
	$(CC) -o $(CECHIN) $(CECHIN).c -I$(INC_DIR)/ -L$(LIB_DIR) -lt2fs $(CFLAGS)

clean:
	rm -rf *.o *~ T_$(INIT) T_$(READBOOT) T_$(SEARCHMFT) T_$(VALIDNAME) T_$(PRINTRECORD) T_$(REGSEC) T_$(FIND) T_$(VBN) T_$(MKDIR) T_$(ADD) T_$(OPDIR) T_$(CREATE) T_$(WRITE) T_$(OPEN) T_$(READD) T_$(SEEK) T_$(READ) T_$(CLOSED) T_$(DELR) T_$(DELB) T_$(ID) T_$(TRUNC) T_$(RMDIR) T_$(DEL) T_$(CLOSE) T_$(STDIR) T_$(STFILE) T_$(TT) T_$(ULT) T_$(RMB) $(CECHIN)
