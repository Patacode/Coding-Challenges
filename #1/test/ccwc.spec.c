#include <stdlib.h>
#include <locale.h>

#include "unity.h"
#include "ccwc.h"

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
	const int actual_byte_count = count_bytes(str);
	const int expected_byte_count = 12;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_two_lines(void)
{
	const char *const str = "Hello, World\nMy friend !";
	const int actual_byte_count = count_bytes(str);
	const int expected_byte_count = 24;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_one_line_with_non_ascii(void)
{
	const char *const str = "Hello, World 😀 !";
	const int actual_byte_count = count_bytes(str);
	const int expected_byte_count = 19;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
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
	const int actual_byte_count = count_bytes_in_file(filename);
	const int expected_byte_count = 5;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_two_lines(void) {
	const char *const filename = "data/ascii_two_lines.txt";
	const int actual_byte_count = count_bytes_in_file(filename);
	const int expected_byte_count = 12;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_with_non_ascii(void) {
	const char *const filename = "data/ascii_one_line_non_ascii.txt";
	const int actual_byte_count = count_bytes_in_file(filename);
	const int expected_byte_count = 10;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_with_newline(void) {
	const char *const filename = "data/ascii_one_line_with_newline.txt";
	const int actual_byte_count = count_bytes_in_file(filename);
	const int expected_byte_count = 6;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

void test_byte_count_in_file_one_line_unknown_file(void) {
	const char *const filename = "data/unknown.txt";
	const int actual_byte_count = count_bytes_in_file(filename);
	const int expected_byte_count = -1;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
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
	const int actual_newline_count = count_newlines(str);
	const int expected_newline_count = 0;

	TEST_ASSERT_EQUAL_INT(expected_newline_count, actual_newline_count);
}

void test_newline_count_two_lines_with_one_newline(void)
{
	const char *const str = "Hello, World\nMy friend !";
	const int actual_newline_count = count_newlines(str);
	const int expected_newline_count = 1;

	TEST_ASSERT_EQUAL_INT(expected_newline_count, actual_newline_count);
}

void test_newline_count_one_line_with_newline(void)
{
	const char *const str = "Hello, World 😀 !\n";
	const int actual_newline_count = count_newlines(str);
	const int expected_newline_count = 1;

	TEST_ASSERT_EQUAL_INT(expected_newline_count, actual_newline_count);
}

/**
 * Test scenarios(is_printable_word(word))
 * - word containing printable ascii chars
 * - word containing printable ascii and non-ascii chars
 * - word containing non-printable chars
 * - word containing printable and non-printable chars
 * - word containing chars not in charset and in charset
 * - word containing chars not in charset only
 */
void test_word_printability_ascii_only(void) {
	const char *const word = "Hello";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_TRUE(actual_result);
}

void test_word_printability_utf(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const word = "Hello😀";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_TRUE(actual_result);
}

void test_word_printability_non_printables(void) {
	const char *const word = "\001\002";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_FALSE(actual_result);
}

void test_word_printability_non_printables_and_printables(void) {
	const char *const word = "Hello\001\002";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_TRUE(actual_result);
}

void test_word_printability_chars_not_in_charset_and_in_charset(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const word = "Hello😀ss";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_TRUE(actual_result);
}

void test_word_printability_chars_not_in_charset(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const word = "™😀";
	const bool actual_result = is_printable_word(word);

	TEST_ASSERT_FALSE(actual_result);
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
	const int actual_word_count = count_words(str);
	const int expected_word_count = 1;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_whitespaces(void) {
	const char *const str = "Hello friend of mine";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 4;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_whitespaces_and_newline(void) {
	const char *const str = "Hello friend of mine\n";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 4;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_consecutive_whitespaces(void) {
	const char *const str = "Hello   friend   of  mine ";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 4;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_tabs(void) {
	const char *const str = "Hello\t friend \t  \tof  mine ";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 4;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_one_letter_words(void) {
	const char *const str = "a  b c\t d \te\tf \t g\t \n";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 7;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_non_printable_chars(void) {
	const char *const str = "Hello \001\002 max";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 2;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_two_lines_without_whitespace(void) {
	const char *const str = "Hello\nfriend";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 2;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_two_lines_with_whitespaces(void) {
	const char *const str = "Hello \n  friend of mine";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 4;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_utf_chars(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello 😀 friend";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 3;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
}

void test_word_count_one_line_with_chars_not_in_charset(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const str = "Hello 😀 friend";
	const int actual_word_count = count_words(str);
	const int expected_word_count = 2;

	TEST_ASSERT_EQUAL_INT(expected_word_count, actual_word_count);
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
	const int actual_char_count = count_chars(str);
	const int expected_char_count = 12;

	TEST_ASSERT_EQUAL_INT(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_utf_charset(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello friend 😀";
	const int actual_char_count = count_chars(str);
	const int expected_char_count = 14;

	TEST_ASSERT_EQUAL_INT(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_utf_charset_but_ascii_locale(void) {
	setlocale(LC_CTYPE, "POSIX");

	const char *const str = "Hello friend 😀";
	const int actual_char_count = count_chars(str);
	const int expected_char_count = 17;

	TEST_ASSERT_EQUAL_INT(expected_char_count, actual_char_count);
}

void test_char_count_one_line_with_chars_in_ascii_charset_but_utf_locale(void) {
	setlocale(LC_CTYPE, "fr_BE.UTF8");

	const char *const str = "Hello friend";
	const int actual_char_count = count_chars(str);
	const int expected_char_count = 12;

	TEST_ASSERT_EQUAL_INT(expected_char_count, actual_char_count);
}

int main(void)
{
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

	// is_printable_word(word)
	RUN_TEST(test_word_printability_ascii_only);
	RUN_TEST(test_word_printability_utf);
	RUN_TEST(test_word_printability_non_printables);
	RUN_TEST(test_word_printability_non_printables_and_printables);
	RUN_TEST(test_word_printability_chars_not_in_charset_and_in_charset);
	RUN_TEST(test_word_printability_chars_not_in_charset);

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

	return UNITY_END();
}
