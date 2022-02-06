CC = gcc

CFLAGS = -g -Wpedantic -Wall -D'MAP_ITEM_FUNCS'

TARGET = cr.c vector.c map.c

all: ${TARGET}
	${CC} ${CFLAGS} -o cr ${TARGET}
