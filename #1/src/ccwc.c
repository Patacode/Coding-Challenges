#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "ccwc.h"
#include "errors.h"
#include "constants.h"

static bool is_printable_word(const char* word) {
  size_t idx = 0;
  wchar_t wc;
  size_t len;

  while(word[idx] != '\0') {
    len = mbrtowc(&wc, word + idx, MB_CUR_MAX, NULL);
    if(len != (size_t) - 1 && len != (size_t) - 2 && iswprint(wc)) return true;
    idx++;
  }

  return false;
}

static int close_file(FILE* file) {
  int result = fclose(file);
  if(result != 0) perror(ERROR_CLOSING_FILE);
  return result;
}

static long get_file_size(FILE* file) {
  int fseek_result = fseek(file, 0, SEEK_END);
  if(fseek_result != 0) {
    perror(ERROR_SEEKING_FILE);
    return ERROR_FILE_IHANDLING;
  }

  long file_size = ftell(file);
  if(file_size < 0) {
    perror(ERROR_DETERMINING_FILE_SIZE);
    return ERROR_FILE_IHANDLING;
  }

  rewind(file);
  if(ferror(file)) {
    perror(ERROR_REWINDING_FILE);
    return ERROR_FILE_IHANDLING;
  }

  return file_size;
}

size_t count_bytes(const char* str)
{
	size_t idx = 0;
  while(str[idx] != '\0') {
    idx++;
  }

  return idx;
}

ssize_t count_bytes_in_file(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if(file == NULL) {
    perror(ERROR_OPENING_FILE);
    return ERROR_FILE_IHANDLING;
  }

  long file_size = get_file_size(file);
  if(file_size == ERROR_FILE_IHANDLING) {
    close_file(file);
    return ERROR_FILE_IHANDLING;
  }

  int fclose_result = close_file(file);
  if(fclose_result != 0) {
    return ERROR_FILE_IHANDLING;
  }

  return file_size;
}

size_t count_chars(const char* str) {
  size_t idx = 0;
  size_t counter = 0;
  wchar_t wc;
  size_t len;

  while(str[idx] != '\0') {
    len = mbrtowc(&wc, str + idx, MB_CUR_MAX, NULL);
    if(len != (size_t) - 1 && len != (size_t) - 2 && iswprint(wc)) idx += len;
    else idx++;
    counter++;
  }

  return counter;
}

size_t count_words(const char* str) {
  size_t idx = 0;
  size_t counter = 0;
  while(str[idx] != '\0') {
    if(!isspace(str[idx])) {
      size_t jdx = idx;
      while(str[jdx] != '\0' && !isspace(str[jdx])) jdx++;
      const size_t word_size = jdx - idx;
      if(word_size > 0) {
        char current_word[word_size + 1];
        strncpy(current_word, str + idx, word_size);
        current_word[word_size] = '\0';
        if(is_printable_word(current_word)) counter++;
      }
      idx = jdx - 1;
    }
    idx++;
  }

  return counter;
}

size_t count_newlines(const char* str) {
  size_t idx = 0;
  size_t counter = 0;
  while(str[idx] != '\0') {
    if(str[idx] == '\n') counter++;
    idx++;
  }

  return counter;
}

char* get_file_content(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if(file == NULL) {
    perror(ERROR_OPENING_FILE);
    return ERROR_FILE_SHANDLING;
  }

  long file_size = get_file_size(file);
  if(file_size == ERROR_FILE_IHANDLING) {
    close_file(file);
    return ERROR_FILE_SHANDLING;
  }

  char* buffer = (char*) malloc(file_size + 1);
  if(buffer == NULL) {
    perror(ERROR_MEMORY_ALLOCATION);
    close_file(file);
    return ERROR_FILE_SHANDLING;
  }

  size_t read_size = fread(buffer, 1, file_size, file);
  if(read_size != file_size && ferror(file)) {
    perror(ERROR_READING_FILE);
    free(buffer);
    close_file(file);
    return ERROR_FILE_SHANDLING;
  }

  int fclose_result = close_file(file);
  if(fclose_result != 0) {
    free(buffer);
    return ERROR_FILE_SHANDLING;
  }

  buffer[read_size] = '\0';

  return buffer;
}

char* get_stdin_content(void) {
  char *line = NULL;
  char* buffer = (char*) malloc(BLOCK_SIZE + 1);
  if(buffer == NULL) {
    perror(ERROR_MEMORY_ALLOCATION);
    return ERROR_FILE_SHANDLING;
  }

  size_t len = 0;
  ssize_t nread;
  size_t counter = 0;
  size_t buffer_offset = 0;
  size_t buffer_size = BLOCK_SIZE;
  while((nread = getline(&line, &len, stdin)) != -1) {
    counter += nread;
    if(counter >= buffer_size) {
      buffer_size += BLOCK_SIZE;
      char* temp = realloc(buffer, buffer_size);
      if(temp == NULL) {
        perror(ERROR_MEMORY_ALLOCATION);
        free(buffer);
        free(line);
        return ERROR_FILE_SHANDLING;
      } else {
        buffer = temp;
      }
    }
    strcpy(buffer + buffer_offset, line);
    buffer_offset = counter;
  }

  free(line);
  if(ferror(stdin)) {
    perror(ERROR_READING_FROM_STDIN);
    free(buffer);
    return ERROR_FILE_SHANDLING;
  }

  buffer[counter] = '\0';
  return buffer;
}
