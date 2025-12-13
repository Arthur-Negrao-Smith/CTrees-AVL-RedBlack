CC = gcc
CFLAGS = -Wall
INCLUDE = ./include


TARGET = src/main
LIBS = src/avl.o

.PHONY: all clean

all:	$(TARGET)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

$(TARGET): clibs
	$(CC) $(CFLAGS) $(TARGET:%=%.c) $(LIBS) -o $@

clibs:	$(LIBS)

clean:
	rm -rf $(TARGET)
	rm -rf $(LIBS)
