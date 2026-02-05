# Smart Makefile: Compiles separately, then links

CC = gcc
CFLAGS = -g -Wall -O0 -std=c99

SOURCES = mysh.c executor.c parser.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = mysh

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Note: The line above MUST start with a TAB character, not spaces

.PHONY: clean all

clean:
	rm -f $(OBJECTS) $(TARGET)