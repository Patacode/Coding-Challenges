#include <stdbool.h>

/**
 * Counts the number of bytes contained in the given string.
 * 
 * - Given string must be NULL-terminated.
 * 
 * @param str the string to be processed
 * @return the number of bytes contained in the given string.
 */
int count_bytes(const char *const str);

/**
 * Counts the number of newlines contained in the given string.
 * 
 * - Given string must be NULL-terminated.
 * 
 * @param str the string to be processed
 * @return the number of newlines contained in the given string.
 */
int count_newlines(const char *const str);

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
int count_words(const char *const str);

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
char* get_file_content(const char *const filename);

/**
 * Counts the number of bytes contained in the pointed file.
 * 
 * @param filename the name of the file to be processed
 * @return the number of bytes contained in the pointed file.
 */
int count_bytes_in_file(const char *const filename);

/**
 * Checks if given word is printable as per current locale.
 * 
 * @param word the word to be checked
 * @return true if given word is printable, false otherwise. 
 */
bool is_printable_word(const char *const word);
