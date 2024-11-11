#include <stdlib.h>

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

	return UNITY_END();
}
