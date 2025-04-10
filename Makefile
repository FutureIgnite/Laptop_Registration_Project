

CC        = gcc
CFLAGS    = -Wall -Wextra
MD        = mkdir
BINPREFIX = ../build
BUILD_DIR = $(BINPREFIX)/$(shell basename $(CURDIR))
SRCS      = $(wildcard *.c)
BINS      = $(patsubst %.c, $(BUILD_DIR)/%, $(SRCS))

all: $(BINS)

$(BUILD_DIR):
	$(MD) -p $(BUILD_DIR)

$(BINS): $(BUILD_DIR)/%: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

.PHONY clean all
clean:
	rm -rf $(BUILD_DIR)
