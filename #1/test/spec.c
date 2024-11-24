#include "unity.h"
#include "ccwc.spec.h"
#include "parser.spec.h"

int main(void) {
  UNITY_BEGIN();

	// count_bytes(str)
	RUN_TEST(test_byte_count_one_line);
	RUN_TEST(test_byte_count_two_lines);
	RUN_TEST(test_byte_count_one_line_with_non_ascii);

	// get_file_content(filename)
	RUN_TEST(test_file_content_retrieval_one_line);
	RUN_TEST(test_file_content_retrieval_two_lines);
	RUN_TEST(test_file_content_retrieval_one_line_non_ascii);
	RUN_TEST(test_file_content_retrieval_one_line_with_newline);
	RUN_TEST(test_file_content_retrieval_unknown_file);

	// count_bytes_in_file(filename)
	RUN_TEST(test_byte_count_in_file_one_line);
	RUN_TEST(test_byte_count_in_file_two_lines);
	RUN_TEST(test_byte_count_in_file_one_line_with_non_ascii);
	RUN_TEST(test_byte_count_in_file_one_line_with_newline);
	RUN_TEST(test_byte_count_in_file_one_line_unknown_file);

	// count_newlines(str)
	RUN_TEST(test_newline_count_one_line_without_newline);
	RUN_TEST(test_newline_count_two_lines_with_one_newline);
	RUN_TEST(test_newline_count_one_line_with_newline);

	// count_words(str)
	RUN_TEST(test_word_count_one_line_with_no_whitespace);
	RUN_TEST(test_word_count_one_line_with_whitespaces);
	RUN_TEST(test_word_count_one_line_with_whitespaces_and_newline);
	RUN_TEST(test_word_count_one_line_with_consecutive_whitespaces);
	RUN_TEST(test_word_count_one_line_with_tabs);
	RUN_TEST(test_word_count_one_line_with_one_letter_words);
	RUN_TEST(test_word_count_one_line_with_non_printable_chars);
	RUN_TEST(test_word_count_two_lines_without_whitespace);
	RUN_TEST(test_word_count_two_lines_with_whitespaces);
	RUN_TEST(test_word_count_one_line_utf_chars);
	RUN_TEST(test_word_count_one_line_with_chars_not_in_charset);

	// count_chars(str)
	RUN_TEST(test_char_count_one_line_with_chars_in_ascii_charset);
	RUN_TEST(test_char_count_one_line_with_chars_in_utf_charset);
	RUN_TEST(test_char_count_one_line_with_chars_in_utf_charset_but_ascii_locale);
	RUN_TEST(test_char_count_one_line_with_chars_in_ascii_charset_but_utf_locale);

 	// get_stdin_content(void)
	RUN_TEST(test_get_stdin_content_one_line);
	RUN_TEST(test_get_stdin_content_huge_content);

  // count_flag_setter(&args, key)
  RUN_TEST(test_count_flag_setter_valid_key_l);
  RUN_TEST(test_count_flag_setter_valid_key_w);
  RUN_TEST(test_count_flag_setter_valid_key_m);
  RUN_TEST(test_count_flag_setter_valid_key_c);
  RUN_TEST(test_count_flag_setter_multiple_valid_keys);
	RUN_TEST(test_count_flag_setter_invalid_key);
	RUN_TEST(test_count_flag_setter_valid_key_with_flag_counter_at_1);

	// parse_opt(key, arg, state)
	RUN_TEST(test_parse_opt_valid_key);
	RUN_TEST(test_parse_opt_valid_key_with_one_positional_argument);
	RUN_TEST(test_parse_opt_valid_key_with_more_than_one_positional_argument);
	RUN_TEST(test_parse_opt_valid_key_with_no_positional_argument);
	RUN_TEST(test_parse_opt_invalid_key);

	// parse_args(&argp, argc, argv, args)
	RUN_TEST(test_parse_args_valid_arguments_with_no_flag);

	// process_args(args)
	RUN_TEST(test_process_args_valid_arguments_with_multiple_flags);
	RUN_TEST(test_process_args_valid_arguments_with_content_from_stdin);
	RUN_TEST(test_process_args_valid_arguments_with_content_from_file);
	RUN_TEST(test_process_args_valid_arguments_with_inexistent_file);

	return UNITY_END();
}