BUILD_PATH=build
INC_PATHS=include include/bullet3
OBJ_PATH=obj
SRC_PATH=src

SRC_FILES=$(shell find $(SRC_PATH) -type f -name '*.cpp')
OBJ_FILES=$(subst .cpp,.o,$(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_FILES)))

GOAL_SYSTEM=$(shell uname -s)
GOAL_ARCHITECTURE=64
GOAL=$(GOAL_SYSTEM)$(GOAL_ARCHITECTURE)

CC_Linux64=g++
CC=$(CC_$(GOAL))

C_FLAGS_Linux64=-std=c++11
C_FLAGS=$(C_FLAGS_$(GOAL)) -g -Wall $(foreach TMP,$(INC_PATHS),-I$(TMP))

RESULT_Linux64=randar.a
RESULT=$(BUILD_PATH)/$(GOAL)/$(RESULT_$(GOAL))

.PHONY: all
all: $(RESULT)

$(RESULT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(RESULT)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(C_FLAGS) -c $< -o $@
