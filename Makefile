CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC_DIR = src
OBJ_DIR = out/obj
BIN_DIR = out

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/test_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run