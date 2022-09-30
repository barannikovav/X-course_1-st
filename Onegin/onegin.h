#ifndef ONEGIN_
#define ONEGIN_

#include <stddef.h>

//const int *poison_ptr = 0xdead; 

struct Line {
    char *ptr = nullptr;
    size_t len = 0;
};

struct Text {
    char *buf_ptr = nullptr;
    size_t buf_size = 0;
    Line *line_arr = nullptr;
    size_t line_arr_size = 0;
};

struct line_arr {
    struct Line **arr = nullptr;
    size_t len = 0;
};

 
/**
	*	@brief This function counts number of occurrences of the symbol in the buffer
    *   @param symbol Symbol for couting
    *   @param buffer Pointer to char array where to count
    * 
    *   @return number of occurences, or error code
    */ 

size_t count_symbol(const char symbol, const char *buffer);

/**
	*	@brief This function creates array of lines from char buffer (text) according to separator
    *   @param file Struct which stores file info, ptr to array of lines in particular
    *   @param separator Separator for char buffer (text)
    * 
    *   @return number of lines, or error code
    */ 

size_t create_lines_arr(Text *f, const char separator);

/**
	*	@brief This function prints line from it's ptr
    *   @param l line to print
    * 
    *   @return number of printed symbols, or error code
    */ 

size_t print_line (Line * l);


/**
	*	@brief This function checks if argument symbol is ASCII latin letter
    *   @param symbol Ptr to symbol to check
    * 
    *   @return Return 1 if True and 0 if False
    */ 

size_t is_letter(const unsigned char * symbol);


/**
	*	@brief This is comparator function for line struct
    *   @param ptr_1 Ptr to first line
    *   @param ptr_2 Ptr to second line
    * 
    *   @return Returning less than, equal to or
                greater than zero if line_1 is lexicographically less than,
                equal to or greater than line_2
    */ 

int line_comp (const void *ptr_1, const void *ptr_2);

/**
	*	@brief This function frees all allocated resources of file structure
    *   @param file Struct which stores file info
    * 
    *   @return Does not return a value
    */ 

void free_text(struct Text * f);

#endif