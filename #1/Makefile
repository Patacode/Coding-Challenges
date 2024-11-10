# Directories
UNITY_DIR = Unity/src
SRC_DIR = src
TEST_DIR = test

# Files
TEST_SRC = $(TEST_DIR)/ccwc.spec.c
SRC = $(SRC_DIR)/ccwc.c
UNITY_SRC = $(UNITY_DIR)/unity.c

# Compiler flags
CFLAGS_SRC = -I $(SRC_DIR)
CFLAGS_TEST = -I $(UNITY_DIR) -I $(SRC_DIR)

# Targets
TARGET_SRC = ccwc
TARGET_TEST = ccwc.test

all: $(TARGET_TEST)

$(TARGET_TEST): $(TEST_SRC) $(SRC) $(UNITY_SRC)
	gcc $(CFLAGS_TEST) -o $(TARGET_TEST) $(UNITY_SRC) $(TEST_SRC) $(SRC)

build: $(SRC)
	gcc $(CFLAGS_SRC) -o $(TARGET_SRC) $(SRC)

test: $(TARGET_TEST)
	./$(TARGET_TEST)

clean:
	rm -f $(TARGET_TEST)
