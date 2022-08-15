OBJS = ./src/*.cpp

CC=g++
CFLAGS= 
DEPS = ./src/quadtree.hpp

all: quadtree

./obj/%.o: ./src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

quadtree: ./obj/main.o ./obj/quadtree.o
	$(CC) -o quadtree ./obj/main.o ./obj/quadtree.o

clean:
	del /s *.o
	del quadtree.exe

