#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <sysexits.h>

#include "parser.h"

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

static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv) {
  setlocale(LC_CTYPE, "");

  Arguments arguments = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };

  argp_parse(&argp, argc, argv, 0, 0, &arguments);

  if(arguments.flag_counter == 0) {
    arguments.count_flags[0] = 'l';
    arguments.count_flags[1] = 'w';
    arguments.count_flags[2] = 'c';
  }

  return process_args(&arguments);
}
