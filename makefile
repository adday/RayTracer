#cs410 p4 makefile (raytracer)
#Alexander Day

CC=g++
OBJS=main.o Model.o Camera.o Shader.o Image.o Parser.o
DEBUG=-g
CFLAGS=-std=c++11 -O3 -Wall -I /Eigen/ -I . -c $(DEBUG)
LFLAGS=-Wall $(DEBUG)

all: raytracer

raytracer: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o raytracer

main.o: main.cpp Model.h Camera.h Shader.h Image.h Parser.h
	$(CC) $(CFLAGS) main.cpp

Model.o: Model.cpp Model.h
	$(CC) $(CFLAGS) Model.cpp

Camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) Camera.cpp

Shader.o: Shader.cpp Shader.h
	$(CC) $(CFLAGS) Shader.cpp

Image.o: Image.cpp Image.h
	$(CC) $(CFLAGS) Image.cpp
	
Parser.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) Parser.cpp

clean:
	rm -f $(OBJS) *~ raytracer
 

