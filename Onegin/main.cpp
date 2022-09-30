#include "errcodes.h"
#include "Filework.h"
#include "onegin.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file_ptr = nullptr;
    Text onegin_f = {};
    size_t buf_size = 0;

    if (argc != 2) {

        puts("Вы забыли указать имя файла для сортировки! Правильный формат:");
        puts("main.cpp <filename>");

        return ERR_ARG_NUM;
    }

    if ((file_ptr = fopen(argv[1], "r")) == NULL) {

        printf("Не могу открыть файл %s\n", argv[1]);

        return ERR_OPEN_FILE;
    }
    
    if (fread_all(file_ptr, &onegin_f.buf_ptr, &onegin_f.buf_size) < 0) {
        printf("Не могу прочитать текст из файла %s\n", argv[1]);

        return ERR_READ_FILE;
    }
    
    if (create_lines_arr(&onegin_f, '\n') < 0) {
        puts("Не могу разделить буффер на линии");

        return ERR_CREATE_LINES;
    }
    puts("hey");
    
    RET_ASSERT(onegin_f.line_arr == nullptr, ERR_NULL_PTR_ARG);
    printf("%p\n", onegin_f.line_arr);
    for (int i = 0; i < onegin_f.line_arr_size; i++)
        print_line(onegin_f.line_arr + i);


    qsort(onegin_f.line_arr, onegin_f.line_arr_size, sizeof(Line), line_comp);
      //  return ERR_SORT_TEXT;
    for (int i = 0; i < onegin_f.line_arr_size; i++)
        print_line(onegin_f.line_arr + i);

    free_text(&onegin_f);
    // What to do if fclose returns error? Should I repeat it? 
    fclose(file_ptr);

    return 0;   
}