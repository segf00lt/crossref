CC = gcc

CFLAGS = -g -Wall

TARGET = crossref.c

all: $(TARGET)
	$(CC) $(CFLAGS) -o crossref $(TARGET)
