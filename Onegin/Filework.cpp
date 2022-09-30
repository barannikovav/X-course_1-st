#include "Filework.h"
#include "errcodes.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


size_t get_flen(FILE *file_ptr) {
    size_t ret_code, flen = 0;

    if ((ret_code = fseek(file_ptr, 0L, SEEK_END)) == -1) {
        return ret_code;
    }
    flen = ftell(file_ptr);
    rewind(file_ptr);

    return flen;
}

size_t fread_all(FILE *file_ptr, char **buffer, size_t *buf_size) {
    size_t ret_code, flen, read_num = 0;

    RET_ASSERT(buf_size == nullptr, ERR_NULL_PTR_ARG);

    if ((flen = get_flen(file_ptr)) == -1) {
        return -1;
    }

    *buf_size = flen;

    if ((*buffer = (char *)calloc(flen + 1, sizeof(char))) == NULL) {
        return ERR_ALL_MEM;
    } 

    while (read_num < flen) {
        ret_code = fread(*buffer, sizeof(char), flen, file_ptr);
        if (ret_code) { /* fread success */
            read_num += ret_code;
        }
        else { /* fread failed */
            if ( ferror(file_ptr) )  /* error reading file */
                return ERR_READ_FILE;
            else if ( feof(file_ptr) ) /* EOF found */
                break;
        }       
    }

    return read_num;
}

size_t fwrite_all(FILE *file_ptr, char **buffer, size_t *buf_size) {
   size_t ret_code = 0;
   
   RET_ASSERT(buf_size == nullptr, ERR_NULL_PTR_ARG);

   return fwrite(*buffer, sizeof(char), *buf_size, file_ptr);
}

