#ifndef BOOTLIB_H
#define BOOTLIB_H

#include <stdbool.h>

// Functions to track memory allocation for testing
bool boot_is_freed(void *ptr);
bool boot_all_freed(void);
void boot_mark_freed(void *ptr);
void boot_reset_tracking(void);

#endif
