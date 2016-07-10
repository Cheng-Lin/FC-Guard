# Compiler
CPP = g++
CC_FLAGS = --std=c++14 -I .

# Library
BOOST = -lboost_system -lboost_filesystem -lboost_program_options
CURSES = -lcurses
LD_FLAGS = -lpthread

# Folders
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGETS = encrypt decrypt
CPP_FILES = $(wildcard $(SRC_DIR)/**/*.cpp)
HPP_FILES = $(wildcard $(SRC_DIR)/**/*.hpp)
OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(CPP_FILES:$(SRC_DIR)/%.cpp=%.o))

all: create_dirs $(TARGETS)

create_dirs:
	@mkdir -p $(BIN_DIR)

$(TARGETS): % : $(OBJ_DIR)/%.o $(OBJ_FILES)
	$(CPP) $(CC_FLAGS) $^ -o $(BIN_DIR)/$@ $(BOOST) $(CURSES) $(LD_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	cd $(SRC_DIR) && $(CPP) $(CC_FLAGS) -c -o ../$@ $(<:$(SRC_DIR)/%=%)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

