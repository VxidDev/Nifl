CC = gcc

TARGET = nifl

SRC_DIR = src
BUILD_DIR = build
PREFIX = /usr/local

CFLAGS_DEV = -Wall -Wextra -g -O0
CFLAGS_REL = -O3 -DNDEBUG

LDFLAGS =

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: dev

dev: CFLAGS = $(CFLAGS_DEV)
dev: $(TARGET)

release: CFLAGS = $(CFLAGS_REL)
release: clean $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	install -Dm755 $(TARGET) $(PREFIX)/bin/$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all dev release install clean run
