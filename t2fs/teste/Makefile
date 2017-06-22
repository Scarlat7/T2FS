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

all: T_$(INIT) T_$(READBOOT)

T_$(INIT): T_$(INIT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(INIT) T_$(INIT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

T_$(READBOOT): T_$(READBOOT).c $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o
	$(CC) -o T_$(READBOOT) T_$(READBOOT).c -I$(INC_DIR)/ $(BIN_DIR)/BootController.o $(BIN_DIR)/apidisk.o $(CFLAGS)

clean:
	rm -rf *.o *~ T_$(INIT) T_$(READBOOT)
