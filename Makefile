CC=gcc
CFLAGS=`sdl-config --cflags` -c -Wall -std=c89 -pedantic
LDFLAGS=-lm `sdl-config --libs`
HOME_DIR=.
BUILD_DIR=$(HOME_DIR)/build
SRC_DIR=$(HOME_DIR)/src
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

$(BUILD_DIR)/game: $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(BUILD_DIR)/game $(OBJFILES)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm $(OBJFILES)
	rm $(BUILD_DIR)/game

.PHONY:clean
