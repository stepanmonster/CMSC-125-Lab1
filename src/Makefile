
CC = gcc
CFLAGS = -g -Wall -O0 -std=c99

SOURCES = mysh.c executor.c parser.c 
OBJECTS = $(SOURCES:.c=.o)
TARGET = mysh
HEADER = command.h

# 'all' will build the target and then run the clean-objects rule
all: $(TARGET)
	@echo "Build complete. Cleaning object files..."
	$(MAKE) clean-objects

# Links object files into the final executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiles .c files into .o files
# Adding $(HEADER) ensures that if you change the struct, everything recompiles
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean all clean-objects

clean-objects:
	rm -f $(OBJECTS)

# Full cleanup of executable and objects
clean:
	rm -f $(OBJECTS) $(TARGET)