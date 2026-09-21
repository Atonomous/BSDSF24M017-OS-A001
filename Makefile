CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
AR = ar
ARFLAGS = rcs

LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

LIB_OBJS = $(OBJ_DIR)/mystrfunctions.o $(OBJ_DIR)/myfilefunctions.o
STATIC_LIB = $(LIB_DIR)/libmyutils.a
TARGET = $(BIN_DIR)/client_static

all: $(TARGET)

$(TARGET): $(OBJ_DIR)/main.o $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $< -L$(LIB_DIR) -lmyutils -o $@

$(STATIC_LIB): $(LIB_OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/* $(BIN_DIR)/*
