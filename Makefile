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



# --------------------------------------------------

# Makefile for compiling the project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
# Linker flags for SFML
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = main.cc game_object.cc modifier.cc moving_object.cc static_obstacle.cc temporary_modifier.cc slope.cc state.cc player.cc snowball_projectile.cc

# Header files
HEADERS = game_object.h modifier.h moving_object.h static_obstacle.h temporary_modifier.h slope.h state.h player.h snowball_projectile.h

# Object files (compiled from source files)
OBJS = $(SRCS:.cc=.o)

# Output binary name
TARGET = game

# Default target
all: $(TARGET)

# Linking the object files to create the final executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile the source files into object files
%.o: %.cc $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the project (force make to run)
rebuild: clean all

.PHONY: all clean rebuild