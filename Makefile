CC = gcc

CFLAGS = -g -Wall

TARGET = cr.c

all: $(TARGET)
	$(CC) $(CFLAGS) -o cr $(TARGET)
