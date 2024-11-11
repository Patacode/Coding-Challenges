#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

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
