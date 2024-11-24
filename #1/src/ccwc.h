#ifndef CCWC_H
#define CCWC_H

#include <stdbool.h>
#include <sys/types.h>

/**
 * Counts the number of bytes contained in the given string.
 * 
 * - Given string must be null-terminated.
 * 
 * @param str the string to be processed
 * @return the number of bytes contained in the given string.
 */
size_t count_bytes(const char* str);

/**
 * Counts the number of bytes contained in the pointed file.
 * 
 * @param filename the name of the file to be processed
 * @return the number of bytes contained in the pointed file, or -1 if an error occured.
 */
ssize_t count_bytes_in_file(const char* filename);

/**
 * Counts the number of chars contained in the given string, as per
 * current locale.
 * 
 * - Given string must be NULL-terminated.
 * 
 * - Invalid characters are not counted.
 * 
 * @param str the string to be processed
 * @return the number of chars contained in the given string.
 */
size_t count_chars(const char* str);

/**
 * Counts the number of words contained in the given string.
 * 
 * - Given string must be NULL-terminated.
 * 
 * - A word is a non-zero-length sequence of printable characters
 * delimited by white space.
 * 
 * @param str the string to be processed
 * @return the number of words contained in the given string.
 */
size_t count_words(const char* str);

/**
 * Counts the number of newlines contained in the given string.
 * 
 * - Given string must be null-terminated.
 * 
 * @param str the string to be processed
 * @return the number of newlines contained in the given string.
 */
size_t count_newlines(const char* str);

/**
 * Reads all the character contained in the pointed file.
 * 
 * - The returned char pointer is referring to a dynamically allocated
 * memory space. It is then up to the client code not to forget to
 * free up this part of memory.
 * 
 * @param filename the name of the file to be processed
 * @return the content of the pointed file.  
 */
char* get_file_content(const char* filename);

/**
 * Reads all the character contained in stdin.
 * 
 * - The returned char pointer is referring to a dynamically allocated
 * memory space. It is then up to the client code not to forget to
 * free up this part of memory.
 * 
 * @return the content of stdin.  
 */
char* get_stdin_content(void);

#endif /* CCWC_H */
