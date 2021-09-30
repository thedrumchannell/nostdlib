#include <stdlib.h>
#include <windows.h>

void *malloc(size_t size)
{
    void* memory = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);

    if (!memory) {
        return NULL;
    }
    
    return memory;
}

void *realloc(void *ptr, size_t size)
{
    void* memory = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, size);

    if (!memory) {
        return NULL;
    }
    
    return memory;
}

void free(void *ptr)
{
    HeapFree(GetProcessHeap(), 0, ptr);
}
