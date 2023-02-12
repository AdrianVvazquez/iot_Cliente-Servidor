CC = gcc
CFLAGS = -Wall -Werror
OUTPUT = servidor.o
OUTPUT2 = cliente.o
DEBUG = -g
SOURCES = servidor.c 
SOURCES2 = cliente.c 
 
all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT)
	$(CC) $(SOURCES2) $(CFLAGS) -o $(OUTPUT2)
debug:
	$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT)
clean:
	rm -f $(OUTPUT)
	rm -f $(OUTPUT2)
fresh:
	make clean
	make all
