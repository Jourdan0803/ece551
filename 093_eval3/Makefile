# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98

# Source files common to all executables
COMMON_SOURCES = Story.cpp Page.cpp
COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)

# Targets
all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4

# cyoa-step1
cyoa-step1: cyoa-step1.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o cyoa-step1 cyoa-step1.o $(COMMON_OBJECTS)

cyoa-step1.o: cyoa-step1.cpp
	$(CXX) $(CXXFLAGS) -c cyoa-step1.cpp

# cyoa-step2
cyoa-step2: cyoa-step2.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o cyoa-step2 cyoa-step2.o $(COMMON_OBJECTS)

cyoa-step2.o: cyoa-step2.cpp
	$(CXX) $(CXXFLAGS) -c cyoa-step2.cpp

# cyoa-step3
cyoa-step3: cyoa-step3.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o cyoa-step3 cyoa-step3.o $(COMMON_OBJECTS)

cyoa-step3.o: cyoa-step3.cpp
	$(CXX) $(CXXFLAGS) -c cyoa-step3.cpp
# cyoa-step4
cyoa-step4: cyoa-step4.o $(COMMON_OBJECTS)
	$(CXX) $(CXXFLAGS) -o cyoa-step4 cyoa-step4.o $(COMMON_OBJECTS)
cyoa-step4.o: cyoa-step4.cpp
	$(CXX) $(CXXFLAGS) -c cyoa-step4.cpp 

# Compile common source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean the build
clean:
	rm -f cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4$(COMMON_OBJECTS) cyoa-step1.o cyoa-step2.o cyoa-step3.o cyoa-step4.o

# Prevent make from doing something with a file named clean
.PHONY: all clean
