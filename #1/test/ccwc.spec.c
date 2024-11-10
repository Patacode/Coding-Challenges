#include "unity.h"
#include "ccwc.h"

void setUp(void) {}
void tearDown(void) {}

/**
 * Test scenarios:
 * - one line containing ASCII characters only
 * - two lines containing ASCII characters only
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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_byte_count_one_line);
	RUN_TEST(test_byte_count_two_lines);
	return UNITY_END();
}
