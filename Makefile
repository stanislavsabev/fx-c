# Makefile for C library

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -fPIC -g -O0 -I.
LDFLAGS = -lcriterion

# Directories
SRC_DIR = .

OBJ_DIR = obj
TEST_DIR = tests
TEST_BIN_DIR = $(TEST_DIR)/bin

# Source files and object files
SRCS = fx.c

TEST_SRCS=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Make sure output directories exist
$(shell mkdir -p $(OBJ_DIR) $(TEST_BIN_DIR))


.PHONY: h help
h: help ##
help: ##*Show this message, default
	@awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make  \033[36m<target>\033[0m\n\nTargets:\n"} \
    /^[a-zA-Z_-]+:.*?##/ { if(length($$2) == 0 ) { printf "\033[36m%7s\033[0m", $$1 } \
							  else { printf "\t\033[36m%-12s\033[0m %s\n", $$1, $$2 }}' $(MAKEFILE_LIST)

.PHONY: rb rebuild
rb: rebuild ##
rebuild: clean build-tests ## Clean and rebuild


# Compile tests
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(SRCS)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)


.PHONY: bt build-tests
bt: build-tests ##
build-tests: $(TEST_BINS) ## Build tests

.PHONY: bm build-main
bm: build-main ##
build-main: $(TEST_BINS) ## Build tests



.PHONY: t test
t: test ##
test: build-tests ## Run tests
	@for test in $(TEST_BINS) ; do ./$$test $(TEST_FLAGS); done


.PHONY: c clean
c: clean ##
clean: ## Clean up
	rm -rf $(OBJ_DIR)/* $(TEST_BIN_DIR)/*


.PHONY: f format
f: format ##
format: ## Format with clang-format
	@clang-format -i $(SRCS) $(TEST_SRCS)

.PHONY: gh
gh: ## Open GitHub
	@firefox https://github.com/stanislavsabev/fx-c &

.PHONY: b
b: build-main ##