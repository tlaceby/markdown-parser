#include "helpers.h"
#include "stdlib.h"
#include <stdio.h>
#include "string.h"
#include "unistd.h"

char* alloc_slice(char* source, size_t start, size_t len) {
    char* slice = (char*)malloc(len * sizeof(char) + 1);
    char* srcOffsetPtr = (char*)(source + start);

    strncpy(slice, srcOffsetPtr, len);
    slice[len] = '\0';
    return slice;
}

char* read_file (char* path) {
    if (access(path, F_OK) != 0) {
        printf("File %s could not be accessed. Please make sure the file at this exists.\n", path);
        exit(FileNotFound);
    }

    FILE* f = fopen(path, "r");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);

    char* contents = malloc(size + 1);
    fread(contents, size, 1, f);
    fclose(f);

    return contents;
}