# name project
TAG := lg

# name compiler
CC := gcc

# source parametres
SRC := main.c
SRC += $(wildcard source/*.c)

# flag parametres
CFLAG := -Wall
CFLAG += -std=c11
CFLAG += -Iinclude/

# library parametres
LIB := -lglfw
LIB += -framework OpenGL

# mode list
.PHONY: release debug clean

# release mode
release: build/release/$(TAG)

build/release/$(TAG): $(SRC)
	@echo "[RELEASE]"
	@mkdir -p build/release/
	@$(CC) $(CFLAG) $(LIB) -O3 $^ -o $@

# debug mode
debug: build/debug/$(TAG)

build/debug/$(TAG): $(SRC)
	@echo "[DEBUG]"
	@mkdir -p build/debug/
	@$(CC) $(CFLAG) $(LIB) -g $^ -o $@

# clean mode
clean:
	@echo "[CLEAN]"
	@rm -r -f build/
