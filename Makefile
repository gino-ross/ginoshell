CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c99
LDFLAGS=

SRC_DIR=src
BUILD_DIR=build

# target to build
TARGET=ginoshell

symlink: $(BUILD_DIR)/$(TARGET)
	@ln -sf $(BUILD_DIR)/$(TARGET) $(TARGET)

# source files and object files
SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# target to run when make is typed
all: $(BUILD_DIR)/$(TARGET) symlink

# link object files to create the executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create build dir if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# clean build artifacts
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

# phony targets
.PHONY: all clean

