# Directories
UNITY_DIR = Unity/src
SRC_DIR = src
TEST_DIR = test

# Files
MAIN_TEST = $(TEST_DIR)/spec.c
TEST_SRC = $(TEST_DIR)/ccwc.spec.c
PARSER_TEST_SRC = $(TEST_DIR)/parser.spec.c
SRC = $(SRC_DIR)/ccwc.c
PARSER_SRC = $(SRC_DIR)/parser.c
ERROR_SRC = $(SRC_DIR)/errors.c
UNITY_SRC = $(UNITY_DIR)/unity.c
MAIN = $(SRC_DIR)/main.c

# Compiler flags
CFLAGS_SRC = -I $(SRC_DIR)
CFLAGS_TEST = -I $(UNITY_DIR) -I $(SRC_DIR)

# Targets
TARGET_SRC = ccwc
TARGET_TEST = ccwc.test

all: $(TARGET_TEST)

$(TARGET_TEST): $(MAIN_TEST) $(TEST_SRC) $(PARSER_TEST_SRC) $(SRC) $(UNITY_SRC) $(PARSER_SRC) $(ERROR_SRC)
	gcc -fprofile-arcs -ftest-coverage $(CFLAGS_TEST) -o $(TARGET_TEST) $(UNITY_SRC) $(MAIN_TEST) $(TEST_SRC) $(PARSER_TEST_SRC) $(SRC) $(PARSER_SRC) $(ERROR_SRC)

$(TARGET_SRC): $(MAIN) $(SRC) $(PARSER_SRC) $(ERROR_SRC)
	gcc $(CFLAGS_SRC) -o $(TARGET_SRC) $(SRC) $(MAIN) $(PARSER_SRC) $(ERROR_SRC)

build: $(TARGET_SRC)
	@echo "Successfully compiled"

run: $(TARGET_SRC)
	./$(TARGET_SRC) $(ARGS)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out --exclude $(UNITY_DIR)
	firefox out/index.html

clean:
	rm -f *.gcda *.gcno
	rm -f $(TARGET_TEST) $(TARGET_SRC)
	rm -f coverage.info
	rm -rf out/
