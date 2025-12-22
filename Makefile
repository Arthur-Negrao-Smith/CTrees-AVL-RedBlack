CC = gcc
CFLAGS = -Wall
INCLUDE = ./include
MAIN_NAME = src/main
LIBS = src/avl.o src/redblack.o

# Windows
ifdef OS
   EXT = .exe
   RM = del /Q
   RUN_CMD = $(TARGET)
   FixPath = $(subst /,\,$1)
else
   # Linux / Unix / macOS
   EXT = 
   RM = rm -rf
   RUN_CMD = ./$(TARGET)
   FixPath = $1
endif

TARGET = $(MAIN_NAME)$(EXT)

.PHONY: all clean run

all:	$(TARGET)

run:	all
	$(RUN_CMD)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

$(TARGET): clibs
	$(CC) $(CFLAGS) $(MAIN_NAME).c $(LIBS) -o $@

clibs:	$(LIBS)

clean:
	$(RM) $(call FixPath,$(TARGET))
	$(RM) $(call FixPath,$(LIBS))
