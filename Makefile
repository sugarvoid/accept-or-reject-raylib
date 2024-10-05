# Define variables for compiler and flags
CC = g++
COMPILER_FLAGS = -O2 -Wall -Wno-missing-braces
LINKER_FLAGS = -L./lib/ -lraylib -lbox2d -lGL -lm -lpthread -ldl -lrt -lX11


# Define source and object files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)


# Define the target executable
TARGET = game

all : $(TARGET)
# Build target executable from object files
$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(TARGET)

# Compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

# Declare clean and rebuild as phony targets
.PHONY: clean rebuild

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild: clean and then build
rebuild: clean all

