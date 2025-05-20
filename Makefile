CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
LDFLAGS=

# target to build
TARGET=ginoshell

# source files and object files
SRCS=main.c ginoshell.c
OBJS=$(SRCS:.c=.o)

# target to run when make is typed
all: $(TARGET)

# link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# compile source files into object files
%.o: %.c ginoshell.h
	$(CC) $(CFLAGS) -c $< -o $@

# clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# phony targets
.PHONY: all clean

