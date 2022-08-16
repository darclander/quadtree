OBJS = ./src/*.cpp

CC=g++
CFLAGS= -I$(IDIR) -lmingw32 -lSDL2main -lSDL2 -lSDL2_Image

IDIR = ./src/headers
_DEPS = quadtree.hpp window.hpp square.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = ./obj
_OBJ = main.o quadtree.o window.o square.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: quadtree

./obj/%.o: ./src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

quadtree: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

run: quadtree
	./quadtree

clean:
	del /s *.o
	del quadtree.exe

###################
### Inspiration ###
###################

# IDIR =../include
# CC=gcc
# CFLAGS=-I$(IDIR)

# ODIR=obj
# LDIR =../lib

# LIBS=-lm

# _DEPS = hellomake.h
# DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _OBJ = hellomake.o hellofunc.o 
# OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


# $(ODIR)/%.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

# hellomake: $(OBJ)
# 	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# .PHONY: clean

# clean:
# 	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 