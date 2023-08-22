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

# Source files and object files
SRCS := $(foreach x, $(SRC_DIR), $(wildcard $(addprefix $(x)/*,.c*)))
OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))
SRC_HEADERS=$(wildcard $(SRC_DIR)/*.h)
INC_HEADERS=$(wildcard $(INC_DIR)/*.h)

# Library name
LIBRARY = libfxc.a
SHARED_LIBRARY = libfxc.so


all: static ## Default fule


rb: rebuild ##
rebuild: clean static ## Rebuild


static: makedirs headers $(OBJS) ## Build static library
	ar rcs $(LIB_DIR)/$(LIBRARY) $(OBJS)


shared: makedirs headers $(OBJS) ## Build shared library
	$(CC) -shared -o $(LIB_DIR)/$(SHARED_LIBRARY) $(OBJS)


headers: $(SRC_HEADERS) $(INC_HEADERS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@


c: clean ##
clean: ## Clean up
	rm -rf $(OBJ_DIR) $(LIB_DIR)/*


makedirs: ## Create buld directories
	@mkdir -p $(INC_DIR) $(OBJ_DIR) $(LIB_DIR)

format: ## Format with clang-format
	@clang-format -i $(SRCS) $(SRC_HEADERS) $(INC_HEADERS)

h: help ##
help: ## Show this message
	@awk 'BEGIN {FS = ":.*##"; printf "Usage:\n  make  \033[36m<target>\033[0m\n\nTargets:\n"} \
    /^[a-zA-Z_-]+:.*?##/ { if(length($$2) == 0 ) { printf "\033[36m%7s\033[0m", $$1 } \
							  else { printf "\t\033[36m%-10s\033[0m %s\n", $$1, $$2 }}' $(MAKEFILE_LIST)

.PHONY: static shared c clean rb rebuild makedirs
