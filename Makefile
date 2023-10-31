# Compiler
CC := gcc

# Compiler flags
CFLAGS := -std=c11 -Wall

# Source file
SRC := main.c

# Executable name
TARGET := program

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)
