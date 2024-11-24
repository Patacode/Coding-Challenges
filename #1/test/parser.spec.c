#include <stdbool.h>
#include <sysexits.h>

#include "parser.h"
#include "unity.h"

/**
 * Test scenarios(count_flag_setter(&args, key)):
 * - valid key l
 * - valid key w
 * - valid key m
 * - valid key c
 * - multiple valid keys
 * - invalid key
 * - valid key with flag_counter at 1
 */
void test_count_flag_setter_valid_key_l(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'l');

  TEST_ASSERT_TRUE(actual_result);
  TEST_ASSERT_EQUAL_size_t(1, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('l', args.count_flags[0]);
}

void test_count_flag_setter_valid_key_w(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'w');

  TEST_ASSERT_TRUE(actual_result);
  TEST_ASSERT_EQUAL_size_t(1, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('w', args.count_flags[1]);
}

void test_count_flag_setter_valid_key_m(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'm');

  TEST_ASSERT_TRUE(actual_result);
  TEST_ASSERT_EQUAL_size_t(1, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('m', args.count_flags[2]);
}

void test_count_flag_setter_valid_key_c(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'c');

  TEST_ASSERT_TRUE(actual_result);
  TEST_ASSERT_EQUAL_size_t(1, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('c', args.count_flags[3]);
}

void test_count_flag_setter_multiple_valid_keys(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'l');
  TEST_ASSERT_TRUE(actual_result);

  actual_result = count_flag_setter(&args, 'w');
  TEST_ASSERT_TRUE(actual_result);

  actual_result = count_flag_setter(&args, 'm');
  TEST_ASSERT_TRUE(actual_result);

  actual_result = count_flag_setter(&args, 'c');
  TEST_ASSERT_TRUE(actual_result);

  TEST_ASSERT_EQUAL_size_t(4, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('l', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('w', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('m', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('c', args.count_flags[3]);
}

void test_count_flag_setter_invalid_key(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'x');

  TEST_ASSERT_FALSE(actual_result);
  TEST_ASSERT_EQUAL_size_t(0, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[3]);
}

void test_count_flag_setter_valid_key_with_flag_counter_at_1(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 1,
    .count_flags = {'l', '\0', '\0', '\0'}
  };
  bool actual_result = count_flag_setter(&args, 'w');

  TEST_ASSERT_TRUE(actual_result);
  TEST_ASSERT_EQUAL_size_t(2, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('w', args.count_flags[1]);
}

/**
 * Test scenarios(parse_opt(key, arg, state)):
 * - valid key
 * - valid key with one positional argument
 * - valid key with more than one positional argument
 * - valid key with no positional argument
 * - invalid key
 */
void test_parse_opt_valid_key(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  struct argp_state state = {
    .input = &args
  };
  error_t actual_result = parse_opt('l', NULL, &state);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
  TEST_ASSERT_EQUAL_STRING(NULL, args.filename);
  TEST_ASSERT_FALSE(args.is_from_stdin);
  TEST_ASSERT_EQUAL_size_t(1, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('l', args.count_flags[0]);
}

void test_parse_opt_valid_key_with_one_positional_argument(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  struct argp_state state = {
    .input = &args,
    .arg_num = 0
  };
  error_t actual_result = parse_opt(ARGP_KEY_ARG, "file.txt", &state);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
  TEST_ASSERT_EQUAL_STRING("file.txt", args.filename);
  TEST_ASSERT_FALSE(args.is_from_stdin);
  TEST_ASSERT_EQUAL_size_t(0, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[3]);
}

void test_parse_opt_valid_key_with_more_than_one_positional_argument(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  struct argp_state state = {
    .input = &args,
    .arg_num = 1
  };
  error_t actual_result = parse_opt(ARGP_KEY_ARG, "file.txt", &state);

  TEST_ASSERT_EQUAL_INT(EX_USAGE, actual_result);
  TEST_ASSERT_EQUAL_STRING(NULL, args.filename);
  TEST_ASSERT_FALSE(args.is_from_stdin);
  TEST_ASSERT_EQUAL_size_t(0, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[3]);
}

void test_parse_opt_valid_key_with_no_positional_argument(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  struct argp_state state = {
    .input = &args,
    .arg_num = 0
  };
  error_t actual_result = parse_opt(ARGP_KEY_END, NULL, &state);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
  TEST_ASSERT_EQUAL_STRING(NULL, args.filename);
  TEST_ASSERT_TRUE(args.is_from_stdin);
  TEST_ASSERT_EQUAL_size_t(0, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[3]);
}

void test_parse_opt_invalid_key(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  struct argp_state state = {
    .input = &args
  };
  error_t actual_result = parse_opt('x', NULL, &state);

  TEST_ASSERT_EQUAL_INT(ARGP_ERR_UNKNOWN, actual_result);
  TEST_ASSERT_EQUAL_STRING(NULL, args.filename);
  TEST_ASSERT_FALSE(args.is_from_stdin);
  TEST_ASSERT_EQUAL_size_t(0, args.flag_counter);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[3]);
}

/**
 * Test scenarios(parse_args(&argp, argc, argv, args)):
 * - valid arguments with no flag
 */
void test_parse_args_valid_arguments_with_no_flag(void) {
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = false,
    .flag_counter = 0,
    .count_flags = {'\0', '\0', '\0', '\0'}
  };
  char* argv[] = { "./ccwc" };
  struct argp_option options[] = {
    {"dummy", 'd', 0, 0, "dummy option"},
    { 0 }
  };
  struct argp argp = {
    .options = options
  };
  parse_args(&argp, 1, argv, &args);

  TEST_ASSERT_EQUAL_CHAR('l', args.count_flags[0]);
  TEST_ASSERT_EQUAL_CHAR('w', args.count_flags[1]);
  TEST_ASSERT_EQUAL_CHAR('\0', args.count_flags[2]);
  TEST_ASSERT_EQUAL_CHAR('c', args.count_flags[3]);
}

/**
 * Test scenarios(process_args(args)):
 * - valid arguments with multiple flags
 * - valid arguments with content from stdin
 * - valid arguments with content from file
 * - valid arguments with inexistent file
 */
void test_process_args_valid_arguments_with_multiple_flags(void) {
  Arguments args = {
    .filename = "data/ascii_one_line.txt",
    .is_from_stdin = false,
    .flag_counter = 4,
    .count_flags = {'l', 'w', 'm', 'c'}
  };
  int actual_result = process_args(&args);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
}

void test_process_args_valid_arguments_with_content_from_stdin(void) {
  freopen("data/ascii_one_line.txt", "r", stdin);
  Arguments args = {
    .filename = NULL,
    .is_from_stdin = true,
    .flag_counter = 4,
    .count_flags = {'l', 'w', 'm', 'c'}
  };
  int actual_result = process_args(&args);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
}

void test_process_args_valid_arguments_with_content_from_file(void) {
  Arguments args = {
    .filename = "data/ascii_one_line.txt",
    .is_from_stdin = false,
    .flag_counter = 4,
    .count_flags = {'l', 'w', 'm', 'c'}
  };
  int actual_result = process_args(&args);

  TEST_ASSERT_EQUAL_INT(0, actual_result);
}

void test_process_args_valid_arguments_with_inexistent_file(void) {
  Arguments args = {
    .filename = "data/unknown.txt",
    .is_from_stdin = false,
    .flag_counter = 4,
    .count_flags = {'l', 'w', 'm', 'c'}
  };
  int actual_result = process_args(&args);

  TEST_ASSERT_EQUAL_INT(1, actual_result);
}
