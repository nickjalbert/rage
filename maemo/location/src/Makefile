CC = gcc
CFLAGS += -Wall -I../h
outputdir = ../bin
targets = location shake_app
libs = libcurl liblocation


.PHONY: all
all: $(targets)

location: location.o post.o shake.o
	${CC} ${CFLAGS} -Wall `pkg-config --libs $(libs)` location.o post.o shake.o -o ${outputdir}/location

location.o: location.c
	${CC} ${CFLAGS} `pkg-config --cflags $(libs)` -c location.c -o location.o

post.o: post.c
	${CC} ${CFLAGS} -c post.c -o post.o

shake.o: shake.c
	${CC} ${CFLAGS} -c shake.c -o shake.o

shake_app: shake_app.o shake.o
	${CC} ${CFLAGS} shake_app.o shake.o -o $(outputdir)/shake_app

shake_app.o: shake_app.c
	${CC} ${CFLAGS} -c shake_app.c -o shake_app.o

clean:
	$(RM) *.o
	$(foreach target,$(targets),$(RM) $(outputdir)/$(target))