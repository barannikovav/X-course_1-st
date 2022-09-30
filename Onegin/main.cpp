#include "errcodes.h"
#include "Filework.h"
#include "onegin.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *main_file_ptr = nullptr;
    FILE *sort_file_ptr = nullptr;
    FILE *reverse_sort_file_ptr = nullptr;
    Text onegin_f = {};
    size_t buf_size = 0;

    if (argc != 2) {

        puts("Вы забыли указать имя файла для сортировки! Правильный формат:");
        puts("main.cpp <filename>");

        return ERR_ARG_NUM;
    }

    if ((main_file_ptr = fopen(argv[1], "r")) == NULL) {

        printf("Не могу открыть файл %s\n", argv[1]);

        return ERR_OPEN_FILE;
    }
    
    if (fread_all(main_file_ptr, &onegin_f.buf_ptr, &onegin_f.buf_size) < 0) {
        printf("Не могу прочитать текст из файла %s\n", argv[1]);

        return ERR_READ_FILE;
    }
    
    if (create_lines_arr(&onegin_f, '\n') < 0) {
        puts("Не могу разделить буффер на линии");

        return ERR_CREATE_LINES;
    }

    
    RET_ASSERT(onegin_f.line_arr == nullptr, ERR_NULL_PTR_ARG);

    qsort(onegin_f.line_arr, onegin_f.line_arr_size, sizeof(Line), line_comp);
      //  return ERR_SORT_TEXT;

    if ((sort_file_ptr = fopen("sorted_file.txt", "w")) == NULL) {

        puts("Не могу открыть файл для записи сортированной версии");

        return ERR_OPEN_FILE;
    }

    if (fprint_text(&onegin_f, sort_file_ptr) != onegin_f.line_arr_size)
        return ERROR_TEXT_FWRITE;

    //qsort(onegin_f.line_arr, onegin_f.line_arr_size, sizeof(Line), line_comp_reverse);
    bubble_sort(onegin_f.line_arr, onegin_f.line_arr_size, sizeof(Line), line_comp_reverse);
      //  return ERR_SORT_TEXT;

    if ((reverse_sort_file_ptr = fopen("reverse_sorted_file.txt", "w")) == NULL) {

        puts("Не могу открыть файл для записи реверсивно-сортированной версии");

        return ERR_OPEN_FILE;
    }

    if (fprint_text(&onegin_f, reverse_sort_file_ptr) != onegin_f.line_arr_size)
        return ERROR_TEXT_FWRITE;

    

    free_text(&onegin_f);
    // What to do if fclose returns error? Should I repeat it? 
    fclose(main_file_ptr);
    fclose(sort_file_ptr);
    fclose(reverse_sort_file_ptr);

    return 0;   
}