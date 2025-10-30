CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2

BIN := moco
OBJ := main.o

.PHONY: all clean
all: $(BIN).exe

$(BIN).exe: $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	- del /q /f "$(BIN).exe" $(OBJ) 2>nul