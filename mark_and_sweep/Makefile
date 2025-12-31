# Makefile for Mark and Sweep Garbage Collector

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
BUILD_DIR = build
TARGET = $(BUILD_DIR)/mark_and_sweep
SOURCES = main.c sneknew.c snekobject.c stack.c vm.c

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

run: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean