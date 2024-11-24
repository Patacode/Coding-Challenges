#include <argp.h>
#include <stdbool.h>
#include <locale.h>

#include "parser.h"
#include "constants.h"

const char* argp_program_version = "ccwc 1.0.0";
const char* argp_program_bug_address = "<maxou.info@gmail.com>";
static char doc[] = "A simplified clone of wc.";
static char args_doc[] = "[FILENAME]";

static struct argp_option options[] = {
  {"bytes", BYTE_FLAG, 0, 0, "print the byte counts"},
  {"lines", LINE_FLAG, 0, 0, "print the newline counts"},
  {"words", WORD_FLAG, 0, 0, "print the word counts"},
  {"chars", CHAR_FLAG, 0, 0, "print the character counts"},
  { 0 }
};

static error_t parse_opt_wrapper(int key, char* arg, struct argp_state* state) {
  error_t result = parse_opt(key, arg, state);
  if(result == argp_err_exit_status) argp_usage(state);
  return result;
}

static struct argp argp = { options, parse_opt_wrapper, args_doc, doc };

int main(int argc, char **argv) {
  setlocale(LC_CTYPE, "");

  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };

  parse_args(&argp, argc, argv, &args);
  return process_args(&args);
}
