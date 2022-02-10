CC = gcc

CFLAGS = -g -Wpedantic -Wall

SRC = cr.c

all:
	${CC} ${CFLAGS} -o cr ${SRC}
