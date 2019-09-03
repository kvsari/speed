# Makefile for speed

CC=gcc

COMPILE=-c -fno-inline -Wall -ggdb

SDL2_FLAGS=$(shell sdl2-config --cflags)
SDL2_LIBS=$(shell sdl2-config --libs)

OBJECTS=main.o video.o draw.o input.o geop.o \
				polyhedron.o entity.o world.o camera.o

speed:$(OBJECTS)
	$(CC) -o speed $(OBJECTS) $(SDL2_LIBS) -lm

help:
	@echo "\"make\" Will make everything"
	@echo "\"make clean\" Will delete all generated files"

main.o: main.c video.h draw.h
	$(CC) $(COMPILE) main.c $(SDL2_FLAGS)

video.o: video.c video.h draw.h
	$(CC) $(COMPILE) video.c $(SDL2_FLAGS)

draw.o: draw.c draw.h video.h
	$(CC) $(COMPILE) draw.c $(SDL2_FLAGS)

input.o: input.c input.h
	$(CC) $(COMPILE) input.c $(SDL2_FLAGS)

geop.o: geop.c geop.h
	$(CC) $(COMPILE) geop.c

polyhedron.o: polyhedron.c polyhedron.h geop.h
	$(CC) $(COMPILE) polyhedron.c

entity.o: entity.c entity.h polyhedron.h
	$(CC) $(COMPILE) entity.c

world.o: world.c world.h
	$(CC) $(COMPILE) world.c

camera.o: camera.c camera.h draw.h entity.h world.h geop.h
	$(CC) $(COMPILE) camera.c $(SDL2_FLAGS)

clean:
	rm -f speed $(OBJECTS) *.core core
