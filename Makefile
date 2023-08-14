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

# Library name
LIBRARY = libfxc.a
SHARED_LIBRARY = libfxc.so


all: static


rebuild: clean static
rb: rebuild


static: makedir $(OBJS)
	ar rcs $(LIB_DIR)/$(LIBRARY) $(OBJS)


shared: makedir $(OBJS)
	$(CC) -shared -o $(LIB_DIR)/$(SHARED_LIBRARY) $(OBJS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)/*
c: clean


makedir: ## Create buld directories
	@mkdir -p $(INC_DIR) $(OBJ_DIR) $(LIB_DIR)


.PHONY: static shared c clean rb rebuild  
