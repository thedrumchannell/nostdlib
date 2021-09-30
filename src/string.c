#include <string.h>

void *memset(void *str, int c, size_t n)
{
    unsigned char *dest = str;
    while (n--) {
        dest[n] = c;
    }

    return str;
}

char *strcpy(char *dest, const char *src)
{
    int i = 0;
    while (dest[i] = src[i++]);

    return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }

    return dest;
}

size_t strlen(const char *str)
{
    size_t i = 0;
    while (str[++i]);
    
    return i;
}
