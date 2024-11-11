#include <argp.h>
#include <stdbool.h>

#include "ccwc.h"

const char* argp_program_version = "ccwc 1.0.0";
const char* argp_program_bug_address = "<maxou.info@gmail.com>";
static char doc[] = "A simplified clone of wc.";
static char args_doc[] = "FILENAME";

static struct argp_option options[] = {
  {"bytes", 'c', 0, 0, "print the byte counts"},
  { 0 }
};

typedef struct {
  bool count_bytes;
  char* filename;
} Arguments;

static error_t parse_opt(int key, char* arg, struct argp_state *state) {
  Arguments* arguments = state -> input;
  switch (key) {
    case 'c': arguments -> count_bytes = true; break;
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
    default: return ARGP_ERR_UNKNOWN;
  }
  return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv) {
  Arguments arguments;
  arguments.filename = NULL;
  arguments.count_bytes = false;

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if(arguments.count_bytes) {
    const int byte_count = count_bytes_in_file(arguments.filename);
    if(byte_count == -1) {
      return 1;
    } else {
      printf("%d %s\n", byte_count, arguments.filename);      
    }
  }

  return 0;
}
