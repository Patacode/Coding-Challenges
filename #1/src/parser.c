#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>

#include "parser.h"
#include "ccwc.h"

bool count_flag_setter(Arguments* args, int key) {
  int flag_idx = -1;
  switch(key) {
    case 'l': flag_idx = 0; break;
    case 'w': flag_idx = 1; break;
    case 'm': flag_idx = 2; break;
    case 'c': flag_idx = 3; break;
  }

  bool is_valid_key = flag_idx != -1;
  if(is_valid_key) {
    args -> flag_counter++;
    args -> count_flags[flag_idx] = (char) key;
  }

  return is_valid_key;
}

error_t parse_opt(int key, char* arg, struct argp_state *state) {
  Arguments* args = state -> input;
  bool was_valid_key = count_flag_setter(args, key);

  switch (key) {
    case ARGP_KEY_ARG:
      if(state -> arg_num == 0) {
        args -> filename = arg;
      } else {
        argp_usage(state);
      }
      break;
    case ARGP_KEY_END:
      if(state -> arg_num < 1) {
        args -> is_from_stdin = true;
      }
      break;
    default: if(!was_valid_key) return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

void parse_args(const struct argp* argp, int argc, char** argv, Arguments* args) {
  argp_parse(argp, argc, argv, 0, 0, args);

  if(args -> flag_counter == 0) {
    args -> count_flags[0] = 'l';
    args -> count_flags[1] = 'w';
    args -> count_flags[2] = 'c';
  }
}

int process_args(const Arguments* args) {
  char* file_content;
  if(args -> is_from_stdin) {
    file_content = get_stdin_content();
  } else {
    file_content = get_file_content(args -> filename);
  }
  if(file_content == NULL) {
    return 1;
  }

  int flag_idx = 0;
  int count_value_idx = 0;
  size_t count_values[4];
  while(flag_idx < 4) {
    char current_count_flag = args -> count_flags[flag_idx];
    if(current_count_flag != '\0') {
      size_t count_value = 0;
      switch(current_count_flag) {
        case 'l':
          count_value = count_newlines(file_content);
          break;
        case 'w':
          count_value = count_words(file_content);
          break;
        case 'm':
          count_value = count_chars(file_content);
          break;
        case 'c':
          if(args -> is_from_stdin) {
            count_value = count_bytes(file_content);
          } else {
            ssize_t tmp_byte_count = count_bytes_in_file(args -> filename);
            if(tmp_byte_count == -1) return 1;
            count_value = (size_t) tmp_byte_count;
          }
          break;
      }
      count_values[count_value_idx] = count_value;
      count_value_idx++;
    }

    flag_idx++;
  }

  for(int i = 0; i < count_value_idx; i++) printf("%zu ", count_values[i]);
  if(args -> is_from_stdin) printf("\n");
  else printf("%s\n", args -> filename);

  free(file_content);
  return 0;
}
