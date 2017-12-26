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

all: $(RESULT)

$(RESULT): $(OBJ_FILES)
	@mkdir -p $(shell dirname $@)
	@echo 'archiving : $(RESULT)'
	@ar crs $(RESULT) $(OBJ_FILES)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	@mkdir -p $(shell dirname $@)
	@echo 'compiling : $<'
	@$(CC) $(C_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	@mkdir -p $(OBJ_PATH) $(BUILD_PATH)
	@rm -R $(OBJ_PATH) $(BUILD_PATH)
