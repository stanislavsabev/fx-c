# Makefile for C library

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -fPIC -g
LFLAGS = -I./include

# Directories
SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj
LIB_DIR = ./lib
TEST_DIR = ./tests
TEST_BIN_DIR = $(TEST_DIR)/bin

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
SRC_HEADERS=$(wildcard $(SRC_DIR)/*.h)
INC_HEADERS=$(wildcard $(INC_DIR)/*.h)
TESTS=$(wildcard $(TEST_DIR)/*.c)
TEST_BINS = $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TESTS))

# Library name
LIB_NAME = libfxc.a
SHARED_LIB_NAME = libfxc.so
LIB = $(LIB_DIR)/$(LIB_NAME)
SHARE_LIB = $(LIB_DIR)/$(SHARED_LIB_NAME)


h: help ##
help: ##*Show this message, default
	@awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make  \033[36m<target>\033[0m\n\nTargets:\n"} \
    /^[a-zA-Z_-]+:.*?##/ { if(length($$2) == 0 ) { printf "\033[36m%7s\033[0m", $$1 } \
							  else { printf "\t\033[36m%-12s\033[0m %s\n", $$1, $$2 }}' $(MAKEFILE_LIST)

b: build ##
build: static ## Build static

rb: rebuild ##
rebuild: clean build ## Clean and rebuild

static: headers $(OBJS)
	ar rcs $(LIB) $(OBJS)

bsh: shared ##
shared: headers $(OBJS) ## Build shared library
	$(CC) -shared -o $(SHARE_LIB) $(OBJS)

headers: $(SRC_HEADERS) $(INC_HEADERS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB)
	$(CC) $(CFLAGS) $(LFLAGS) $< $(OBJS) -o $@ -lcriterion

bt: build-tests ##
build-tests: build $(TEST_BINS) ## Build tests

t: test ##
test: build-tests ## Run tests
	@for test in $(TEST_BINS) ; do ./$$test $(TEST_FLAGS); done

c: clean ##
clean: ## Clean up
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(TEST_BIN_DIR)/*

md: makedirs ##
makedirs: ## Create buld directories
	@mkdir -p $(INC_DIR) $(OBJ_DIR) $(LIB_DIR) $(TEST_DIR) $(TEST_BIN_DIR)

f: format ##
format: ## Format with clang-format
	@clang-format -i $(SRCS) $(SRC_HEADERS) $(INC_HEADERS) $(TESTS)

.PHONY: h help b build rb rebuild static bsh shared headers bt t test c clean md makedirs f format