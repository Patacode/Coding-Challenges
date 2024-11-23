# Directories
UNITY_DIR = Unity/src
SRC_DIR = src
TEST_DIR = test

# Files
TEST_SRC = $(TEST_DIR)/ccwc.spec.c
SRC = $(SRC_DIR)/ccwc.c
PARSER_SRC = $(SRC_DIR)/parser.c
UNITY_SRC = $(UNITY_DIR)/unity.c
MAIN = $(SRC_DIR)/main.c

# Compiler flags
CFLAGS_SRC = -I $(SRC_DIR)
CFLAGS_TEST = -I $(UNITY_DIR) -I $(SRC_DIR)

# Targets
TARGET_SRC = ccwc
TARGET_TEST = ccwc.test

all: $(TARGET_TEST)

$(TARGET_TEST): $(TEST_SRC) $(SRC) $(UNITY_SRC) $(PARSER_SRC)
	gcc -fprofile-arcs -ftest-coverage $(CFLAGS_TEST) -o $(TARGET_TEST) $(UNITY_SRC) $(TEST_SRC) $(SRC) $(PARSER_SRC)

$(TARGET_SRC): $(MAIN) $(SRC) $(PARSER_SRC)
	gcc $(CFLAGS_SRC) -o $(TARGET_SRC) $(SRC) $(MAIN) $(PARSER_SRC)

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
