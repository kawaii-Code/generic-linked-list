CC = gcc
BIN = bin
SRC = examples/*.c

all: directories examples

directories:
	mkdir -p "bin"

examples: $(SRC)
	$(CC) examples/ll_int.c -o $(BIN)/int
	$(CC) examples/ll_string.c -o $(BIN)/string

run: all
	./$(BIN)/int
	./$(BIN)/string
