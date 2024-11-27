CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Lista över alla objektfiler som ska länkas
OBJS := player.o game_object.o main.o state.o slope.o snowball_projectile.o

# Huvudmål
all: plmain

# Bygg exekverbara filer
plmain: $(OBJS)
	$(CXX) $(CXXFLAGS) -o plmain $(OBJS) $(LIBS)

# Regler för att skapa objektfiler från källkod
player.o: player.cc player.h
	$(CXX) $(CXXFLAGS) -c player.cc

game_object.o: game_object.cc game_object.h
	$(CXX) $(CXXFLAGS) -c game_object.cc

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

state.o: state.cc state.h
	$(CXX) $(CXXFLAGS) -c state.cc

slope.o: slope.cc slope.h
	$(CXX) $(CXXFLAGS) -c slope.cc

snowball_projectile.o: snowball_projectile.cc snowball_projectile.h
	$(CXX) $(CXXFLAGS) -c snowball_projectile.cc

modifier.o: modifier.cc modifier.h
	$(CXX) $(CXXFLAGS) -c modifier.cc

static_obstacle.o: static_obstacle.cc static_obstacle.h
	$(CXX) $(CXXFLAGS) -c static_obstacle.cc

# Regel för att bygga övriga program
player_test: player.o game_object.o player_test.o test_main.o
	$(CXX) $(CXXFLAGS) -o player_test player.o game_object.o
	 player_test.o test_main.o modifier.cc static_obstacle.cc $(LIBS)

# Rensningsregel
.PHONY: clean
clean:
	rm -f *.o plmain player_test slope_test main
