# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Target executable
TARGET = engine

# Source files (explicit to avoid CSV issues)
SRCS = main.cpp \
       Game.cpp \
       GameUtils.cpp \
       World.cpp \
       FortniteWorld.cpp \
       WorldGraph.cpp \
       Entry.cpp \
       Chest.cpp \
       Item.cpp \
       Weapon.cpp \
       ItemDatabase.cpp \
       LootPool.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compile step
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run (interactive default)
run: $(TARGET)
	./$(TARGET) --map DefaultMap.csv --loot Items.csv --runs 1

# Run simulation
simulate: $(TARGET)
	./$(TARGET) --map DefaultMap.csv --loot Items.csv --runs 1000000

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)