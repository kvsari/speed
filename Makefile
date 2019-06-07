# Makefile for speed

CC=gcc

COMPILE=-c -fno-inline -Wall -ggdb

SDL2_FLAGS=$(shell sdl2-config --cflags)
SDL2_LIBS=$(shell sdl2-config --libs)

OBJECTS=main.o video.o draw.o

speed:$(OBJECTS)
	$(CC) -o speed $(OBJECTS) $(SDL2_LIBS)

help:
	@echo "\"make\" Will make everything"
	@echo "\"make clean\" Will delete all generated files"

main.o: main.c video.h draw.h
	$(CC) $(COMPILE) main.c $(SDL2_FLAGS)

video.o: video.c video.h draw.h
	$(CC) $(COMPILE) video.c $(SDL2_FLAGS)

draw.o: draw.c draw.h video.h
	$(CC) $(COMPILE) draw.c $(SDL2_FLAGS)

clean:
	rm -f speed $(OBJECTS) *.core core
