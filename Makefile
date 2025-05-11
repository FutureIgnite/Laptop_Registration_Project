CC        = gcc
CFLAGS    = -Wall -Wextra -std=c89 -g
GTK_FLAGS = $(shell pkg-config --cflags gtk+-3.0)  # GTK3 compiler flags
LIBS      =  $(shell pkg-config --libs gtk+-3.0) -lsqlite3 # GTK3 + SQlite 3

SRC_DIR   = srcs
BUILD_DIR = build
BIN_DIR   = bin

SRCS      = $(wildcard $(SRC_DIR)/*.c)
OBJS      = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TARGET    = $(BIN_DIR)/DevAuth

.PHONY: all setup clean

all: setup $(TARGET)
	@echo "Source files: $(SRCS)"
	@echo "Building $(TARGET)..."
	@echo "Build complete."
	@echo "Executable is located at $(TARGET)"

setup:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(GTK_FLAGS) -o $@ $^ $(LIBS)
	@echo "Linking objects..."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling source $<..."
	$(CC) $(CFLAGS) $(GTK_FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) 
