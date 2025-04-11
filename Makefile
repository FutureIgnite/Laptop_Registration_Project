CC        = gcc
CFLAGS    = -Wall -Wextra -g
#LIBS      = -lsqlite3

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
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Linking objects..."

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling source $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
