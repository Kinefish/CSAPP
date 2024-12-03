CC = /usr/bin/gcc
CFLAGS = -Wall -g -O0 -std=gnu99
EXE = csapp
SRC = ./src
CODE = ./src/memory/*.c ./src/cpu/*.c ./src/disk/*.c ./src/utils/*.c ./src/main.c
.PHONY: csapp
csapp:
	$(CC) $(CFLAGS) -I$(SRC) $(CODE) -o $(EXE)
	./$(EXE)

clean:
	rm -f *.o *.~ $(EXE)
