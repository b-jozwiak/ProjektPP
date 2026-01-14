CC = gcc
CFLAGS = -Wall -Wextra -std=c99
CFLAGS_ASAN = $(CFLAGS) -fsanitize=address -g

SRC_DIR = src
OBJ_DIR = out/obj
OBJ_DIR_ASAN = out/obj_memcheck
BIN_DIR = out

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
OBJECTS_ASAN = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR_ASAN)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/rejestr
EXECUTABLE_ASAN = $(BIN_DIR)/rejestr_memcheck

all: $(EXECUTABLE)

memcheck: $(EXECUTABLE_ASAN)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE_ASAN): $(OBJECTS_ASAN) | $(BIN_DIR)
	$(CC) $(CFLAGS_ASAN) -o $(EXECUTABLE_ASAN) $(OBJECTS_ASAN)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR_ASAN):
	mkdir -p $(OBJ_DIR_ASAN)
	
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_ASAN)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR_ASAN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS_ASAN) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_ASAN) $(EXECUTABLE) $(EXECUTABLE_ASAN)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all memcheck clean run