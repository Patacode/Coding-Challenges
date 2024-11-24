#include <stdlib.h>
#include <locale.h>

#include "unity.h"
#include "ccwc.h"
#include "ccwc.spec.h"

char* dynamic_content;

void setUp(void) {
	dynamic_content = NULL;
}

void tearDown(void) {
	free(dynamic_content);
}

/**
 * Test scenarios(count_bytes(str)):
 * - one line containing ASCII characters only
 * - two lines containing ASCII characters only
 * - one line containing ASCII and non-ASCII characters
 */
void test_byte_count_one_line(void)
{
	const char *const str = "Hello, World";
	const size_t actual_byte_count = count_bytes(str);
	const size_t expected_byte_count = 12;

	TEST_ASSERT_EQUAL_size_t(expected_byte_count, actual_byte_count);
}

void test_byte_count_two_lines(void)
{
	const char *const str = "Hello, World\nMy friend !";
	const size_t actual_byte_count = count_bytes(str);
	const size_t expected_byte_count = 24;

	TEST_ASSERT_EQUAL_size_t(expected_byte_count, actual_byte_count);
}

void test_byte_count_one_line_with_non_ascii(void)
{
	const char *const str = "Hello, World 😀 !";
	const size_t actual_byte_count = count_bytes(str);
	const size_t expected_byte_count = 19;

	TEST_ASSERT_EQUAL_size_t(expected_byte_count, actual_byte_count);
}

/**
 * Test scenarios(get_file_content(filename)):
 * - one line containing ASCII characters only
 * - two lines containing ASCII characters only
 * - one line containing ASCII and non-ASCII characters
 * - one line containing ASCII characters and newline char at the end
 * - inexistent file
 */
void test_file_content_retrieval_one_line(void) {
	const char *const filename = "data/ascii_one_line.txt";
	char* actual_file_content = get_file_content(filename);
	const char *const expected_file_content = "hello";

	dynamic_content = actual_file_content;

	TEST_ASSERT_EQUAL_STRING(expected_file_content, actual_file_content);
}

void test_file_content_retrieval_two_lines(void) {
	const char *const filename = "data/ascii_two_lines.txt";
	char* actual_file_content = get_file_content(filename);
	const char *const expected_file_content = "hello\nfriend";

	dynamic_content = actual_file_content;

	TEST_ASSERT_EQUAL_STRING(expected_file_content, actual_file_content);
}

void test_file_content_retrieval_one_line_non_ascii(void) {
	const char *const filename = "data/ascii_one_line_non_ascii.txt";
	char* actual_file_content = get_file_content(filename);
	const char *const expected_file_content = "hello 😀";

	dynamic_content = actual_file_content;

	TEST_ASSERT_EQUAL_STRING(expected_file_content, actual_file_content);
}

void test_file_content_retrieval_one_line_with_newline(void) {
	const char *const filename = "data/ascii_one_line_with_newline.txt";
	char* actual_file_content = get_file_content(filename);
	const char *const expected_file_content = "hello\n";

	dynamic_content = actual_file_content;

	TEST_ASSERT_EQUAL_STRING(expected_file_content, actual_file_content);
}

void test_file_content_retrieval_unknown_file(void) {
	const char *const filename = "data/unknown.txt";
	char* actual_file_content = get_file_content(filename);

	dynamic_content = actual_file_content;

	TEST_ASSERT_NULL(actual_file_content);
}

/**
 * Test scenarios(count_bytes_in_file(filename)):
 * - one line containing ASCII characters only
 * - two lines containing ASCII characters only
 * - one line containing ASCII and non-ASCII characters
 * - one line containing ASCII characters and newline char at the end
 * - inexistent file
 */
void test_byte_count_in_file_one_line(void) {
	const char *const filename = "data/ascii_one_line.txt";
	const ssize_t actual_byte_count = count_bytes_in_file(filename);
	const ssize_t expected_byte_count = 5;

	TEST_ASSERT_EQUAL_INT64(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_two_lines(void) {
	const char *const filename = "data/ascii_two_lines.txt";
	const ssize_t actual_byte_count = count_bytes_in_file(filename);
	const ssize_t expected_byte_count = 12;

	TEST_ASSERT_EQUAL_INT64(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_with_non_ascii(void) {
	const char *const filename = "data/ascii_one_line_non_ascii.txt";
	const ssize_t actual_byte_count = count_bytes_in_file(filename);
	const ssize_t expected_byte_count = 10;

	TEST_ASSERT_EQUAL_INT64(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_with_newline(void) {
	const char *const filename = "data/ascii_one_line_with_newline.txt";
	const ssize_t actual_byte_count = count_bytes_in_file(filename);
	const ssize_t expected_byte_count = 6;

	TEST_ASSERT_EQUAL_INT64(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_unknown_file(void) {
	const char *const filename = "data/unknown.txt";
	const ssize_t actual_byte_count = count_bytes_in_file(filename);
	const ssize_t expected_byte_count = -1;

	TEST_ASSERT_EQUAL_INT64(expected_byte_count, actual_byte_count);
}

/**
 * Test scenarios(count_newlines(str)):
 * - one line with no newline
 * - two lines with one newline
 * - one line with newline
 */
void test_newline_count_one_line_without_newline(void)
{
	const char *const str = "Hello, World";
	const size_t actual_newline_count = count_newlines(str);
	const size_t expected_newline_count = 0;

	TEST_ASSERT_EQUAL_size_t(expected_newline_count, actual_newline_count);
}

void test_newline_count_two_lines_with_one_newline(void)
{
	const char *const str = "Hello, World\nMy friend !";
	const size_t actual_newline_count = count_newlines(str);
	const size_t expected_newline_count = 1;

	TEST_ASSERT_EQUAL_size_t(expected_newline_count, actual_newline_count);
}

void test_newline_count_one_line_with_newline(void)
{
	const char *const str = "Hello, World 😀 !\n";
	const size_t actual_newline_count = count_newlines(str);
	const size_t expected_newline_count = 1;

	TEST_ASSERT_EQUAL_size_t(expected_newline_count, actual_newline_count);
}

/**
 * Test scenarios(count_words(str))
 * - one line with no whitespace
 * - one line with withespaces
 * - one line with withespaces and newline
 * - one line with consecutive withespaces
 * - one line with tabs
 * - one line with one letter words
 * - one line with whitespaces and non-printable chars
 * - two lines with no whitespace
 * - two lines with whitespaces
 * - one line with utf chars
 * - one line with chars not in charset
 */
void test_word_count_one_line_with_no_whitespace(void) {
	const char *const str = "Hello";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 1;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_whitespaces(void) {
	const char *const str = "Hello friend of mine";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 4;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_whitespaces_and_newline(void) {
	const char *const str = "Hello friend of mine\n";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 4;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_consecutive_whitespaces(void) {
	const char *const str = "Hello   friend   of  mine ";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 4;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_tabs(void) {
	const char *const str = "Hello\t friend \t  \tof  mine ";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 4;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_one_letter_words(void) {
	const char *const str = "a  b c\t d \te\tf \t g\t \n";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 7;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_non_printable_chars(void) {
	const char *const str = "Hello \001\002 max";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 2;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_two_lines_without_whitespace(void) {
	const char *const str = "Hello\nfriend";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 2;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_two_lines_with_whitespaces(void) {
	const char *const str = "Hello \n  friend of mine";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 4;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_utf_chars(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello 😀 friend";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 3;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_chars_not_in_charset(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const str = "Hello 😀 friend";
	const size_t actual_word_count = count_words(str);
	const size_t expected_word_count = 2;

	TEST_ASSERT_EQUAL_size_t(expected_word_count, actual_word_count);
}

/**
 * Test scenarios(count_chars(str))
 * - one line with chars in ascii charset
 * - one line with chars in utf charset
 * - one line with chars in utf charset but ascii effective
 * - one line with chars in ascii charset but utf effective
 */
void test_char_count_one_line_with_chars_in_ascii_charset(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const str = "Hello friend";
	const size_t actual_char_count = count_chars(str);
	const size_t expected_char_count = 12;

	TEST_ASSERT_EQUAL_size_t(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_utf_charset(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello friend 😀";
	const size_t actual_char_count = count_chars(str);
	const size_t expected_char_count = 14;

	TEST_ASSERT_EQUAL_size_t(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_utf_charset_but_ascii_locale(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const str = "Hello friend 😀";
	const size_t actual_char_count = count_chars(str);
	const size_t expected_char_count = 17;

	TEST_ASSERT_EQUAL_size_t(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_ascii_charset_but_utf_locale(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello friend";
	const size_t actual_char_count = count_chars(str);
	const size_t expected_char_count = 12;

	TEST_ASSERT_EQUAL_size_t(expected_char_count, actual_char_count);
}

/**
 * Test scenarios(get_stdin_content(void))
 * - retrieve one line
 * - retrieve huge content
 */
void test_get_stdin_content_one_line(void) {
  freopen("data/ascii_one_line.txt", "r", stdin);

	char* actual_stdin_content = get_stdin_content();
	const char *const expected_stdin_content = "hello";

	dynamic_content = actual_stdin_content;

	TEST_ASSERT_EQUAL_STRING(expected_stdin_content, actual_stdin_content);
}

void test_get_stdin_content_huge_content(void) {
	const char* filename = "data/test.txt";
  freopen(filename, "r", stdin);

	char* actual_stdin_content = get_stdin_content();
	const char *const expected_stdin_content = get_file_content(filename);

	dynamic_content = actual_stdin_content;

	TEST_ASSERT_EQUAL_STRING(expected_stdin_content, actual_stdin_content);
}
