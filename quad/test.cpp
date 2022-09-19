#include "quad_test.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    int tests_number = 0;
    char line[20];
    FILE* fp;
    int completed_test = 0;

  if (argc != 2) {

      puts("Вы забыли указать имя файла с тестовыми данными! Правильный формат:");
      puts("quad_test.cpp <filename>");

      return ERR_ARG_NUM;
  }

  if ((fp = fopen(argv[1], "r")) == NULL) {

    printf("Не могу открыть файл %s\n", argv[1]);

    return ERR_OPEN_FILE;
  }

  if (fgets(line, sizeof(line), fp) == NULL) {
    printf("Не могу считать строку из файла %s\n", argv[1]);

    return ERR_READ_LINE;
  } 
  else {
    if (sscanf(line, "%d", &tests_number) != 1) {
      printf("Невалидное число тестов. Пожалуйста, вводите натуральное число тестов, отличное от нуля!");
      return ERR_INV_IN;
    }
  }

  printf("%d\n", tests_number); 

  for (int i = 0; i < tests_number; i++) {
    
    int n, m = 0;
    int num_roots = 0;
    double a, b, c, x_1, x_2, tx_1, tx_2 =  0.0/0.0;

    if ((n = get_test_input(&a, &b, &c, &tx_1, &tx_2, &num_roots, fp)) >= 0) {

      if ((m = solve_eq(a, b, c, &x_1, &x_2)) >= 0) {

        if ((num_roots & m) != NO_SOLUTIONS) {
          if (validate_solutions(num_roots, x_1, x_2, tx_1, tx_2)) {
            completed_test += 1;
            puts("Test passed!");
          }
        }
        else {

          puts("Test passed!");
          completed_test += 1;
        }
      }
      else {

        return n;
      }

    }
    else {

      return n;
    }
    
  }

  printf("Test stat: %d / %d \n", completed_test, tests_number);

}