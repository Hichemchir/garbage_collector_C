#!/usr/bin/env python3


import subprocess
import sys
import os
from pathlib import Path

def main():
    current_dir = Path.cwd()
    if not (current_dir / "main.c").exists():
        print("Error: main.c not found in current directory")
        print("Please run this script from the mark_and_sweep directory.")
        return 1

    print("Compiling Mark and Sweep Garbage Collector...")

    compile_cmd = [
        "gcc",
        "-Wall", "-Wextra", "-std=c99", "-g",
        "-o", "mark_and_sweep",
        "main.c", "munit.c", "bootlib.c",
        "sneknew.c", "snekobject.c", "stack.c", "vm.c"
    ]

    try:
        result = subprocess.run(compile_cmd, capture_output=True, text=True)

        if result.returncode != 0:
            print("Compilation failed:")
            print(result.stderr)
            return 1

        print("Compilation successful.")

        print("\nRunning tests...")

        if not os.path.exists("./mark_and_sweep"):
            print("Executable not found after compilation.")
            return 1

        result = subprocess.run(["./mark_and_sweep"], capture_output=True, text=True)

        if result.stdout:
            print("Test results:")
            print(result.stdout)

        if result.stderr:
            print("Errors/Warnings:")
            print(result.stderr)

        if result.returncode == 0:
            print("All tests passed.")
        else:
            print("Some tests failed.")

        return result.returncode

    except FileNotFoundError:
        print("Error: gcc not found. Please ensure development tools are installed.")
        return 1
    except Exception as e:
        print(f"Unexpected error: {e}")
        return 1

if __name__ == "__main__":
    sys.exit(main())