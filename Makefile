# Define variables for compiler and flags
CXX = g++
CXXFLAGS = -O2 -Wall -Wno-missing-braces
INCLUDES = -I./include/ -I./src/header/
LIBS = -L./lib/ -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Define source and object files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Define the target executable
TARGET = Game

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $@

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(TARGET) $(OBJS)

# Declare the default target
.PHONY: all clean
all: $(TARGET)
