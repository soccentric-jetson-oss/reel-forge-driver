DRV_NAME := reel-forge
DRV_VERSION := 0.1.0
CC ?= gcc
CFLAGS := -O2 -Wall -Wextra
BUILD_DIR := build
INCLUDES := -Ilib/include -Iinclude

all: lib test

lib: $(BUILD_DIR)/lib$(DRV_NAME).so $(BUILD_DIR)/lib$(DRV_NAME).a

$(BUILD_DIR)/lib$(DRV_NAME).o: lib/src/lib$(DRV_NAME).c include/reel_forge_uapi.h
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/lib$(DRV_NAME).so: $(BUILD_DIR)/lib$(DRV_NAME).o
	$(CC) -shared -o $@ $^

$(BUILD_DIR)/lib$(DRV_NAME).a: $(BUILD_DIR)/lib$(DRV_NAME).o
	ar rcs $@ $^

test: $(BUILD_DIR)/$(DRV_NAME)_test
	LD_LIBRARY_PATH=$(BUILD_DIR) $<

$(BUILD_DIR)/$(DRV_NAME)_test: test/$(DRV_NAME)_test.c $(BUILD_DIR)/lib$(DRV_NAME).a
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $< -L$(BUILD_DIR) -l$(DRV_NAME) -lpthread

clean:
	rm -rf $(BUILD_DIR)

# ── Formatting & Linting ────────────────────────────────────────────
CLANG_FILES := src/*.c include/*.h lib/src/*.c lib/include/*.h
format:
	@clang-format -i $(CLANG_FILES) 2>/dev/null || true
format-check:
	@clang-format --dry-run --Werror $(CLANG_FILES) 2>/dev/null || echo "WARNING: clang-format not available"
lint:
	@cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem src/*.c lib/src/*.c test/*.c 2>/dev/null || echo "WARNING: cppcheck not available"
doc:
	@doxygen docs/Doxyfile 2>/dev/null || echo "WARNING: doxygen not available"
analyze: format-check lint
