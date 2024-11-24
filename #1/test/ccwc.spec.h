#ifndef CCWC_SPEC_H
#define CCWC_SPEC_H

// count_bytes()
void test_byte_count_one_line(void);
void test_byte_count_two_lines(void);
void test_byte_count_one_line_with_non_ascii(void);

// get_file_content()
void test_file_content_retrieval_one_line(void);
void test_file_content_retrieval_two_lines(void);
void test_file_content_retrieval_one_line_non_ascii(void);
void test_file_content_retrieval_one_line_with_newline(void);
void test_file_content_retrieval_unknown_file(void);

// count_bytes_in_file()
void test_byte_count_in_file_one_line(void);
void test_byte_count_in_file_two_lines(void);
void test_byte_count_in_file_one_line_with_non_ascii(void);
void test_byte_count_in_file_one_line_with_newline(void);
void test_byte_count_in_file_one_line_unknown_file(void);

// count_newlines()
void test_newline_count_one_line_without_newline(void);
void test_newline_count_two_lines_with_one_newline(void);
void test_newline_count_one_line_with_newline(void);

// count_words()
void test_word_count_one_line_with_no_whitespace(void);
void test_word_count_one_line_with_whitespaces(void);
void test_word_count_one_line_with_whitespaces_and_newline(void);
void test_word_count_one_line_with_consecutive_whitespaces(void);
void test_word_count_one_line_with_tabs(void);
void test_word_count_one_line_with_one_letter_words(void);
void test_word_count_one_line_with_non_printable_chars(void);
void test_word_count_two_lines_without_whitespace(void);
void test_word_count_two_lines_with_whitespaces(void);
void test_word_count_one_line_utf_chars(void);
void test_word_count_one_line_with_chars_not_in_charset(void);

// count_chars()
void test_char_count_one_line_with_chars_in_ascii_charset(void);
void test_char_count_one_line_with_chars_in_utf_charset(void);
void test_char_count_one_line_with_chars_in_utf_charset_but_ascii_locale(void);
void test_char_count_one_line_with_chars_in_ascii_charset_but_utf_locale(void);

// get_stdin_content()
void test_get_stdin_content_one_line(void);
void test_get_stdin_content_huge_content(void);

#endif // CCWC_SPEC_H
