CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = main.cpp
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE)
