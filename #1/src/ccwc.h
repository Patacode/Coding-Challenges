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
