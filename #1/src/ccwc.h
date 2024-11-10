/**
 * Returns the number of bytes contained in the given string
 * as per the current locale.
 * 
 * - Invalid characters are not counted.
 * - Given string must be NULL-terminated.
 * 
 * @param str the string to be processed
 * @return the number of bytes contained in the given string.
 */
int count_bytes(const char *const str);
