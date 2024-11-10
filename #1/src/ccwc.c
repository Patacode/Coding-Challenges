#include <stddef.h>

#include "ccwc.h"

int count_bytes(const char *const str)
{
	int idx = 0;
  while(str[idx] != '\0') {
    idx++;
  }

  return idx;
}

const char *const get_file_content(const char *const filename) {
  return "hello";
}
