#include <stdlib.h>

#include "unity.h"
#include "ccwc.h"

char* dynamic_content;

void setUp(void) {
	dynamic_content = NULL;
}

void tearDown(void) {
	printf("Freeing up memory...\n%s\n", dynamic_content);
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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_byte_count_one_line);
	RUN_TEST(test_byte_count_two_lines);
	RUN_TEST(test_byte_count_one_line_with_non_ascii);
	RUN_TEST(test_file_content_retrieval_one_line);
	RUN_TEST(test_file_content_retrieval_two_lines);
	return UNITY_END();
}
