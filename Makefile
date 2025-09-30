# Makefile for Shell Implementation
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Detect running on Windows (native) and warn the user: this project uses POSIX APIs
# (fork/wait/etc.) that are not available on native Windows toolchains. Prefer WSL
# or MSYS2/MinGW environments. This check prints a helpful warning when `make` is
# executed from a Windows shell (where the OS environment variable is Windows_NT).
UNAME_S := $(shell uname -s 2>/dev/null)
ifeq ($(OS),Windows_NT)
WINDOWS = 1
endif

ifeq ($(WINDOWS),1)
$(warning Detected Windows environment. shell.c uses POSIX APIs (fork/wait) which are not available in native Windows GCC. Build inside WSL, MSYS2 or a Linux environment. See README.md for instructions.)
endif

# Target executable
TARGET = shell

# Source files
SRCS = shell.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Build the shell executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Run the shell
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run