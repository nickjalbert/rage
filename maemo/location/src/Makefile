CC = gcc
CFLAGS += -Wall -I../h
targets = location
libs = libcurl liblocation
outputdir = ../bin

.PHONY: all
all: $(targets)

location: location.o post.o
	${CC} ${CFLAGS} -Wall `pkg-config --libs $(libs)` location.o post.o -o ${outputdir}/location

location.o: location.c
	${CC} ${CFLAGS} `pkg-config --cflags $(libs)` -c location.c -o location.o

post.o: post.c
	${CC} ${CFLAGS} -c post.c -o post.o

clean:
	$(RM) $(targets) *.o