#include <stdio.h>
#include <stdlib.h>
#include "snekobject.h"

int main() {
    printf("=== Reference Counting Garbage Collector Demo ===\n\n");
    
    printf("Test 1: Creating an integer\n");
    snek_object_t *num = new_snek_integer(42);
    printf("  Integer created with value 42\n");
    printf("  Reference count: %d\n", num->refcount);
    
    refcount_inc(num);
    printf("  After increment, refcount: %d\n", num->refcount);
    
    refcount_dec(num);
    printf("  After decrement, refcount: %d\n", num->refcount);
    
    refcount_dec(num);
    printf("  After final decrement, object freed automatically\n\n");
    
    printf("Test 2: Creating a string\n");
    snek_object_t *str = new_snek_string("Hello, World!");
    printf("  String created: '%s'\n", str->data.v_string);
    printf("  Reference count: %d\n", str->refcount);
    
    refcount_dec(str);
    printf("  String freed automatically when refcount reached 0\n\n");
    
    printf("Test 3: Creating a Vector3 with nested objects\n");
    snek_object_t *x = new_snek_integer(10);
    snek_object_t *y = new_snek_integer(20);
    snek_object_t *z = new_snek_integer(30);
    printf("  Created integers: x=10, y=20, z=30\n");
    printf("  Each has refcount: %d\n", x->refcount);
    
    snek_object_t *vec = new_snek_vector3(x, y, z);
    printf("  Vector3 created, now x,y,z refcounts: %d\n", x->refcount);
    
    refcount_dec(x);
    printf("  Decremented x, but still alive (held by vector)\n");
    
    refcount_dec(vec);
    printf("  Vector freed, which also freed x,y,z\n");
    
    refcount_dec(y);
    refcount_dec(z);
    printf("  Cleaned up remaining references\n\n");
    
    printf("Test 4: Creating an array\n");
    snek_object_t *array = new_snek_array(3);
    printf("  Array created with size 3\n");
    
    snek_object_t *a = new_snek_integer(100);
    snek_object_t *b = new_snek_integer(200);
    snek_object_t *c = new_snek_integer(300);
    
    snek_array_set(array, 0, a);
    snek_array_set(array, 1, b);
    snek_array_set(array, 2, c);
    printf("  Array filled: 100, 200, 300\n");
    printf("  Element refcount: %d\n", a->refcount);
    
    refcount_dec(a);
    refcount_dec(b);
    refcount_dec(c);
    printf("  Released original refs, array still holds them\n");
    
    refcount_dec(array);
    printf("  Array freed, which freed all elements\n\n");
    
    printf("=== Demo Complete ===\n");
    
    return 0;
}
