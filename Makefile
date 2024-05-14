# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinc

# Source files
SRCS = src/Token.cpp src/Scanner.cpp src/Lox.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
EXEC = lox

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

# Rebuild the project from scratch
rebuild: clean all

# Phony targets (not actual files)
.PHONY: all clean rebuild run
