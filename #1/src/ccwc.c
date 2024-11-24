#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "ccwc.h"

size_t count_bytes(const char* str)
{
	size_t idx = 0;
  while(str[idx] != '\0') {
    idx++;
  }

  return idx;
}

char* get_file_content(const char* filename) {
  FILE* file = fopen(filename, "rb"); // Open the file in binary read mode
  if(file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  rewind(file);

  if(file_size < 0) {
    perror("Error determining file size");
    fclose(file);
    return NULL;
  }

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

ssize_t count_bytes_in_file(const char* filename) {
  FILE* file = fopen(filename, "rb");
  if(file == NULL) {
    perror("Error opening file");
    return -1;
  }

  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fclose(file);

  if(file_size < 0) {
    perror("Error determining file size");
    return -1;
  }

  return file_size;
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

bool is_printable_word(const char* word) {
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

char* get_stdin_content(void) {
  char *line = NULL;
  const size_t block_size = 1024;
  char* buffer = (char*) malloc(block_size + 1);
  if(buffer == NULL) {
    perror("Memory allocation error");
    return NULL;
  }

  size_t len = 0;
  ssize_t nread;
  size_t counter = 0;
  size_t buffer_offset = 0;
  size_t buffer_size = block_size;
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
