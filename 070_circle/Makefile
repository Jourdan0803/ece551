CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -std=c++98

all: circles

circles: main.cpp circle.cpp point.cpp
	$(CXX) $(CXXFLAGS) -o circles main.cpp circle.cpp point.cpp

clean:
	rm -f circles
