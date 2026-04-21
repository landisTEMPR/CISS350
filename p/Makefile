CXX = g++
CXXFLAGS = -std=c++11 -I$(shell brew --prefix raylib)/include -I./includes -I./src
LDFLAGS = -L$(shell brew --prefix raylib)/lib -lraylib
TARGET = main

SRC = $(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard includes/*.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(wildcard *.o) $(wildcard src/*.o) $(wildcard includes/*.o)

run: $(TARGET)
	./$(TARGET)
