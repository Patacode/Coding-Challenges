#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "ccwc.h"

const char* argp_program_version = "ccwc 1.0.0";
const char* argp_program_bug_address = "<maxou.info@gmail.com>";
static char doc[] = "A simplified clone of wc.";
static char args_doc[] = "FILENAME";

static struct argp_option options[] = {
  {"bytes", 'c', 0, 0, "print the byte counts"},
  {"lines", 'l', 0, 0, "print the newline counts"},
  {"words", 'w', 0, 0, "print the word counts"},
  {"chars", 'm', 0, 0, "print the character counts"},
  { 0 }
};

typedef struct {
  bool count_bytes;
  bool count_lines;
  bool count_words;
  bool count_chars;
  char count_flags[4];
  char* filename;
} Arguments;

bool set_count(Arguments *const arguments, int key) {
  int flag_idx = -1;
  switch(key) {
    case 'l': arguments -> count_lines = true; flag_idx = 0; break;
    case 'w': arguments -> count_words = true; flag_idx = 1; break;
    case 'm': arguments -> count_chars = true; flag_idx = 2; break;
    case 'c': arguments -> count_bytes = true; flag_idx = 3; break;
  }

  bool is_valid_key = flag_idx != -1;
  if(is_valid_key) {
    arguments -> count_flags[flag_idx] = key;
  }

  return is_valid_key;
}

static error_t parse_opt(int key, char* arg, struct argp_state *state) {
  Arguments* arguments = state -> input;
  bool was_valid_key = set_count(arguments, key);

  switch (key) {
    case ARGP_KEY_ARG:
      if(state -> arg_num == 0) {
        arguments -> filename = arg;
      } else {
        argp_usage(state);
      }
      break;
    case ARGP_KEY_END:
      if(state -> arg_num < 1) {
        argp_usage(state);
      }
      break;
    default: if(!was_valid_key) return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int process_args(const Arguments *const arguments) {
  char* file_content = get_file_content(arguments -> filename);
  if(file_content == NULL) {
    return 1;
  }

  int flag_idx = 0;
  int count_value_idx = 0;
  int count_values[4];
  while(flag_idx < 4) {
    char current_count_flag = arguments -> count_flags[flag_idx];
    if(current_count_flag != '\0') {
      switch(current_count_flag) {
        case 'l':
          const int newline_count = count_newlines(file_content);
          count_values[count_value_idx] = newline_count;
          count_value_idx++;
          break;
        case 'w':
          const int word_count = count_words(file_content);
          count_values[count_value_idx] = word_count;
          count_value_idx++;
          break;
        case 'm':
          const int char_count = count_chars(file_content);
          count_values[count_value_idx] = char_count;
          count_value_idx++;
          break;
        case 'c':
          const int byte_count = count_bytes_in_file(arguments -> filename);
          if(byte_count == -1) return 1;
          count_values[count_value_idx] = byte_count;
          count_value_idx++;
          break;
      }
    }

    flag_idx++;
  }

  for(int i = 0; i < count_value_idx; i++) printf("%d ", count_values[i]);
  printf("%s\n", arguments -> filename);

  free(file_content);
  return 0;
}

int main(int argc, char **argv) {
  setlocale(LC_CTYPE, "");

  Arguments arguments;
  arguments.filename = NULL;
  arguments.count_bytes = false;
  arguments.count_lines = false;
  arguments.count_words = false;
  arguments.count_chars = false;

  strcpy(arguments.count_flags, "\0\0\0\0");
  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if(arguments.count_flags[0] == '\0') {
    arguments.count_flags[0] = 'l';
    arguments.count_flags[1] = 'w';
    arguments.count_flags[2] = 'c';
  }

  return process_args(&arguments);
}
