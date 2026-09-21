CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/main.c src/mystrfunctions.c src/myfilefunctions.c
OBJ = obj/main.o obj/mystrfunctions.o obj/myfilefunctions.o
TARGET = bin/client

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(OBJ) -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf obj/*.o bin/*
