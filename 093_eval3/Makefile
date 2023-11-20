# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98

# Target executable name
TARGET = cyoa-step1

# Source files
SOURCES = cyoa-step1.cpp Story.cpp Page.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Rule to make the target
all: $(TARGET)

# Rule to link the program
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile the source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean the build
clean:
	rm -f $(TARGET) $(OBJECTS)

# Prevent make from doing something with a file named clean
.PHONY: all clean
