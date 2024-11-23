#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include <sys/types.h>

#include "ccwc.h"

int count_bytes(const char *const str)
{
	int idx = 0;
  while(str[idx] != '\0') {
    idx++;
  }

  return idx;
}

char* get_file_content(const char *const filename) {
  FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
  if(file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  char* buffer = (char*) malloc(file_size + 1);
  if(buffer == NULL) {
    perror("Memory allocation error");
    fclose(file);
    return NULL;
  }

  fread(buffer, 1, file_size, file);
  buffer[file_size] = '\0';
  fclose(file);
  return buffer;
}

int count_bytes_in_file(const char *const filename) {
  FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
  if(file == NULL) {
    perror("Error opening file");
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fclose(file);

  return file_size;
}

int count_newlines(const char *const str) {
  int idx = 0;
  int counter = 0;
  while(str[idx] != '\0') {
    if(str[idx] == '\n') counter++;
    idx++;
  }

  return counter;
}

bool is_printable_word(const char *const word) {
  int idx = 0;
  wchar_t wc;
  size_t len;

  while(word[idx] != '\0') {
    len = mbrtowc(&wc, word + idx, MB_CUR_MAX, NULL);
    if(len != (size_t) - 1 && len != (size_t) - 2 && iswprint(wc)) return true;
    idx++;
  }

  return false;
}

int count_words(const char *const str) {
  int idx = 0;
  int counter = 0;
  while(str[idx] != '\0') {
    if(!isspace(str[idx])) {
      int jdx = idx;
      while(str[jdx] != '\0' && !isspace(str[jdx])) jdx++;
      const int word_size = jdx - idx;
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

int count_chars(const char *const str) {
  int idx = 0;
  int counter = 0;
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

char* get_stdin_content(void) {
  char *line = NULL;
  const int block_size = 1024;
  char* buffer = (char*) malloc(block_size + 1);
  if(buffer == NULL) {
    perror("Memory allocation error");
    return NULL;
  }

  size_t len = 0;
  ssize_t nread;
  long counter = 0;
  long buffer_offset = 0;
  long buffer_size = block_size;
  while((nread = getline(&line, &len, stdin)) != -1) {
    counter += nread;
    if(counter >= buffer_size) {
      buffer_size += block_size;
      char* temp = realloc(buffer, buffer_size);
      if(temp == NULL) {
        perror("Memory allocation error");
        free(buffer);
        free(line);
        return NULL;
      } else {
        buffer = temp;
      }
    }
    strcpy(buffer + buffer_offset, line);
    buffer_offset = counter;
  }

  free(line);
  if(ferror(stdin)) {
    perror("Error reading from stdin");
    free(buffer);
    return NULL;
  }

  buffer[counter] = '\0';
  return buffer;
}
