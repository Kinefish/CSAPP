CC = /usr/bin/gcc
CFLAGS = -Wall -g -O0 -std=gnu99

EXE_HARDWARE = exe_hardware

SRC = ./src

#debug
COMMON = $(SRC_DIR)/common/*.c


# hardware
CPU =$(SRC_DIR)/hardware/cpu/*.c
MEMORY = $(SRC_DIR)/hardware/memory/*.c

# main
MAIN_HARDWARE = $(SRC_DIR)/main_hardware.c

.PHONY:hardware
hardware:
	$(CC) $(CFLAGS) -I$(SRC_DIR) $(COMMON) $(CPU) $(MEMORY) $(DISK) $(MAIN_HARDWARE) -o $(EXE_HARDWARE)
	./$(EXE_HARDWARE)

clean:
	rm -f *.o *.~ $(EXE_HARDWARE)