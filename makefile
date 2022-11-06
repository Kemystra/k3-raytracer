linkTarget = k3-rtx

# Define needed libraries
LIBS = -lSDL2

# Define flags
CFLAGS = -std=c++17

# Define needed object files (*.o)
objects = main.o CApp.o $(patsubst %.cpp, %.o, $(wildcard ./k3RayTrace/*.cpp))

# Define stuff that can be rebuild for each compilations
rebuildables = $(objects) $(linkTarget)

# Rule for builds
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create object files
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rmtrash $(rebuildables)