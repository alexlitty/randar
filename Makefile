# Paths
SRCPATH=src
INCPATHS=include include/bullet3 include/cef include/pngpp
OBJPATH=obj
LIBPATH=lib
BINPATH=bin

# Linker flags
LDFLAGS=-L$(LIBPATH) -lcef_dll_wrapper -lcef -lX11 -lXxf86vm -pthread -lXi -lXrandr -lGL -lGLEW -lglfw3 -lBulletDynamics -lBulletCollision -lLinearMath -lpng

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

# Link into executable
$(EXECUTABLE): $(OBJECT_FILES)
	@echo "Creating executable $(BINPATH)/$@"
	@$(CC) $(CFLAGS) $(OBJECT_FILES) $(LDFLAGS) -o $(BINPATH)/$@

# Compile source into objects
$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	@echo -n "Compiling $<"
	@$(CC) $(INCFLAGS) $(CFLAGS) -c $< -o $@

# Cleaning Target
.PHONY: clean
clean:
	@find . -type f -name '*.o' -delete
