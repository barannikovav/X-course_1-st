#ifndef ERRCODES_
#define ERRCODES_

#define RET_ASSERT(expr, errnum) \
	if (expr) \
		return errnum

enum error_codes {
    ERR_ARG_NUM = -1,   // Error code -1 - wrong number of arguments
    ERR_OPEN_FILE = -2, // Error code -2 - can't open file
    ERR_ALL_MEM = -3,    // Error code -3 - can't allocate memory
    ERR_READ_FILE = -4,  // Error code -4 - can't read file
    ERR_NULL_PTR_ARG = -5,   // Error code -5 - function pointer argument is nullptr
    ERR_CREATE_LINES = -6,  // Error code -6 - can't create array of lines
    ERR_COUNT_SYM = -7,     // Error code -7 - can't count symbol appearances
    ERR_SORT_TEXT = -8,    // Error code -8 - can't sort text
    ERR_PRINT_LINE = -9,  // Error code -9 - can't print  line
    ERROR_TEXT_FWRITE = -10, // Error code -10 - can't write text to file
};

#endif