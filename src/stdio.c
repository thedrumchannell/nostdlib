#include <stdio.h>
#include <windows.h>

int putc(int c, FILE *stream)
{
    DWORD written;

    if (WriteFile(stream, &c, 1, &written, NULL)) {
        return c;
    }
    
    return EOF;
}

int putchar(int c)
{
    HANDLE hFile = GetStdHandle(STD_OUTPUT_HANDLE);

    if (putc(c, hFile) != EOF) {
        return c;
    }
    
    return EOF;
}

int puts(const char *str)
{
    size_t len = strlen(str);
    HANDLE hFile = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;

    if (!WriteFile(hFile, str, len, &written, NULL)) {
        return EOF;
    }

    if (putchar('\n') == EOF) {
        return EOF;
    }

    return 1;
}
