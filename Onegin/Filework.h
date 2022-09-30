#ifndef FILEWORK_
#define FILEWORK_
#include <stdio.h>
#include <stddef.h>

struct file_element {
    char *filename = nullptr;
    FILE *file_ptr = nullptr;
};

// gets length of file
size_t get_flen(FILE *file_ptr);

// reads all text file content into buffer
size_t fread_all(FILE *file_ptr, char **buffer, size_t *buf_size);


#endif