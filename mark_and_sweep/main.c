#include <stdio.h>
#include <stdlib.h>
#include "vm.h"
#include "sneknew.h"

int main() {
    printf("=== Mark and Sweep Garbage Collector Demo ===\n\n");
    
    vm_t *vm = vm_new();
    printf("VM created\n\n");
    
    printf("Test 1: Creating objects in frame 1\n");
    frame_t *frame1 = vm_new_frame(vm);
    
    snek_object_t *str1 = new_snek_string(vm, "Hello World");
    frame_reference_object(frame1, str1);
    printf("  String 'Hello World' created\n");
    
    snek_object_t *num1 = new_snek_integer(vm, 42);
    frame_reference_object(frame1, num1);
    printf("  Integer 42 created\n");
    
    printf("  Total objects in VM: %zu\n\n", vm->objects->count);
    
    printf("Test 2: Running GC (nothing should be collected)\n");
    vm_collect_garbage(vm);
    printf("  After GC: %zu objects (all still referenced)\n\n", vm->objects->count);
    
    printf("Test 3: Creating frame 2 with more objects\n");
    frame_t *frame2 = vm_new_frame(vm);
    
    snek_object_t *str2 = new_snek_string(vm, "Goodbye");
    frame_reference_object(frame2, str2);
    printf("  String 'Goodbye' created in frame 2\n");
    
    snek_object_t *num2 = new_snek_integer(vm, 100);
    frame_reference_object(frame2, num2);
    printf("  Integer 100 created in frame 2\n");
    
    printf("  Total objects in VM: %zu\n\n", vm->objects->count);
    
    printf("Test 4: Freeing frame 2 and running GC\n");
    frame_free(vm_frame_pop(vm));
    printf("  Frame 2 freed\n");
    
    vm_collect_garbage(vm);
    printf("  After GC: %zu objects (frame 2 objects collected)\n\n", vm->objects->count);
    
    printf("Test 5: Creating orphan objects (not referenced)\n");
    new_snek_string(vm, "I'm orphaned");
    new_snek_integer(vm, 999);
    printf("  Created 2 orphan objects (not in any frame)\n");
    printf("  Total objects in VM: %zu\n", vm->objects->count);
    
    printf("  Running GC...\n");
    vm_collect_garbage(vm);
    printf("  After GC: %zu objects (orphans collected)\n\n", vm->objects->count);
    
    printf("Test 6: Complex objects - Vector3\n");
    snek_object_t *x = new_snek_integer(vm, 10);
    snek_object_t *y = new_snek_integer(vm, 20);
    snek_object_t *z = new_snek_integer(vm, 30);
    snek_object_t *vec = new_snek_vector3(vm, x, y, z);
    frame_reference_object(frame1, vec);
    printf("  Vector3 created with x=10, y=20, z=30\n");
    printf("  Total objects: %zu (vector + 3 integers)\n\n", vm->objects->count);
    
    printf("Test 7: Freeing all frames\n");
    frame_free(vm_frame_pop(vm));
    printf("  Frame 1 freed\n");
    
    vm_collect_garbage(vm);
    printf("  After GC: %zu objects (everything collected)\n\n", vm->objects->count);
    
    vm_free(vm);
    printf("VM freed\n\n");
    
    printf("=== Demo Complete ===\n");
    printf("Mark and Sweep traces from roots (frames) and collects unreachable objects\n");
    
    return 0;
}
