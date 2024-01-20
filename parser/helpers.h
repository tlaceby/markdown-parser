#ifndef __markdown_helpers__
#define __markdown_helpers__
#include "stdlib.h"

typedef enum Error {
    NoError,
    InvalidArguments,
    FileNotFound,
    OutMemory,
    UnexpectedToken,
    UnexpectedEndOfFile,
} Error;

char* alloc_slice(char* source, size_t start, size_t len);
char* read_file (char* path);

#endif