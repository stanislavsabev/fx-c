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


all: h ##* Default rule


b: build ##
build: static build-tests ## Build the library and tests


rb: rebuild ##
rebuild: clean build ## Rebuild


static: headers $(OBJS) ## Build static library
	ar rcs $(LIB) $(OBJS)


shared: headers $(OBJS) ## Build shared library
	$(CC) -shared -o $(SHARE_LIB) $(OBJS)


headers: $(SRC_HEADERS) $(INC_HEADERS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@


$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB)
	$(CC) $(CFLAGS) $(LFLAGS) $< $(OBJS) -o $@ -lcriterion


build-tests: static $(TEST_BINS) ## Build tests

t: test ##
test: build-tests ## Run tests
	@for test in $(TEST_BINS) ; do ./$$test $(TEST_FLAGS); done


c: clean ##
clean: ## Clean up
	rm -rf $(OBJ_DIR)/* $(LIB_DIR)/* $(TEST_BIN_DIR)/*


makedirs: ## Create buld directories
	@mkdir -p $(INC_DIR) $(OBJ_DIR) $(LIB_DIR) $(TEST_DIR) $(TEST_BIN_DIR)


f: format ##
format: ## Format with clang-format
	@clang-format -i $(SRCS) $(SRC_HEADERS) $(INC_HEADERS) $(TESTS)


h: help ##
help: ## Show this message
	@awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make  \033[36m<target>\033[0m\n\nTargets:\n"} \
    /^[a-zA-Z_-]+:.*?##/ { if(length($$2) == 0 ) { printf "\033[36m%7s\033[0m", $$1 } \
							  else { printf "\t\033[36m%-10s\033[0m %s\n", $$1, $$2 }}' $(MAKEFILE_LIST)


.PHONY: b build rb rebuild static shared headers build-tests t test c clean makedirs f format h help