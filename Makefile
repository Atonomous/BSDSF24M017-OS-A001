CC = gcc
CFLAGS = -Iinclude
PIC_FLAGS = -fPIC
AR = ar
ARFLAGS = rcs

LIB_DIR = lib
OBJ_DIR = obj
BIN_DIR = bin

STATIC_LIB = $(LIB_DIR)/libmyutils.a
DYNAMIC_LIB = $(LIB_DIR)/libmyutils.so

all: static dynamic

static: $(BIN_DIR)/client_static
dynamic: $(BIN_DIR)/client_dynamic

$(OBJ_DIR)/main.o: src/main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%_pic.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(PIC_FLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(STATIC_LIB): $(OBJ_DIR)/mystrfunctions.o $(OBJ_DIR)/myfilefunctions.o
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(BIN_DIR)/client_static: $(OBJ_DIR)/main.o $(STATIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR) -lmyutils -o $@

$(DYNAMIC_LIB): $(OBJ_DIR)/mystrfunctions_pic.o $(OBJ_DIR)/myfilefunctions_pic.o
	@mkdir -p $(LIB_DIR)
	$(CC) -shared $^ -o $@

$(BIN_DIR)/client_dynamic: $(OBJ_DIR)/main.o $(DYNAMIC_LIB)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_DIR) -lmyutils -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(LIB_DIR)/* $(BIN_DIR)/*

PREFIX = /usr/local

install: $(BIN_DIR)/client_static
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 755 $(BIN_DIR)/client_static $(DESTDIR)$(PREFIX)/bin/client
	install -d $(DESTDIR)$(PREFIX)/share/man/man3
	install -m 644 man/man3/* $(DESTDIR)$(PREFIX)/share/man/man3/
	mandb
