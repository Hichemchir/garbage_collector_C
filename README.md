# Garbage Collector in C

Two simple implementations of garbage collection algorithms in C.

## Overview

This project demonstrates two fundamental garbage collection strategies:

1. **Reference Counting** (`cyclic_reference/`) - Tracks object references and frees objects when refcount reaches 0
2. **Mark and Sweep** (`mark_and_sweep/`) - Traces reachable objects from roots and collects unreachable memory

## Running the Demos

### Cyclic reference

```bash
cd cyclic_reference
make run
```

### Mark and Sweep

```bash
cd mark_and_sweep
make run
```

## Cleaning Up

To remove build artifacts:
```bash
make clean
```

## What Each Demo Shows

### Reference Counting Demo
- Automatic memory management through reference counting
- Creating integers, strings, vectors, and arrays
- How refcount increases when objects are referenced
- Automatic deallocation when refcount reaches zero

### Mark and Sweep Demo
- VM with stack frames managing object references
- Three-phase collection (Mark, Trace, Sweep)
- Collecting orphaned objects not in any frame
- Tracing through complex nested objects (Vector3)

## Implementation Details

### Reference Counting
- Each object has a `refcount` field
- `refcount_inc()` increments the counter
- `refcount_dec()` decrements and frees at 0
- Nested objects (Vector3, Array) properly manage child references

### Mark and Sweep
- **Mark**: Identify root objects in active frames
- **Trace**: Follow references to find all reachable objects
- **Sweep**: Free unmarked (unreachable) objects
- Uses a VM with stack frames to track live references

## Requirements

- GCC or Clang
- C99 standard support
- Make

## Limitations

**Reference Counting**: Cannot handle cyclic references without additional mechanisms (hence the folder name).

**Mark and Sweep**: Requires pausing to run collection (stop-the-world).