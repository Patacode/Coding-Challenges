#include "unity.h"
#include "ccwc.h"

void setUp(void) {}
void tearDown(void) {}

void test_byte_count(void)
{
	const char *const str = "Hello, World";
	const int actual_byte_count = count_bytes(str);
	const int expected_byte_count = 12;

	TEST_ASSERT_EQUAL_INT(expected_byte_count, actual_byte_count);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_byte_count);
	return UNITY_END();
}
