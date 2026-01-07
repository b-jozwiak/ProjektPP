CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCES = /src/main.c 
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = test_program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run