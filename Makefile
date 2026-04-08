CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o code main.cpp

clean:
	rm -f code
