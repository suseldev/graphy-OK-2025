CC      := gcc
CFLAGS  := -std=c11 -O2 -Wall -Wextra -Iinclude
LDFLAGS := -lgsl -lgslcblas -lm

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

# all C files
SRC := $(wildcard $(SRC_DIR)/*.c)

MAIN_RANDOM       := main_random.c
MAIN_GREEDY       := main_greedy.c
MAIN_RAND_GREEDY  := main_rand_greedy.c

COMMON_SRC := $(filter-out \
    $(SRC_DIR)/$(MAIN_RANDOM) \
    $(SRC_DIR)/$(MAIN_GREEDY) \
    $(SRC_DIR)/$(MAIN_RAND_GREEDY), \
    $(SRC))

COMMON_OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(COMMON_SRC))

all: graphy_random graphy_greedy graphy_rand_greedy

graphy_random: $(COMMON_OBJ) $(OBJ_DIR)/main_random.o | $(BIN_DIR)
	$(CC) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

graphy_greedy: $(COMMON_OBJ) $(OBJ_DIR)/main_greedy.o | $(BIN_DIR)
	$(CC) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

graphy_rand_greedy: $(COMMON_OBJ) $(OBJ_DIR)/main_rand_greedy.o | $(BIN_DIR)
	$(CC) $^ -o $(BIN_DIR)/$@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

