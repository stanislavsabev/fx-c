# Makefile for C library

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include -fPIC -g


# Directories
SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj
LIB_DIR = ./lib

# Source files and object files
SRCS := $(foreach x, $(SRC_DIR), $(wildcard $(addprefix $(x)/*,.c*)))
OBJS := $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))

# Library name
LIBRARY = fxlib.a
SHARED_LIBRARY = fxlib.so


all: static shared


rebuild: clean static shared


static: makedir $(OBJS)
	ar rcs $(LIB_DIR)/$(LIBRARY) $(OBJS)


shared: makedir $(OBJS)
	$(CC) -shared -o $(LIB_DIR)/$(SHARED_LIBRARY) $(OBJS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)/$(LIBRARY) $(LIB_DIR)/$(SHARED_LIBRARY)


makedir: ## Create buld directories
	@mkdir -p $(INC_DIR) $(OBJ_DIR) $(LIB_DIR)


.PHONY: clean static shared rebuild
