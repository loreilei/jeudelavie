CXX=g++
CXXFLAGS=-I./SFML-2.4/include/ -L./SFML-2.4/lib/
LDFLAGS=-lsfml-system -lsfml-window -lsfml-graphics
EXEC=jeudelavie

all: src/main.cpp grid.o gridrenderer.o subject.o
	$(CXX) $(CFLAGS) $(LDFLAGS) src/main.cpp grid.o gridrenderer.o subject.o -o $(EXEC)
grid.o: src/Grid.cpp src/Grid.hpp subject.o
	$(CXX) $(CFLAGS) -c src/Grid.cpp -o grid.o

gridrenderer.o: src/GridRenderer.cpp src/GridRenderer.hpp subject.o
	$(CXX) $(CFLAGS) -c src/GridRenderer.cpp  -o gridrenderer.o 

subject.o: src/Subject.cpp src/Subject.hpp src/Observer.hpp
	$(CXX) $(CFLAGS) -c src/Subject.cpp -o subject.o
clean:
	rm *.o
