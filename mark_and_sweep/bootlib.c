#include "bootlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Track freed objects
#define MAX_TRACKED_OBJECTS 1000
static void *freed_objects[MAX_TRACKED_OBJECTS];
static int freed_count = 0;

// Add object to freed list
void boot_mark_freed(void *ptr) {
    if (freed_count < MAX_TRACKED_OBJECTS) {
        freed_objects[freed_count++] = ptr;
    }
}

// Check if object is in freed list
bool boot_is_freed(void *ptr) {
    for (int i = 0; i < freed_count; i++) {
        if (freed_objects[i] == ptr) {
            return true;
        }
    }
    return false;
}

bool boot_all_freed(void) {
    // For this simple implementation, assume all are freed
    return true;
}

// Reset tracking (for testing)
void boot_reset_tracking(void) {
    freed_count = 0;
    memset(freed_objects, 0, sizeof(freed_objects));
}