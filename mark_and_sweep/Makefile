# Makefile for Mark and Sweep Garbage Collector

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = mark_and_sweep
SOURCES = main.c munit.c bootlib.c sneknew.c snekobject.c stack.c vm.c

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

# Run the tests
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Create a simple Python script to run the project
python-runner:
	@echo "#!/usr/bin/env python3" > run_project.py
	@echo "import subprocess" >> run_project.py
	@echo "import sys" >> run_project.py
	@echo "import os" >> run_project.py
	@echo "" >> run_project.py
	@echo "def main():" >> run_project.py
	@echo "    # Build the project" >> run_project.py
	@echo "    print('Building project...')" >> run_project.py
	@echo "    result = subprocess.run(['make'], capture_output=True, text=True)" >> run_project.py
	@echo "    if result.returncode != 0:" >> run_project.py
	@echo "        print('Build failed:')" >> run_project.py
	@echo "        print(result.stderr)" >> run_project.py
	@echo "        sys.exit(1)" >> run_project.py
	@echo "" >> run_project.py
	@echo "    # Run the tests" >> run_project.py
	@echo "    print('Running tests...')" >> run_project.py
	@echo "    result = subprocess.run(['./$(TARGET)'], capture_output=True, text=True)" >> run_project.py
	@echo "    print(result.stdout)" >> run_project.py
	@echo "    if result.stderr:" >> run_project.py
	@echo "        print('Errors:')" >> run_project.py
	@echo "        print(result.stderr)" >> run_project.py
	@echo "" >> run_project.py
	@echo "    return result.returncode" >> run_project.py
	@echo "" >> run_project.py
	@echo "if __name__ == '__main__':" >> run_project.py
	@echo "    sys.exit(main())" >> run_project.py
	@chmod +x run_project.py
	@echo "Created run_project.py - you can now run: python3 run_project.py"

.PHONY: all run clean python-runner