
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Lista över alla objektfiler som ska länkas
OBJS := main.o player.o game_object.o slope_objects.o modifier.o snowball_projectile.o moving_object.o static_obstacle.o temporary_modifier.o state.o slope.o

OBJSPT := player_test.o player.o game_object.o  modifier.o snowball_projectile.o moving_object.o static_obstacle.o temporary_modifier.o 

# Huvudmål
all: game playertest

# Regler för att skapa objektfiler från källkod

game_object.o: game_object.cc game_object.h
	$(CXX) $(CXXFLAGS) -c game_object.cc

player.o: player.cc player.h
	$(CXX) $(CXXFLAGS) -c player.cc

modifier.o: modifier.cc modifier.h
	$(CXX) $(CXXFLAGS) -c modifier.cc

static_obstacle.o: static_obstacle.cc static_obstacle.h
	$(CXX) $(CXXFLAGS) -c static_obstacle.cc

slope_objects.o: slope_objects.cc slope_objects.h
	$(CXX) $(CXXFLAGS) -c slope_objects.cc

moving_object.o: moving_object.cc moving_object.h
	$(CXX) $(CXXFLAGS) -c moving_object.cc

temporary_modifier.o: temporary_modifier.cc temporary_modifier.h 
	$(CXX) $(CXXFLAGS) -c temporary_modifier.cc

main.o: main.cc
	$(CXX) $(CXXFLAGS) -c main.cc

state.o: state.cc state.h
	$(CXX) $(CXXFLAGS) -c state.cc

slope.o: slope.cc slope.h slope_objects.h context.h
	$(CXX) $(CXXFLAGS) -c slope.cc

snowball_projectile.o: snowball_projectile.cc snowball_projectile.h context.h
	$(CXX) $(CXXFLAGS) -c snowball_projectile.cc

# test_main.o: test_main.cc catch.hpp
# 	$(CXX) $(CXXFLAGS) -c test_main.cc

player_test.o: player_test.cc context.h
	$(CXX) $(CXXFLAGS) -c player_test.cc


# Bygg exekverbara filer
game: $(OBJS)
	$(CXX) $(CXXFLAGS) -o play $(OBJS) $(LIBS)

playertest: $(OBJSPT)
	$(CXX) $(CXXFLAGS) -o playertest $(OBJSPT) $(LIBS)


# Rensningsregel
.PHONY: clean

clean:
	rm -f $(OBJS) play $(OBJSPT) playertest
# ------------------------------------------------