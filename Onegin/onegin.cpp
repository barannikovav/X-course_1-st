#include "onegin.h"
#include "errcodes.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>



size_t count_symbol(const char symbol, const char *buffer) {
    size_t count = 0;
    size_t i = 0;
    char element;

    RET_ASSERT(buffer == nullptr, ERR_NULL_PTR_ARG);

    while ((element = *(buffer + i)) != '\0') {
        if (element == symbol)
            count++;
        i++;
    }

    return count;
}

size_t create_lines_arr(struct Text *f, const char separator) {
    char *line_start = nullptr;
    char *cur_buf_pos = nullptr;
    Line *line_arr = nullptr;
    Line *cur_line_pos = nullptr;
    size_t i = 0; 
    size_t line_num = 0;

    RET_ASSERT(f == nullptr, ERR_NULL_PTR_ARG);
    RET_ASSERT(f->buf_ptr == nullptr, ERR_NULL_PTR_ARG);

    if ((line_num = count_symbol(separator, f->buf_ptr)) < 0)
        return ERR_COUNT_SYM;
    
    if ((line_arr = (Line *) calloc(line_num, sizeof(Line))) == NULL)
        return ERR_ALL_MEM;

    f->line_arr = line_arr; // CHECK
    f->line_arr_size = line_num;

    line_num = 0;
    line_start = f->buf_ptr;
    cur_buf_pos = f->buf_ptr;
    
    for (i = 0; i < f->buf_size + 1; i++) {
        
        printf("i = %zu\n", i);
        cur_buf_pos = f->buf_ptr + i;
        cur_line_pos = f->line_arr + line_num;

        if (*cur_buf_pos == separator) {
            
            cur_line_pos->ptr = line_start;
            cur_line_pos->len = cur_buf_pos - line_start;

            line_start = cur_buf_pos + 1;
            line_num++;
        }       

    }

    return line_num++;
}

size_t print_line (Line * l) {
    RET_ASSERT(l == nullptr || l->ptr == nullptr, ERR_NULL_PTR_ARG);
    
    size_t i = 0;
    for (i = 0; i < l->len; i++) {
        //printf("%p\n", l->ptr+i);
        putchar(*(l->ptr+i)); // how to process putchar errors here?
        //printf("%zu\n", i);
    }

    putchar('\n');

    return i++;
}

size_t is_letter(const unsigned char * symbol) {
    return ((*symbol > 64 && *symbol < 91) || (*symbol > 96 && *symbol < 123));
}

int line_comp (const void *ptr_1, const void *ptr_2) {
    const Line *line_1 = (const Line *) ptr_1;
    const Line *line_2 = (const Line *) ptr_2;
    const unsigned char *str_1 = (const unsigned char *) line_1->ptr;
    const unsigned char *str_2 = (const unsigned char *) line_2->ptr;
    size_t len_1 = line_1->len;
    size_t len_2 = line_2->len;
    size_t min_len = 0;
    unsigned char c1, c2;
    size_t i = 1;

    min_len = (((len_1) < (len_2)) ? (len_1) : (len_2));

    do {
        if (i > min_len) {
            if (len_1 == len_2)
                return 0;
            else if (len_1 == min_len)
                return -1;
            else if (len_2 == min_len)
                return 1;
        }
        c1 = (unsigned char) *str_1++;
        c2 = (unsigned char) *str_2++;
        if (!(is_letter(&c1) && is_letter(&c2))) {
            continue;
        }
        i++;
    }
    while (c1 == c2);

    return c1 - c2;
}

void free_text(Text * f) {
    if (f->buf_ptr != nullptr)
        free(f->buf_ptr);

    if (f->line_arr != nullptr) {
        free(f->line_arr);
    }
}