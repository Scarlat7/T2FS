#
# Makefile ESQUELETO
#
# DEVE ter uma regra "all" para geração da biblioteca
# regra "clean" para remover todos os objetos gerados.
#
# NECESSARIO adaptar este esqueleto de makefile para suas necessidades.
#
# 

CC=gcc
CFLAGS=-Wall
CFLAGS += -DDEBUG -g 
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

BOOT=BootController
FILES=FilesController
TUPLES=TuplesController
T2FS=t2fs

all: $(BOOT).o $(FILES).o $(TUPLES).o $(T2FS).o libt2fs.a

$(BOOT).o: $(SRC_DIR)/$(BOOT).c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/$(BOOT).c -o $(BIN_DIR)/$(BOOT).o

$(FILES).o: $(SRC_DIR)/$(FILES).c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/$(FILES).c -o $(BIN_DIR)/$(FILES).o

$(TUPLES).o: $(SRC_DIR)/$(TUPLES).c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/$(TUPLES).c -o $(BIN_DIR)/$(TUPLES).o

$(T2FS).o: $(SRC_DIR)/$(T2FS).c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/$(T2FS).c -o $(BIN_DIR)/$(T2FS).o

libt2fs.a: $(BIN_DIR)/$(BOOT).o $(BIN_DIR)/$(FILES).o $(BIN_DIR)/$(TUPLES).o $(BIN_DIR)/$(T2FS).o $(BIN_DIR)/apidisk.o  $(BIN_DIR)/bitmap2.o
	ar crs $(LIB_DIR)/libt2fs.a $(BIN_DIR)/$(BOOT).o $(BIN_DIR)/$(FILES).o $(BIN_DIR)/$(TUPLES).o $(BIN_DIR)/$(T2FS).o $(BIN_DIR)/apidisk.o  $(BIN_DIR)/bitmap2.o

clean:
	rm -rf $(LIB_DIR)/*.a $(SRC_DIR)/*~ $(INC_DIR)/*~ *~ ; cp $(BIN_DIR)/bitmap2.o $(INC_DIR)/bitmap2.o ; cp $(BIN_DIR)/apidisk.o $(INC_DIR)/apidisk.o ; rm -rf $(BIN_DIR)/*.o ; mv $(INC_DIR)/apidisk.o $(BIN_DIR)/apidisk.o ; mv $(INC_DIR)/bitmap2.o $(BIN_DIR)/bitmap2.o


