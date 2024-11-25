CXX:=g++
CXXFLAGS:=-std=c++17 -Wall -Wextra -Wpedantic
LIBS:=-lsfml-graphics -lsfml-window -lsfml-system

all: slope

slope_test: slope.cc test_main.cc test.cc
	$(CXX) $(CXXFLAGS) -o slope_test slope.cc test_main.cc test.cc $(LIBS)

main: main.cc state.cc slope.cc
	$(CXX) $(CXXFLAGS) -o main main.cc state.cc slope.cc $(LIBS)

player: player.cc game_object.cc player_test.cc test_main.cc
	$(CXX) $(CXXFLAGS) -o player player.cc game_object.cc player_test.cc test_main.cc $(LIBS)

.PHONY: clean
clean:
	rm slope
