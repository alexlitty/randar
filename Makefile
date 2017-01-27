# Paths
SRCPATH=src
INCPATHS=include include/bullet3 include/cef
OBJPATH=obj
LIBPATH=lib
BINPATH=bin

# Linker flags
LDFLAGS=-L$(LIBPATH) -lcef_dll_wrapper -lcef -lX11 -lXxf86vm -pthread -lXi -lXrandr -lGL -lGLEW -lglfw3 -lBulletDynamics -lBulletCollision -lLinearMath -lpng

# Background colors
BG_WHITE=$$(tput setab 7)

# Foreground colors
FG_RED=$$(tput setaf 1)
FG_GREEN=$$(tput setaf 2)
FG_YELLOW=$$(tput setaf 3)
FG_BLUE=$$(tput setaf 4)
FG_MAGENTA=$$(tput setaf 5)
FG_CYAN=$$(tput setaf 6)

# Other colors
COLOR_RESET=$$(tput sgr 0)
 
# Goal-Based variables
GOAL = $(MAKECMDGOALS)
ifeq ($(GOAL), clean)
	GOAL = 
	SOURCE_FILES =
endif

# Files
SOURCES=$(shell find $(SRCPATH) -type f -name '*.cpp')
OBJECTS=$(SOURCES:src/%.cpp=$(OBJPATH)/%.o)
SOURCE_FILES =$(SOURCES)
OBJECT_FILES=$(OBJECTS)

# Compilers
CC_linux64=g++
CC = $(CC_$(GOAL))

# Language-specific flags
CFLAGS_linux64=-Wall -std=c++11 -g
CFLAGS=$(CFLAGS_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
EXECUTABLE_linux64=randar
EXECUTABLE=$(EXECUTABLE_$(GOAL))

# Initial Target
$(GOAL): $(SOURCES_FILES) $(EXECUTABLE)
	@echo "$(BG_WHITE)$(FG_MAGENTA) Executing $(COLOR_RESET)"

# Link into executable
$(EXECUTABLE): $(OBJECT_FILES)
	@echo ""
	@echo "$(BG_WHITE)$(FG_GREEN) Linking $(COLOR_RESET)"
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $(BINPATH)/$@
	@echo ""

# Compile source into objects
$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@

# Cleaning Target
.PHONY: clean
clean:
	@find . -type f -name '*.o' -delete
